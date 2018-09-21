#pragma once
#include <iostream>
template <class T> class List
{
public:

	List();
	~List();
	List(const List <T> & data);
	List& operator=(List&);
	bool operator==(const List&);

	void add(T _data);
	void kill(T _data);

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
		bool operator==(Iterator itr) { if (itr.iter == this->iter) { return true; } else { return false; } }
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
	printf("copy constractor for the list is called \n");
	
	const List<T>* curr = &_list;
	List<T>* now = this;
	prev = nullptr;

	List<T>* tmp;

	while (curr) {
		tmp = new List<T>();
		tmp->data = curr->data;
		now ->next = tmp;
		curr = curr->next;
		now = now->next;
	}
}

template <class T> List<T>& List<T>::operator=(List<T> &_list) {
	//printf("\'=\' operand is called \n");

	const List<T>* curr = &_list;
	List<T>* now = this;
	prev = nullptr;

	List<T>* tmp;

	while (curr) {
		tmp = new List<T>();
		tmp->data = curr->data;
		now = tmp;
		curr = curr->next;
		now = now->next;
	}

	return *this;
}

template <class T> bool List<T>::operator==(const List<T> &_list) {
	const List<T>* curr = &_list;
	List<T>* now = this;
	while(curr) {
		if (now->data != curr->data) {
			return false;
		}
		curr = curr->next;
		now = now->next;
	}
	return true;
}

template <class T> List<T>::~List()
{
	//printf("delete the list: %c, and it's address %p \n",this->data, &(this->data));
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

template <class T> void List<T>::kill(T _data)
{
	if (next == nullptr) {
		printf("there wasn't the node to kill\n");
		return;
	}
	if (next->data == _data) {
		List<T>* targetnode = next;
		next = next->next;
		delete targetnode;
		printf("succesfully deleted the node\n");
	}
	else {
		next->kill(_data);
	}
}


