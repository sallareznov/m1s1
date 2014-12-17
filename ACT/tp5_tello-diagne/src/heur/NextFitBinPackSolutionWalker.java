package heur;

public class NextFitBinPackSolutionWalker extends BinPackSolutionWalker {

	public NextFitBinPackSolutionWalker(BinPackPartialSolution partialSolution,
			ObjectsEnumeration objectsEnumeration) {
		super(partialSolution, objectsEnumeration);
	}

	@Override
	public void goToNextPartialSolution() {
		final int object = getObjectsEnumeration().next();
		try {
			getPartialSolution().commitObject(object, getLastBin());
		}
		catch (FullBinException e) {
			getPartialSolution().addBin();
			incrLastBin();
			try {
				getPartialSolution().commitObject(object, getLastBin());
			} catch (FullBinException e1) {
				System.err.println("Unreachable exception theorically");
			}
		}
	}

}
