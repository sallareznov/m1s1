package heur;

public class BinPackProblem implements Problem {
	
	private int _nbObjects;
	private int[] _weights;
	private int _capacity;
	
	public BinPackProblem(int nbObjects, int[] weights, int capacity) {
		_nbObjects = nbObjects;
		_weights = weights;
		_capacity = capacity;
	}

	public int getNbObjects() {
		return _nbObjects;
	}

	public int[] getWeights() {
		return _weights;
	}

	public int getCapacity() {
		return _capacity;
	}

	@Override
	public void display() {
		System.out.println("nbObjects = " + _nbObjects);
		System.out.println("capacity of each bin = " + _capacity);
		System.out.print("weights =");
		for (int i = 0 ; i < _weights.length ; i++) {
			System.out.print(" " + _weights[i]);
		}
		System.out.println();
	}

}