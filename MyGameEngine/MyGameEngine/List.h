#pragma once
#include <iostream>
#include <assert.h>

template <class T> class Node
{
public:
	T data;
	Node* next;
	Node(T _data) {
		this->data = _data;
	}

	~Node() {
		if (std::is_fundamental<T>::value) {

		}
		else {
			delete data;
		}
	}	
};

template <class T> class List
{
private:
	int size;
	Node<T> *head;

public:

	List() {
		head = nullptr;
		size = 0;
	};
	~List() {
		if (head == nullptr) 
			return;

		Node<T> * curre = head;
		Node<T> * temp;

		while (curre->next != nullptr) {
			temp = curre;
			curre = temp->next;
			delete temp;
		}
		delete curre;
	}

	void add(T data) {
		if (head == nullptr) {
			head = new Node<T>(data);
			size++;
			return;
		}
		else {
			Node<T> *curre = head;
			while (curre->next != nullptr) {
				curre = curre->next;
			}

			curre->next = new Node<T>(data);
			size++;
		}
	}

	bool remove(T data) {
		Node<T> *curre = head;
		Node<T> *prev = nullptr;
		int count = 0;
		while (curre != nullptr) {
			if (curre->data == data) {
				if (count == size-1) {
					prev->next = nullptr;
					delete curre;
					size--;
					return true;
				}
				Node<T> *tmp = curre->next;
				curre->next = curre->next->next;
				size--;
				delete tmp;
				return true;
			}
			prev = curre;
			curre = curre->next;
			count++;
		}
		assert(false);
		return false;
	}

	T get(int i) {
		int count = 0;
		Node<T> *curre = head;
		while (count != i && curre !=nullptr) {
			curre = curre->next;
			count++;
		}
		return curre->data;
	}

	int length() {
		return this->size;
	}
};

