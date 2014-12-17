package heur;

import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class FirstFitBinPackSolutionWalker extends BinPackSolutionWalker {

	public FirstFitBinPackSolutionWalker(
			BinPackPartialSolution partialSolution,
			ObjectsEnumeration objectsEnumeration) {
		super(partialSolution, objectsEnumeration);
	}

	@Override
	public void goToNextPartialSolution() {
		final int object = getObjectsEnumeration().next();
		final Map<Integer, Integer> bins = ((BinPackPartialSolution) getPartialSolution())
				.getNumBinsToCapacities();
		final Set<Integer> binsCapacities = bins.keySet();
		final Iterator<Integer> it = binsCapacities.iterator();
		while (it.hasNext()) {
			try {
				getPartialSolution().commitObject(object, it.next());
				return;
			}
			catch (FullBinException e) {
				continue;
			}
		}
		getPartialSolution().addBin();
		incrLastBin();
		try {
			getPartialSolution().commitObject(object, getLastBin());
		} catch (FullBinException e) {
			System.out.println("Unreachable exception theorically");
		}
	}

}
