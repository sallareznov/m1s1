package heur;

public abstract class BinPackSolutionWalker extends SolutionWalker {
	
	private int _lastBin;

	public BinPackSolutionWalker(BinPackPartialSolution partialSolution,
			ObjectsEnumeration objectsEnumeration) {
		super(partialSolution, objectsEnumeration);
		_lastBin = 0;
	}
	
	@Override
	public BinPackPartialSolution getPartialSolution() {
		return (BinPackPartialSolution) super.getPartialSolution();
	}
	
	@Override
	public abstract void goToNextPartialSolution();
	
	public int getLastBin() {
		return _lastBin;
	}
	
	public void incrLastBin() {
		_lastBin++;
	}

}
