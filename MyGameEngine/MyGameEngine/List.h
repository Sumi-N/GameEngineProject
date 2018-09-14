#pragma once
template <class T> class List
{
public:

	T& getDate() { return data; }
	List* getNext() { return next; }

	class Iterator {
	private:
		List* iter;
	public:
		void operator++(int){ iter = (iter->getNext()); }
		T& operator*() { return iter->getDate(); }
		void operator=(List* ptr) { iter = ptr; }
		bool operator!=(List* ptr) { return iter != ptr; }
	};

	List();
	~List();
	void add(T data);
	List* begin() { return this; }
	List* end() { return NULL; }

private:

	List * next;
	List* prev;
	T data;

	List(List<T>* prev, T data);
};

template <class T> List<T>::List()
{
	data = NULL;
	next = NULL;
	prev = NULL;
}

template <class T> List<T>::List(List<T>* _prev, T _data) {
	data = _data;
	next = NULL;
	prev = _prev;
}


template <class T> List<T>::~List()
{
	delete next;
	printf("the linked-list: %p is deleting \n", &(this->data));
}

template <class T> void List<T>::add(T _data)
{
	//If this is the first node
	if (data == NULL) {
		data = _data;
		return;
	}
	//If this is the latest node, then add _data
	if (next == NULL) {
		next = new List<T>(this, _data);
		return;
	}
	//If this is "not" the last node, then do recursion
	next->add(_data);
	return;
}


