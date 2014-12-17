package palette;

import java.util.Map;

public class Main {
	
	private static void usage() {
		System.err
				.println("java Palette k < ../images-test/imageInitiale > ../images-test/imageReduite");
		System.err.println("k : le nombre de couleurs de la palette réduite");
		System.err.println("imageInitiale : l'image initiale à réduire");
		System.err.println("imageReduite : l'image finale obtenue");
	}
	
	public static void main(String[] args) throws Exception {
		try {
			// récupération de k
			final int k = Integer.parseInt(args[0]);
			// construction de l'image initiale
			final int[][] imageInitiale = TraitementImage.construitImagePGM();
			// transformation de l'image initiale en palette
			final Palette paletteImageInitiale = TraitementImage.imageToPalette(imageInitiale);
			// construction du vecteur d'indices et décomposition de la palette
			final int[][] vecteurIndices = new int[k + 1][paletteImageInitiale.getTaille()];
			paletteImageInitiale.decompose(k, 0, vecteurIndices);
			// récupération des segments de décomposition à k couleurs
			final int[] segments = paletteImageInitiale.getSegmentsPaletteReduite(k, vecteurIndices);
			// récupération de la table d'association entre les anciens et les nouveaux gris de l'image réduite
			final Map<Integer, Integer> assoc = paletteImageInitiale.getAssoc(segments);
			// construction de l'image réduite à partir de l'image initiale et de la table d'association
			final int[][] imageReduite = TraitementImage.paletteToImage(imageInitiale, assoc);
			// affichage de l'image réduite
			TraitementImage.afficheImage(imageReduite);
		} catch (ArrayIndexOutOfBoundsException e) {
			// pas assez d'arguments
			usage();
		} catch (NumberFormatException e) {
			// k n'est pas un entier
			usage();
		}
	}

}
