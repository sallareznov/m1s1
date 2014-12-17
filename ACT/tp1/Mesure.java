
public class Mesure {

	/**
	 * tSize[] contient, par ordre croissant, toutes les tailles de donnees pour
	 * lesquelles les temps d'execution des algorithmes seront mesures par l'une
	 * des methodes mesureNomAlgorithme sur l'objet de type Mesure.
	 */
	int tSize[];
	/**
	 * tRep[i] contient le nombre de donnees differentes toutes de taille
	 * tSize[i] sur lequel la moyenne des temps d'executions sera calculee par
	 * l'une des methodes mesureNomAlgorithme sur l'objet de type Mesure.
	 */
	int tRep[];
	/**
	 * tRes[i] contient a l'issue d'une mesure effectuee par une methode
	 * mesureNomAlgorithme le temps moyen d'execution de l'algorithme
	 * NomAlgorithme sur tRep[i] donnees differentes de taille tSize[i] .
	 */
	double tRes[];

	/**************************************************************************
	 ************************************************************************** 
	 **************************** CONSTRUCTEUR ********************************
	 ************************************************************************** 
	 *************************************************************************/

	public Mesure(int[] tSize, int[] tRep) {
		this.tSize = tSize;
		this.tRep = tRep;
		this.tRes = new double[tSize.length];

		for (int i = 0; i < this.tRes.length; i++) {
			this.tRes[i] = 0;
		}

	}

	/**************************************************************************
	 ************************************************************************** 
	 ************************ MESURE DES ALGORITHMES **************************
	 ************************************************************************** 
	 *************************************************************************/

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de rechercheL sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[], pour la recherche de l'element 0 qui
	 * est contenu dans L
	 */

	public void mesureRechercheL() {
		double startTime;
		double totalTime;
		boolean present;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaL();
				/** nouvelle instance */

				startTime = System.nanoTime();
				present = M.rechercheL(0);
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de rechercheT sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[], pour la recherche de l'element 0 qui
	 * est contenu dans T
	 */

	public void mesureRechercheT() {
		double startTime;
		double totalTime;
		boolean present;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaT();
				/** nouvelle instance */

				startTime = System.nanoTime();
				present = M.rechercheT(0);
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de minimumSimpleL sur
	 * les nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureMinimumSimpleL() {
		double startTime;
		double totalTime;
		int min;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaL();
				/** nouvelle instance */

				startTime = System.nanoTime();
				min = M.minimumSimpleL();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de minimumSimpleT sur
	 * les nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureMinimumSimpleT() {
		double startTime;
		double totalTime;
		int min;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaT();
				/** nouvelle instance */

				startTime = System.nanoTime();
				min = M.minimumSimpleT();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de minimumTriL sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureMinimumTriL() {
		double startTime;
		double totalTime;
		int min;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaL();
				/** nouvelle instance */

				startTime = System.nanoTime();
				min = M.minimumTriL();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de minimumTriT sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureMinimumTriT() {
		double startTime;
		double totalTime;
		int min;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaT();
				/** nouvelle instance */

				startTime = System.nanoTime();
				min = M.minimumTriT();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de mystereL sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureMystereL() {
		double startTime;
		double totalTime;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaL();
				/** nouvelle instance */

				startTime = System.nanoTime();
				M.mystereL();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de mystereT sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureMystereT() {
		double startTime;
		double totalTime;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {

				M.aleaT();
				/** nouvelle instance */

				startTime = System.nanoTime();
				M.mystereT();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];

		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de aleaL sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureAleaL() {
		double startTime;
		double totalTime;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {
				startTime = System.nanoTime();
				M.aleaL();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];
		}
	}

	/**
	 * ecrit dans tRes[] les moyennes de temps de calcul de aleaT sur les
	 * nombres contenus dans tRep[] d'executions sur des donnees dont les
	 * tailles sont indiquees dans tSize[]
	 */

	public void mesureAleaT() {
		double startTime;
		double totalTime;

		this.resetRes();

		for (int i = 0; i < this.tSize.length; i++) {

			Methodes M = new Methodes(this.tSize[i]);

			for (int j = 0; j < this.tRep[i]; j++) {
				startTime = System.nanoTime();
				M.aleaT();
				totalTime = (System.nanoTime() - startTime);
				this.tRes[i] = this.tRes[i] + totalTime;
			}
			this.tRes[i] = this.tRes[i] / this.tRep[i];
		}
	}

	/**************************************************************************
	 ************************************************************************** 
	 *********************** FONCTIONS DE REFERENCE ***************************
	 ************************************************************************** 
	 *************************************************************************/

	/**
	 * ecrit dans tRes[] les valeurs de la fonction de reference log n pour les
	 * valeurs de n contenues dans tSize[]
	 */
	public void refLog(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.log(Math.pow(this.tSize[i], k));
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs de la fonction de reference n^k pour les
	 * valeurs de n contenues dans tSize[]
	 */
	public void refNpK(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.pow(this.tSize[i], k);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs de la fonction de reference n log n pour
	 * les valeurs de n contenues dans tSize[]
	 */
	public void refNlogn() {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.log(this.tSize[i]) * ((double) this.tSize[i]);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs de la fonction de reference exp pour les
	 * valeurs de n contenues dans tSize[]
	 */
	public void refExp() {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.exp(this.tSize[i]);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs de la fonction de reference k^n pour les
	 * valeurs de n contenues dans tSize[]
	 */
	public void refKpN(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.pow(k, this.tSize[i]);
		}
	}

	/**************************************************************************
	 ************************************************************************** 
	 ****************** RAPPORTS ENTRE FONCTIONS DE REFERENCE *****************
	 ************************************************************************** 
	 *************************************************************************/

	/**
	 * ecrit dans tRes[] les valeurs du rapport log(n)/log(n^k) pour les valeurs
	 * de n contenues dans tSize[]
	 */
	public void rapportLogLogK(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.log(this.tSize[i])
					/ Math.log(Math.pow(this.tSize[i], k));
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs du rapport log(n^k)/log(n) pour les valeurs
	 * de n contenues dans tSize[]
	 */
	public void rapportLogKLog(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.log(Math.pow(this.tSize[i], k))
					/ Math.log(this.tSize[i]);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs du rapport (n^epsi)/log(n) pour les valeurs
	 * de n contenues dans tSize[]
	 */
	public void rapportNepsiLog(double epsi) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.pow(this.tSize[i], epsi)
					/ Math.log(this.tSize[i]);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs du rapport log(n)/(n^epsi) pour les valeurs
	 * de n contenues dans tSize[]
	 */
	public void rapportLogNepsi(double epsi) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.log(this.tSize[i])
					/ Math.pow(this.tSize[i], epsi);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs du rapport (2^n)/(n^k) pour les valeurs de
	 * n contenues dans tSize[]
	 */
	public void rapport2pNNpK(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.pow(2, this.tSize[i])
					/ Math.pow(this.tSize[i], k);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs du rapport (n^k)/(2^n) pour les valeurs de
	 * n contenues dans tSize[]
	 */
	public void rapportNpK2pN(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.pow(this.tSize[i], k)
					/ Math.pow(2, this.tSize[i]);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs du rapport (k^n)/(2^n) pour les valeurs de
	 * n contenues dans tSize[]
	 */
	public void rapportKpN2pN(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.pow(k, this.tSize[i])
					/ Math.pow(2, this.tSize[i]);
		}
	}

	/**
	 * ecrit dans tRes[] les valeurs du rapport (2^n)/(k^n) pour les valeurs de
	 * n contenues dans tSize[]
	 */
	public void rapport2pNKpN(double k) {
		for (int i = 0; i < this.tSize.length; i++) {
			this.tRes[i] = Math.pow(2, this.tSize[i])
					/ Math.pow(k, this.tSize[i]);
		}
	}

	/**************************************************************************
	 ************************************************************************** 
	 ************************* RESULTATS DES MESURES **************************
	 ************************************************************************** 
	 *************************************************************************/

	/** remise à 0 du tableau tRes[] */
	public void resetRes() {
		for (int i = 0; i < this.tRes.length; i++) {
			this.tRes[i] = 0;
		}
	}

	/**
	 * retourne une copie du tableau tRes[], pour recuperer les resultats entre
	 * deux appels a des methodes mesureNomAlgorithme ou
	 * refNomFonctionDeReference ou encore rapportNomsFonctions
	 */
	public double[] getRes() {

		double copie[] = new double[this.tRes.length];
		for (int i = 0; i < this.tRes.length; i++) {
			copie[i] = this.tRes[i];
		}
		return copie;
	}

	/**
	 * retourne une copie du tableau tRes[] dont chaque element a ete multiplie
	 * par le facteur factor
	 */
	public double[] scaledRes(double factor) {
		double[] tmp = new double[this.tRes.length];

		for (int i = 0; i < this.tRes.length; i++) {
			tmp[i] = factor * this.tRes[i];
		}
		return tmp;
	}

	/**
	 * affiche les valeurs contenues dans le tableau a deux dimension res en
	 * faisant preceder chaque ligne de la taille de donnee contenue dans
	 * tSize[]. Les tableaux res[j] pour j verifiant 0 <= j < res.length sont
	 * ainsi affiches en colonnes successives apres la colonne tSize[].
	 */
	public void output(double[][] res) {

		for (int i = 0; i < res[0].length; i++) {
			System.out.print("" + this.tSize[i]);
			for (int j = 0; j < res.length; j++) {
				System.out.print(" " + res[j][i]);
			}
			System.out.print("\n");
		}

	}

	/**************************************************************************
	 ************************************************************************** 
	 ********************************* MAIN ***********************************
	 ************************************************************************** 
	 *************************************************************************/

	public static void main(String[] arg) throws Exception {

		if (arg.length < 1) {
			System.out.println("toto !");
		} else {
			int choix = Integer.parseInt(arg[0]);
			
			int sizes[] = { 2, 10, 20, 30, 40, 50, 100, 150, 200, 300, 400,
					500, 1000, 1500, 2000, 5000, 10000, 25000, 50000,
					75000, 100000, 250000, 500000 };

			switch (choix) {
			case 0:
				/** Exemple */
				
				int rep0[] = { 100, 100, 100, 100, 100, 100, 200, 100, 100,
						200, 100, 100, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
				double scale0[] = { 200, 300, 400, 500, 600 };

				int nbCourbe0 = scale0.length + 1;
				double[][] res0 = new double[nbCourbe0][sizes.length];
				Mesure M0 = new Mesure(sizes, rep0);

				M0.mesureAleaT();
				res0[0] = M0.getRes();

				M0.refNpK(1);
				for (int i = 1; i < nbCourbe0; i++) {
					res0[i] = M0.scaledRes(scale0[i - 1]);
				}

				M0.output(res0);

				break;
			case 1:
				int lowRep[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
						3, 3, 3, 3, 3, 3, 3, 3 };
				int highRep[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30 };

				int nbCourbes = 4;
				double[][] res1 = new double[nbCourbes][sizes.length];
				Mesure MlowRep = new Mesure(sizes, lowRep);

				MlowRep.mesureAleaT();
				res1[0] = MlowRep.getRes();
				MlowRep.resetRes();
				MlowRep.mesureAleaL();
				res1[1] = MlowRep.getRes();

				Mesure MhighRep = new Mesure(sizes, highRep);

				MhighRep.mesureAleaT();
				res1[2] = MhighRep.getRes();
				MhighRep.resetRes();
				MhighRep.mesureAleaL();
				res1[3] = MhighRep.getRes();

				MlowRep.output(res1);

				break;

			case 2:
				int rep11[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
						3, 3, 3, 3, 3, 3, 3, 3 };
				int rep12[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30 };

				int nbCourbe1 = 4;
				double[][] res2 = new double[nbCourbe1][sizes.length];
				Mesure M11 = new Mesure(sizes, rep11);

				M11.mesureRechercheT();
				res2[0] = M11.getRes();
				M11.resetRes();
				M11.mesureRechercheL();
				res2[1] = M11.getRes();

				Mesure M12 = new Mesure(sizes, rep12);

				M12.mesureRechercheT();
				res2[2] = M12.getRes();
				M12.resetRes();
				M12.mesureRechercheL();
				res2[3] = M12.getRes();

				M11.output(res2);

				break;
				case 3:

				int repFaible[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
						3, 3, 3, 3, 3, 3, 3, 3 };
				int repEleve[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30 };

				double[][] res3 = new double[4][sizes.length];
				Mesure M31 = new Mesure(sizes, repFaible);

				M31.mesureMinimumSimpleT();
				res3[0] = M31.getRes();
				M31.resetRes();
				M31.mesureMinimumSimpleL();
				res3[1] = M31.getRes();

				Mesure M32 = new Mesure(sizes, repEleve);

				M32.mesureMinimumTriT();
				res3[2] = M32.getRes();
				M32.resetRes();
				M32.mesureMinimumTriL();
				res3[3] = M32.getRes();

				M31.output(res3);

				break;

				case 4:
				int sizesRef[] = { 2, 4, 6, 8, 10, 12, 14};
				int repRef[] = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30 };
				double scaleRef[] = { 200, 300, 400, 500, 600 };
				double[][] res4 = new double[5][sizesRef.length];

				Mesure MRef = new Mesure(sizesRef, repRef);

				MRef.refLog(1);
				res4[0] = MRef.getRes();
				MRef.resetRes();
				MRef.refNpK(1);
				res4[1] = MRef.getRes();
				MRef.resetRes();
				MRef.refNlogn();
				res4[2] = MRef.getRes();
				MRef.resetRes();
				MRef.refExp();
				res4[3] = MRef.getRes();
				MRef.resetRes();
				MRef.refKpN(1);
				res4[4] = MRef.getRes();

				MRef.output(res4);
				break;

				case 5:
				double[] v_epsilon = {2, 1, 0.5, 0.2, 0.1};
				int[] rep5 = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30 };
				Mesure M5 = new Mesure(sizes, rep5);
				double[][] res5 = new double[v_epsilon.length][sizes.length];

				for (int i = 0 ; i < v_epsilon.length ; i++) {
					M5.rapportLogNepsi(v_epsilon[i]);
					res5[i] = M5.getRes();
					M5.resetRes();
				}
				
				M5.output(res5);
				break;

				case 6:
				int[] sizes6 = {1, 2, 3, 4, 5};
				double[] v_k = {2, 4, 6, 8, 10};
				int[] rep6 = { 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
						30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30 };
				Mesure M6 = new Mesure(sizes6, rep6);
				double[][] res6 = new double[v_k.length][sizes.length];
								
				for (int i = 0 ; i < v_k.length ; i++) {
					M6.rapportNpK2pN(v_k[i]);
					res6[i] = M6.getRes();
					M6.resetRes();
				}
				
				M6.output(res6);

				case 7:
				int sizesRef2[] = { 2, 4, 6, 8, 10, 12, 14};
				int repRef2[] = {1, 1, 1, 1, 1, 1, 1};
				//double scaleRef2[] = { 200, 300, 400, 500, 600 };
				double[][] resRef = new double[2][sizesRef2.length];

				Mesure MRef2 = new Mesure(sizesRef2, repRef2);

				MRef2.mesureAleaT();
				resRef[0] = MRef2.getRes();
				MRef2.resetRes();
				MRef2.refNpK(2);
				resRef[1] = MRef2.getRes();

				MRef2.output(resRef);

			default:
				break;

			}
		}
	}
}
