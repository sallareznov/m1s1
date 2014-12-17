package heur;

public abstract class SolutionWalker {
	
	private PartialSolution _partialSolution;
	private ObjectsEnumeration _objectsEnumeration;
	
	public SolutionWalker(PartialSolution partialSolution, ObjectsEnumeration objectsEnumeration) {
		_partialSolution = partialSolution;
		_objectsEnumeration = objectsEnumeration;
	}
	
	public PartialSolution getPartialSolution() {
		return _partialSolution;
	}
	
	public ObjectsEnumeration getObjectsEnumeration() {
		return _objectsEnumeration;
	}
	
	public boolean isTerminated() {
		return _partialSolution.isComplete();
	}
	
	public abstract void goToNextPartialSolution();
	
	public PartialSolution current() {
		return _partialSolution;
	}

}
