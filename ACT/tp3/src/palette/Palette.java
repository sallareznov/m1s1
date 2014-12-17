package palette;

import java.util.HashMap;
import java.util.Map;

public class Palette {

	private Couleur[] _couleurs;

	public Palette(Couleur[] couleurs) {
		_couleurs = couleurs;
	}

	public int getTaille() {
		return _couleurs.length;
	}

	public Couleur getCouleur(int i) throws ArrayIndexOutOfBoundsException {
		return _couleurs[i];
	}

	public int meilleurGris(int deb, int fin) throws IllegalArgumentException {
		if ((deb < 0) || (fin < 0) || (deb > fin) || (fin >= getTaille())) {
			throw new IllegalArgumentException();
		}
		int sommeGris = 0;
		int sommePoids = 0;
		for (int i = deb; i <= fin; i++) {
			final Couleur couleurCourante = _couleurs[i];
			sommeGris += couleurCourante.getGris() * couleurCourante.getPoids();
			sommePoids += couleurCourante.getPoids();
		}
		return (Math.round(sommeGris / sommePoids));
	}

	public int distanceMin(int deb, int fin) throws IllegalArgumentException {
		if ((deb < 0) || (deb > fin) || (fin >= getTaille())) {
			throw new IllegalArgumentException();
		}
		int distanceMinimale = 0;
		final int meilleurGrisDebFin = meilleurGris(deb, fin);
		for (int i = deb; i <= fin; i++) {
			final Couleur couleurCourante = _couleurs[i];
			final int ecartGris = couleurCourante.getGris()
					- meilleurGrisDebFin;
			final double carreEcartGris = Math.pow(ecartGris, 2);
			distanceMinimale += carreEcartGris * couleurCourante.getPoids();
		}
		return distanceMinimale;
	}

	public int decompose(int k, int deb, int vecteurIndices[][])
			throws IllegalArgumentException {
		if ((k < 0) || (deb < 0) || (deb >= getTaille()) || (k > getTaille())) {
			throw new IllegalArgumentException();
		}

		if (k == getTaille()) {
			return 0;
		}

		final int vecteurDistanceMin[][] = new int[k + 1][getTaille()];

		for (int j = 0; j < vecteurDistanceMin[0].length; j++) {
			vecteurDistanceMin[0][j] = 0;
			vecteurDistanceMin[1][j] = distanceMin(j, getTaille() - 1);
		}

		for (int i = 2; i < vecteurDistanceMin.length; i++) {
			for (int j = 0; j < vecteurDistanceMin[0].length; j++) {
				vecteurDistanceMin[i][j] = distanceMin(deb, getTaille() - 1);
				for (int l = j + 1; l <= getTaille() - i; l++) {
					final int distanceMinDebI = distanceMin(j, l)
							+ vecteurDistanceMin[i - 1][l + 1];
					if (distanceMinDebI < vecteurDistanceMin[i][j]) {
						vecteurDistanceMin[i][j] = distanceMinDebI;
						vecteurIndices[i][j] = l;
					}
				}
			}
		}
		return vecteurDistanceMin[k][deb];
	}

	public int[] getSegmentsPaletteReduite(int k, int[][] vecteurIndices) {
		final int[] segments = new int[k];
		segments[k - 1] = getTaille() - 1;
		int indSegments = 0;
		int current = 0;
		for (int i = k; i > 1; i--) {
			current = vecteurIndices[i][current];
			segments[indSegments] = current;
			current++;
			indSegments++;
		}
		return segments;
	}

	public Map<Integer, Integer> getAssoc(int[] segments) {
		final Map<Integer, Integer> assoc = new HashMap<Integer, Integer>();
		int debutSegment = 0;
		for (int i = 0; i < segments.length; i++) {
			final int finSegment = segments[i];
			final int meilleurGrisSegment = meilleurGris(debutSegment,
					segments[i]);
			for (int j = debutSegment; j <= finSegment; j++) {
				final Couleur couleurCourante = getCouleur(j);
				assoc.put(couleurCourante.getGris(), meilleurGrisSegment);
			}
			debutSegment = finSegment + 1;
		}
		return assoc;
	}

}
