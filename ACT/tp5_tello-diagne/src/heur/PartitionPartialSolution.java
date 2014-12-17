package heur;

public class PartitionPartialSolution implements PartialSolution {
	
	private PartitionProblem _associatedProblem;
	private int _nbCommittedObjects;
	private int[] _affectations;
	
	public PartitionPartialSolution(PartitionProblem associatedProblem) {
		_associatedProblem = associatedProblem;
		_nbCommittedObjects = 0;
		_affectations = new int[_associatedProblem.getNbObjects()];
		for (int i = 0; i < _affectations.length; i++) {
			_affectations[i] = -1;
		}
	}
	
	@Override
	public PartitionProblem getAssociatedProblem() {
		return _associatedProblem;
	}

	@Override
	public boolean isComplete() {
		return (_nbCommittedObjects == _associatedProblem.getNbObjects());
	}

	@Override
	public void display() {
		System.out.println("nbCommittedObjects = " + _nbCommittedObjects);
		System.out.println("affectations : ");
		for (int i = 0 ; i < _affectations.length ; i++) {
			System.out.println(i + " [weight = " + _associatedProblem.getIntegers()[i] + "] -> " + _affectations[i]);
		}
		System.out.println();
	}

}