package heur;

import java.util.InputMismatchException;
import java.util.Scanner;

public class OnlineEnumeration implements ObjectsEnumeration {
	
	private Scanner _reader;
	private int _nbNumbersRead;
	private int _nbNumbersToRead;
	
	public OnlineEnumeration(int nbNumbersToRead) {
		_reader = new Scanner(System.in);
		_nbNumbersToRead = nbNumbersToRead;
		_nbNumbersRead = 0;
	}

	@Override
	public boolean hasNext() {
		return (_nbNumbersRead < _nbNumbersToRead);
	}

	@Override
	public int next() {
		try {
			return _reader.nextInt();
		}
		catch (InputMismatchException e) {
			// TODO
			return 0;
		}
		
	}
	
	public void closeReader() {
		_reader.close();
	}

}
