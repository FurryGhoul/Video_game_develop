#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <iostream>

typedef unsigned int uint;

#define min(a,b) (a<b)? a:b
#define MIN_ARRAY_BLOCK_SIZE 10

template <class T>
class Array
{
public:
	Array();
	Array(uint memSize);
	~Array();

	bool empty()const;
	uint size()const;

	bool insert(uint index, const T& elem);
	bool remove(uint index);

	T& operator[](uint index)const;
	void shrinkToFit();

	void print() const;

	void allocMem(uint memSize);

	T* arrayElems;
	uint memSize;
	uint numElems;
};

//Constructor that inicialice with the minimum array size
template<class T>
Array<T>::Array():arrayElems(NULL){
	memSize = MIN_ARRAY_BLOCK_SIZE;
	numElems = 0;
	allocMem(this->memSize);
}

//Constructor that inicialice with the indicated size
template<class T>
Array<T>::Array(uint memSize) : arrayElems(NULL){
	numElems = 0;
	this->memSize = memSize;
	allocMem(this->memSize);
}

//the destructor eliminates the array
template<class T>
Array<T>::~Array(){
	if (arrayElems != NULL) {
		delete[] arrayElems;
		arrayElems = NULL;
	}
}

//this function is inicialiced when is necessary more space
template<class T>
void Array<T>::allocMem(uint _memSize) {
	
	//First we have to create a new array with the new size
	T* aux_arra = new T[_memSize];

	//We choose the minimum between the new size or the number of elements
	uint newNumElems = min(numElems, _memSize);

	//we copy the elements of the array to the new array
	for (uint i = 0; i < newNumElems; ++i)
	{
		aux_arra[i] = arrayElems[i];
	}

	//We delete the elements of the array
	if (arrayElems != NULL) {
		delete[]arrayElems;
	}

	//We change the pointer of the array to the new array
	arrayElems = aux_arra;
	//we set the new number of elements and the new size
	this->memSize = _memSize;
	this->numElems = newNumElems;
}

//return true if is empty or false if not
template<class T>
bool Array<T>::empty()const {

	if (numElems == 0) {
		return true;
	}
	else {
		return false;
	}
}

//return the number of elements of the array
template<class T>
uint Array<T>::size()const {
	return numElems;
}

template<class T>
bool Array<T>::insert(uint index, const T& elem) {
	//the index is bigger than the space
	if (index > numElems) { return false; }

	//allocating more space if we need it
	if (numElems >= memSize) {
		allocMem(memSize + MIN_ARRAY_BLOCK_SIZE);
	}

	//moving the elements to make space for the new element
	for (uint i = numElems; i > index; i--) {
		arrayElems[i] = arrayElems[i - 1];
	}

	//writting the new element in the position
	arrayElems[index] = elem;
	numElems++;
	return true;
}

template<class T>
bool Array<T>::remove(uint index) {

	//the index is bigger than the space
	if (index >= numElems) { return false; }

	//removing the elements one forward and eliminate the element that we want
	for (uint i = index; i < numElems-1; i++) {
		arrayElems[i] = arrayElems[i + 1];
	}

	numElems--;
	return true;
}

template<class T>
T& Array<T>::operator[](uint index)const {
	return arrayElems[index];
}

template<class T>
void Array<T>::shrinkToFit() {
	//if the num of elements is smaller than the size we reduce the empty sapce 
	if (numElems < memSize) {
		allocMem(numElems);
	}
}

template<class T>
void Array<T>::print() const {
	
	if (empty()) { cout << "Dynamic array empty" << endl; }
	
	else {
		for (uint i = 0; i < numElems; i++) {
			cout << arrayElems[i];
			if (i < numElems - 1) {
				cout << " | ";
			}
		}
		cout << endl;
	}
}
#endif //_ARRAY_H_