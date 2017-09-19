#include <iostream>
#include "Array.h"

using namespace std;
typedef unsigned int uint;


template <class T>
class Lists
{
public:
	Lists();
	~Lists();

	void pushFront(const T& elem);
	void pushBack(const T& elem);
	void popFront();
	void popBack();
	void insert(uint pos, const T& elem);
	void remove(uint pos);

	T front() const;
	T back() const;

	T getValue(uint pos) const;

	bool empty() const;
	uint size() const;
	void clear();

	void print() const;
	void printReverse() const;

	void Get_from_Arr(Array<T>& arr, uint index_1, uint index_2);
	void complete_from_Array(Array<T>& arr);
	
private:
	struct Node {
		T value;
		Node* prev;
		Node* next;
	};

	Node* first;
	Node* last;

	uint numElems;
};


template <class T>
Lists<T>::Lists()
{
	numElems = 0;
	first = nullptr;
	last = nullptr;
}

template <class T>
Lists<T>::~Lists()
{

}

template <class T>
void Lists<T>::pushFront(const T& elem) {

	Node* aux = new Node;

	aux->value = elem;
	aux->next = first;
	aux->prev = nullptr;

	if(numElems>0){
		first->prev = aux;
	}

	if (numElems == 0) { last = aux; }

	first = aux;

	numElems++;
}

template <class T>
void Lists<T>::pushBack(const T& elem) {

	Node* aux = new Node;

	aux->value = elem;
	aux->prev = last;
	aux->next = nullptr;
	last = aux;
	
	if (last->prev) {
		last->prev->next = last;
	}
	
	if (numElems == 0) { first = aux; }

	numElems++;
}

template <class T>
void Lists<T>::popFront() {

	Node* aux = first;
	first = first->next;
	first->prev = nullptr;

	delete aux;

	numElems--;

	if (numElems == 0) { last = nullptr; }
}

template <class T>
void Lists<T>::popBack() {
	if (numElems>0) {
		if (numElems == 0) {
			delete first;
			first = nullptr;
			last = nullptr;
			numElems--;
		}

		else {

			Node* previ = first;
			Node* current = first->next;

			while (current->next != nullptr) {
				previ = current;
				current = current->next;
			}

			delete current;
			last = previ;
			last->next = nullptr;

			numElems--;
		}
	}
}

template <class T>
void Lists<T>::insert(uint pos, const T& elem) {

	if (pos >= 0) {

		if (pos == 0) {
			pushFront(elem);
		}

		else if (pos == numElems) {
			pushBack(elem);
		}

		else {

			Node* previ = first;
			Node* curr = first->next;
			Node* aux = new Node;
			uint counter = 1;

			while (counter != pos) {
				previ = curr;
				curr = curr->next;
				counter++;
			}

			aux->value = elem;
			previ->next = aux;
			aux->prev = previ;
			aux->next = curr;
			curr->prev = aux;

			numElems++;
		}

	}


}

template <class T>
void Lists<T>::remove(uint pos) {

	if (numElems > 0) {

		if (pos == 0) {
			popFront();
		}

		else if (pos == numElems-1) {
			popBack();
		}

		else {

			Node* previ = first;
			Node* curr = first->next;
			Node* aux = new Node;
			uint counter = 1;

			while (counter != pos) {
				previ = curr;
				curr = curr->next;
				counter++;
			}

			aux = curr->next;
			previ->next = aux;
			aux->prev = previ;

			delete curr;

			numElems--;
		}
	}
}

template <class T>
T Lists<T>::front()const {
	return first->value;
}

template <class T>
T Lists<T>::back()const {
	return last->value;
}

template <class T>
T Lists<T>::getValue(uint pos)const {
	if (pos >= 0) {

		if (pos == 0) {
			front();
		}

		else if (pos == numElems) {
			back();
		}

		else {

			Node* previ = first;
			Node* curr = first->next;
			uint counter = 1;

			while (counter != pos) {
				previ = curr;
				curr = curr->next;
				counter++;
			}

			return curr->value;
		}
	}
}

template <class T>
bool Lists<T>::empty() const {

	if (numElems == 0) { return true; }
	else { return false; }
}

template <class T>
uint Lists<T>::size() const {
	return numElems;
}

template <class T>
void Lists<T>::clear() {

	Node* previ = first;
	Node* curr = first->next;

	while (curr->next != nullptr) {
		previ = curr;
		curr = curr->next;
		delete previ->prev;
	}

	delete previ;
	delete curr;
	first = nullptr;
	last = nullptr;
}

template <class T>
void Lists<T>::print()const {

	for (int i = 0; i <= numElems-1; i++) {
		cout << getValue(i);
		if (i < numElems-1) { cout << " | "; }
	}

	cout << endl;
}

template <class T>
void Lists<T>::printReverse()const {

	for (int i = numElems-1; i >= 0; i--) {
		cout << getValue(i);
		if (i >0) { cout << " | "; }
	}
	cout << endl;
}

template<class T>
void Lists<T>::Get_from_Arr(Array<T>& arr,uint index_1,uint index_2) {
	
	insert(index_2, arr.arrayElems[index_1]);

}

template<class T>
void Lists<T>::complete_from_Array(Array<T>& arr){
	
	uint counter = 0;
	Node* aux = first;

	while (counter != arr.numElems) {
		aux->value = arr[counter];
		aux = aux->next;
	}
}


//#endif //LISTS_H