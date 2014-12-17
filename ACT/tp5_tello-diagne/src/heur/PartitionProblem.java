package heur;

public class PartitionProblem implements Problem {
	
	private int _nbObjects;
	private int[] _integers;
	
	public PartitionProblem(int nbObjects, int[] integers) {
		_nbObjects = nbObjects;
		_integers = integers;
	}
	
	public int getNbObjects() {
		return _nbObjects;
	}
	
	public int[] getIntegers() {
		return _integers;
	}
	
	public int sumIntegers() {
		int cpt = 0;
		for (int i = 0 ; i < _integers.length ; i++) {
			cpt += _integers[i];
		}
		return cpt;
	}

	@Override
	public void display() {
		System.out.println("nbObjects = " + _nbObjects);
		System.out.print("integers =");
		for (int i = 0 ; i < _integers.length ; i++) {
			System.out.print(" " + _integers[i]);
		}
		System.out.println();
	}

}
