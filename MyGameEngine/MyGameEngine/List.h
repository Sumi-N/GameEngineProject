#pragma once
template <class T> class List
{
public:

	List();
	~List();
	List(const List <T> & data);
	void add(T data);
	List* begin() { return next; }
	List* end() { return nullptr; }
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

private:

	List* next;
	List* prev;
	T data;
};

template <class T> List<T>::List()
{
	next = nullptr;
	prev = nullptr;
}

template <class T> List<T>::List(const List<T> &_list) {
	printf("copy the list: %c, and it's address %p \n", this->data, &(this->data));
	if (_list.next != nullptr) {
		List(_list.next);
	}
	this.data = _list.data;
}

template <class T> List<T>::~List()
{
	printf("delete the list: %c, and it's address %p \n",this->data, &(this->data));
	delete next;
}

template <class T> void List<T>::add(T _data)
{
	//If this is the latest node, then add _data
	if (next == nullptr) {
		next = new List<T>();
		next->prev = this;
		next->data = _data;
		return;
	}
	//If this is "not" the last node, then do recursion
	next->add(_data);
	return;
}


