package heur;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Solve {

	private static void usage() {
		System.out.println("java heur.Solve <mode> <file>");
		System.out
				.println("<mode> (ON|OFF) specifies which mode you choose to solve your problem");
		System.out
				.println("<file> contains your problem's data (mandatory in the offline mode only");
		System.out.println("Examples : 	- java heur.Solve -on");
		System.out.println("			- java heur.Solve -off bin1data/N3C3W4_G");
	}

	public void onlineMode() {

	}

	public BinPackProblem offlineMode(String filename)
			throws FileNotFoundException {
		final Scanner sc = new Scanner(new File(filename));
		final int nbObjects = sc.nextInt();
		final int capacity = sc.nextInt();
		final int[] objectsWeights = new int[nbObjects];
		for (int i = 0; i < nbObjects; i++) {
			objectsWeights[i] = sc.nextInt();
		}
		sc.close();

		return new BinPackProblem(nbObjects, objectsWeights, capacity);
	}

	public static BinPackSolutionWalker getChosenSolutionWalker(
			HeuristicType heuristicType,
			BinPackPartialSolution partialSolution,
			ObjectsEnumeration enumeration) {
		switch (heuristicType) {
		case NEXT_FIT:
			return new NextFitBinPackSolutionWalker(partialSolution,
					enumeration);
		case FIRST_FIT:
			return new FirstFitBinPackSolutionWalker(partialSolution,
					enumeration);
		default:
			return new BestFitBinPackSolutionWalker(partialSolution,
					enumeration);
		}
	}

	public static void solveAndPrint(BinPackProblem problem,
			HeuristicType heuristicType) {
		final BinPackPartialSolution partialSolution = new BinPackPartialSolution(
				problem);
		final ObjectsEnumeration enumeration = new OfflineEnumeration(
				problem.getNbObjects());
		final BinPackSolutionWalker solutionWalker = getChosenSolutionWalker(heuristicType, partialSolution, enumeration);
		final long startTime = System.currentTimeMillis();
		while (!solutionWalker.isTerminated()) {
			solutionWalker.goToNextPartialSolution();
		}
		partialSolution.display();
		final long executionTime = System.currentTimeMillis() - startTime;
		System.out.println((solutionWalker.getLastBin() + 1) + " bins used !");
		System.out.println("Execution time : " + executionTime
				+ " milliseconds.");
	}

	public static void main(String[] args) {
		if ((args.length < 1)
				|| (("-off".equals(args[0])) && (args.length < 2))) {
			usage();
			return;
		}
		Scanner sc = null;
		try {
			sc = new Scanner(new File(args[1]));
		} catch (FileNotFoundException e) {
			System.err.println("Enter a valid filename");
			return;
		}

		final int nbObjects = sc.nextInt();
		final int capacity = sc.nextInt();
		final int[] objectsWeights = new int[nbObjects];
		for (int i = 0; i < nbObjects; i++) {
			objectsWeights[i] = sc.nextInt();
		}
		sc.close();

		final BinPackProblem problem = new BinPackProblem(nbObjects,
				objectsWeights, capacity);

		System.out.println("************ PROBLEM *************");
		problem.display();
		System.out.println("**********************************");
		System.out.println();

		System.out.println("************* RESULTS *************");
		System.out.println("- NextFit");
		solveAndPrint(problem, HeuristicType.NEXT_FIT);
		System.out.println();
		System.out.println("- FirstFit");
		solveAndPrint(problem, HeuristicType.FIRST_FIT);
		System.out.println();
		System.out.println("- BestFit");
		solveAndPrint(problem, HeuristicType.BEST_FIT);

	}

}
