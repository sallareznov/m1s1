package heur;

import java.util.Map;
import java.util.Map.Entry;

public class BestFitBinPackSolutionWalker extends BinPackSolutionWalker {

	public BestFitBinPackSolutionWalker(BinPackPartialSolution partialSolution,
			ObjectsEnumeration objectsEnumeration) {
		super(partialSolution, objectsEnumeration);
	}

	@Override
	public void goToNextPartialSolution() {
		final int object = getObjectsEnumeration().next();
		final BinPackPartialSolution partialSolution = getPartialSolution();
		final int objectWeight = partialSolution.getAssociatedProblem()
				.getWeights()[object];
		final Map<Integer, Integer> bins = partialSolution
				.getNumBinsToCapacities();
		int mostFilledBin = -1;
		int mostFilledBinRemainingCapacity = partialSolution
				.getAssociatedProblem().getCapacity() + 1;
		boolean flag = false;
		for (final Entry<Integer, Integer> binEntry : bins.entrySet()) {
			final int currentBinRemainingCapacity = binEntry.getValue();
			if ((currentBinRemainingCapacity >= objectWeight)
					&& (currentBinRemainingCapacity < mostFilledBinRemainingCapacity)) {
				mostFilledBin = binEntry.getKey();
				mostFilledBinRemainingCapacity = binEntry.getValue();
				flag = true;
			}
		}
		if (flag) {
			try {
				getPartialSolution().commitObject(object, mostFilledBin);
				return;
			} catch (FullBinException e) {
				System.out.println("Unreachable exception theorically");
			}

		} else {
			getPartialSolution().addBin();
			incrLastBin();
			try {
				getPartialSolution().commitObject(
						object, getLastBin());
			} catch (FullBinException e) {
				System.out.println("Unreachable exception theorically");
			}
		}
	}

}
