package heur;

import java.util.HashMap;
import java.util.Map;

public class BinPackPartialSolution implements PartialSolution {

	private BinPackProblem _associatedProblem;
	private int _nbCommittedObjects;
	private Map<Integer, Integer> _numBinsToCapacities;
	private int[] _affectations;

	public BinPackPartialSolution(BinPackProblem associatedProblem) {
		_associatedProblem = associatedProblem;
		_nbCommittedObjects = 0;
		_numBinsToCapacities = new HashMap<Integer, Integer>();
		_numBinsToCapacities.put(0, _associatedProblem.getCapacity());
		_affectations = new int[_associatedProblem.getNbObjects()];
		for (int i = 0; i < _affectations.length; i++) {
			_affectations[i] = -1;
		}
	}
	
	@Override
	public BinPackProblem getAssociatedProblem() {
		return _associatedProblem;
	}
	
	public Map<Integer, Integer> getNumBinsToCapacities() {
		return _numBinsToCapacities;
	}
	
	public void addBin() {
		_numBinsToCapacities.put(_numBinsToCapacities.size(), _associatedProblem.getCapacity());
	}

	public void commitObject(int numObject, int numBin) throws FullBinException {
		if (!_numBinsToCapacities.containsKey(numBin)) {
			throw new IllegalArgumentException(numBin
					+ ": This bin doesn't exist");
		}
		final int objectWeight = _associatedProblem.getWeights()[numObject];
		if (_affectations[numObject] != -1) {
			throw new IllegalArgumentException(
					"This object has already been committed");
		}
		final int binRemainingCapacity = _numBinsToCapacities.get(numBin);
		if (objectWeight > binRemainingCapacity) {
			throw new FullBinException();
		}
		else {
			_numBinsToCapacities.remove(numBin);
			_numBinsToCapacities.put(numBin, binRemainingCapacity - objectWeight);
			_affectations[numObject] = numBin;
			_nbCommittedObjects++;
		}
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
			System.out.println(i + " [weight = " + _associatedProblem.getWeights()[i] + "] -> " + _affectations[i]);
		}
		System.out.println();
	}

}
