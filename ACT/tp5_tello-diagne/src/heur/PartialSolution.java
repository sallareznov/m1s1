package heur;

public interface PartialSolution {
	
	Problem getAssociatedProblem();
	
	boolean isComplete();
	
	void display();

}
