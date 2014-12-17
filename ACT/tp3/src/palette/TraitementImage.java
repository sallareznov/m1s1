package palette;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;
import java.util.TreeMap;

public class TraitementImage {
	
	public static int[][] construitImagePGM() {
		final Scanner sc = new Scanner(System.in);
		sc.nextLine();
		final int n = sc.nextInt();
		final int m = sc.nextInt();
		final int[][] image = new int[n][m];
		sc.nextInt();
		int xCourant = 0;
		int yCourant = 0;
		for (int i = 0; i < n * m; i++) {
			image[xCourant][yCourant] = sc.nextInt();
			yCourant++;
			if (yCourant == image[0].length) {
				yCourant = 0;
				xCourant++;
			}
		}
		sc.close();
		return image;
	}
	
	public static Palette imageToPalette(int[][] image) {
		final Map<Integer, Integer> cptPixels = new TreeMap<Integer, Integer>();
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image[0].length; j++) {
				final int pixelCourant = image[i][j];
				if (!cptPixels.containsKey(pixelCourant))
					cptPixels.put(pixelCourant, 1);
				else
					cptPixels
							.put(pixelCourant, cptPixels.get(pixelCourant) + 1);
			}
		}
		final List<Couleur> couleursList = new LinkedList<Couleur>();
		for (final Entry<Integer, Integer> couleur : cptPixels.entrySet()) {
			couleursList.add(new Couleur(couleur.getValue(), couleur.getKey()));
		}
		final Couleur[] couleursTab = couleursList
				.toArray(new Couleur[couleursList.size()]);
		return new Palette(couleursTab);
	}
	
	public static int[][] paletteToImage(int[][] image,
			Map<Integer, Integer> assoc) {
		final int[][] newImage = new int[image.length][image[0].length];
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image[0].length; j++) {
				newImage[i][j] = assoc.get(image[i][j]);
			}
		}
		return newImage;
	}

	public static void afficheImage(int[][] image) {
		System.out.println("P2");
		System.out.println(image.length + " " + image[0].length);
		System.out.println("255");
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image[0].length; j++) {
				System.out.println(image[i][j]);
			}
		}
	}

}
