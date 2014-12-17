package palette;

import java.util.Comparator;

public class Couleur {
	
	private int _poids;
	private int _gris;
	
	public Couleur(int poids, int gris) {
		_poids = poids;
		_gris = gris;
	}
	
	public int getPoids() {
		return _poids;
	}
	
	public int getGris() {
		return _gris;
	}
	
	@Override
    public boolean equals(Object obj) {
    	if (obj instanceof Couleur) {
    		final Couleur couleur = (Couleur) obj;
    		return ((couleur.getGris() == _gris) && (couleur.getPoids() == _poids));
    	}
    	return false;
    }
	
	public static class ComparateurCouleur implements Comparator<Couleur> {

		@Override
		public int compare(Couleur arg0, Couleur arg1) {
			return Integer.signum(arg0.getGris() - arg1.getGris());
		}
    	
    }

}
