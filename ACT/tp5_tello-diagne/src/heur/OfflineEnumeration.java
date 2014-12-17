package heur;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class OfflineEnumeration implements ObjectsEnumeration {

	private List<Integer> _objects;
	private Iterator<Integer> _objectsIter;

	public OfflineEnumeration(int nbObjects) {
		_objects = new ArrayList<Integer>();
		for (int i = 0 ; i < nbObjects ; i++) {
			_objects.add(i);
		}
		_objectsIter = _objects.iterator();
	}

	@Override
	public boolean hasNext() {
		return _objectsIter.hasNext();
	}

	@Override
	public int next() {
		return _objectsIter.next();
	}

}
