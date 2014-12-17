package palette;

import static org.junit.Assert.assertEquals;

import java.util.Map;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

public class PaletteUnitTest {

	private Couleur[] couleurs;
	private Palette palette;
	private Integer[][] image;
	private Palette nouvellePalette;
	private Map<Integer, Integer> oldGrisToNewGris;

	@Before
	public void setUp() {
		// couleurs
		couleurs = new Couleur[7];
		couleurs[0] = new Couleur(5, 0);
		couleurs[1] = new Couleur(5, 20);
		couleurs[2] = new Couleur(1, 100);
		couleurs[3] = new Couleur(1, 132);
		couleurs[4] = new Couleur(2, 164);
		couleurs[5] = new Couleur(1, 180);
		couleurs[6] = new Couleur(10, 255);
		// palette
		palette = new Palette(couleurs);
		// image
		image = new Integer[5][5];
		image[0][0] = 0;
		image[0][1] = 0;
		image[0][2] = 0;
		image[0][3] = 0;
		image[0][4] = 0;
		image[1][0] = 20;
		image[1][1] = 20;
		image[1][2] = 20;
		image[1][3] = 20;
		image[1][4] = 20;
		image[2][0] = 100;
		image[2][1] = 132;
		image[2][2] = 164;
		image[2][3] = 164;
		image[2][4] = 180;
		image[3][0] = 255;
		image[3][1] = 255;
		image[3][2] = 255;
		image[3][3] = 255;
		image[3][4] = 255;
		image[4][0] = 255;
		image[4][1] = 255;
		image[4][2] = 255;
		image[4][3] = 255;
		image[4][4] = 255;
		// nouvelle palette
		nouvellePalette = TraitementImage.imageToPalette(image);
		// oldGrisToNewGris
		oldGrisToNewGris = nouvellePalette.getAssocGris(3);
	}

	@Rule
	public ExpectedException expectedException = ExpectedException.none();

	@Test
	public void testMeilleurGris() {
		assertEquals(135, palette.meilleurGris(0, 6));
		expectedException.expect(IllegalArgumentException.class);
		expectedException.expectMessage("Intervalle incorrect");
		assertEquals(135, palette.meilleurGris(3, 8));
	}

	@Test
	public void testDistanceMin() {
		assertEquals(
				5096,
				palette.distanceMin(0, 1) + palette.distanceMin(2, 5)
						+ palette.distanceMin(6, 6));
		expectedException.expect(IllegalArgumentException.class);
		expectedException.expectMessage("Intervalle incorrect");
		assertEquals(
				5096,
				palette.distanceMin(0, 1) + palette.distanceMin(2, 5)
						+ palette.distanceMin(6, 7));
	}

	@Test
	public void testDecompose() {
		Integer[][] tabIndices = Palette.genereSentinelle(4,
				palette.getTaille());
		assertEquals(5096, palette.decompose(3, 0, tabIndices));
	}

	@Test
	public void testImageToPalette() {
		assertEquals(7, nouvellePalette.getTaille());
		assertEquals(5, nouvellePalette.getCouleur(0).getPoids());
		assertEquals(0, nouvellePalette.getCouleur(0).getGris());
		assertEquals(5, nouvellePalette.getCouleur(1).getPoids());
		assertEquals(20, nouvellePalette.getCouleur(1).getGris());
		assertEquals(1, nouvellePalette.getCouleur(2).getPoids());
		assertEquals(100, nouvellePalette.getCouleur(2).getGris());
		assertEquals(1, nouvellePalette.getCouleur(3).getPoids());
		assertEquals(132, nouvellePalette.getCouleur(3).getGris());
		assertEquals(2, nouvellePalette.getCouleur(4).getPoids());
		assertEquals(164, nouvellePalette.getCouleur(4).getGris());
		assertEquals(1, nouvellePalette.getCouleur(5).getPoids());
		assertEquals(180, nouvellePalette.getCouleur(5).getGris());
		assertEquals(10, nouvellePalette.getCouleur(6).getPoids());
		assertEquals(255, nouvellePalette.getCouleur(6).getGris());
	}

	@Test
	public void testGetoldGrisToNewGris() {
		assertEquals(10, (int) oldGrisToNewGris.get(0));
		assertEquals(10, (int) oldGrisToNewGris.get(0));
		assertEquals(148, (int) oldGrisToNewGris.get(100));
		assertEquals(148, (int) oldGrisToNewGris.get(132));
		assertEquals(148, (int) oldGrisToNewGris.get(164));
		assertEquals(148, (int) oldGrisToNewGris.get(180));
		assertEquals(255, (int) oldGrisToNewGris.get(255));
	}

	@Test
	public void testTransforme() {
		Integer[][] nouvelleImage = TraitementImage.paletteToImage(image,
				oldGrisToNewGris);
		assertEquals(10, (int) nouvelleImage[0][0]);
		assertEquals(10, (int) nouvelleImage[1][0]);
		assertEquals(148, (int) nouvelleImage[2][0]);
		assertEquals(255, (int) nouvelleImage[3][0]);
		assertEquals(255, (int) nouvelleImage[4][0]);
		assertEquals(10, (int) nouvelleImage[0][1]);
		assertEquals(10, (int) nouvelleImage[1][1]);
		assertEquals(148, (int) nouvelleImage[2][1]);
		assertEquals(255, (int) nouvelleImage[3][1]);
		assertEquals(255, (int) nouvelleImage[4][1]);
		assertEquals(10, (int) nouvelleImage[0][2]);
		assertEquals(10, (int) nouvelleImage[1][2]);
		assertEquals(148, (int) nouvelleImage[2][2]);
		assertEquals(255, (int) nouvelleImage[3][2]);
		assertEquals(255, (int) nouvelleImage[4][2]);
		assertEquals(10, (int) nouvelleImage[0][3]);
		assertEquals(10, (int) nouvelleImage[1][3]);
		assertEquals(148, (int) nouvelleImage[2][3]);
		assertEquals(255, (int) nouvelleImage[3][3]);
		assertEquals(255, (int) nouvelleImage[4][3]);
		assertEquals(10, (int) nouvelleImage[0][4]);
		assertEquals(10, (int) nouvelleImage[1][4]);
		assertEquals(148, (int) nouvelleImage[2][4]);
		assertEquals(255, (int) nouvelleImage[3][4]);
		assertEquals(255, (int) nouvelleImage[4][4]);
	}

}
