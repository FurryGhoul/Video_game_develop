#include <iostream>

using namespace std;
typedef unsigned int uint;


#include "Array.h"
#include "Lists.h"
#include "vec3.h"

template<class T>
void List_to_Array(Array<T>& arr, Lists<T>& list);
template<class T>
void print_array(const Array<T> &arr);

//first number is in the position 0
//Last number is in the position Size-1

int main() {

	/*Lists<int> patata;

	cout << "Inserting number 3" << endl;
	patata.pushFront(3);
	getchar();

	cout << "Inserting number 2" << endl;
	patata.pushFront(2);
	getchar();

	cout << "Inserting number 4" << endl;
	patata.pushBack(4);
	getchar();

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	cout << "Printing Reverse" << endl;
	getchar();
	patata.printReverse();

	cout << "inserting 5 between 2 and 3" << endl;
	patata.insert(1, 5);

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	cout << "Removing number 2" << endl;
	patata.popFront();

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	cout << "Removing number 4" << endl;
	patata.popBack();

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	cout << "total num = " << patata.size() << endl;

	cout << "inserting 4 between 5 and 3" << endl;
	patata.insert(1, 4);
	getchar();

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	cout << "last " << patata.back()<<endl;
	getchar();

	cout << "Inserting number 6" << endl;
	patata.pushFront(6);
	getchar();

	cout << "Inserting number 10" << endl;
	patata.pushFront(10);
	getchar();

	cout << "Inserting number 4" << endl;
	patata.pushBack(4);
	getchar();

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	cout << "Total numbers = " << patata.size() << endl;

	cout << "removing number 6" << endl;
	getchar();
	patata.remove(1);

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	cout << "removing number last 4" << endl;
	getchar();
	patata.remove(patata.size()-1);

	cout << "Total numbers = " << patata.size() << endl;

	cout << "Printing!" << endl;
	getchar();
	patata.print();

	system("pause");

	std::cout << "The output should be:" << std::endl;
	std::cout << "0 1 2 13 12 4 5 6 7 8 9 10 11" << std::endl;
	std::cout << "Could not insert element at index 20" << std::endl;
	std::cout << "Could not remove element at index 20" << std::endl;
	std::cout << std::endl;

	Array<unsigned int> myArray(5);

	for (unsigned int i = 0; i < 11; ++i)
		myArray.insert(i, i);

	myArray.insert(11, 11);

	myArray[3] = 12;

	myArray.insert(3, 13);


	std::cout << "Output:" << std::endl;

	myArray.print();

	const bool inserted = myArray.insert(20, 20);
	if (!inserted) {
		std::cout << "Could not insert element at index 20" << std::endl;
	}

	const bool removed = myArray.remove(20);
	if (!removed) {
		std::cout << "Could not remove element at index 20" << std::endl;
	}*/
	
	Array<int> prova;
	Array<int> loca(4);
	Lists<int> proveta;

	proveta.insert(0, 1);
	proveta.insert(1, 2);
	proveta.insert(2, 3);
	proveta.insert(3, 4);

	cout << "The list" << endl;
	proveta.print();

	prova.insert(0, 5);
	prova.insert(1, 6);
	prova.insert(2, 7);
	prova.insert(3, 8);
	
	cout << "The Array 1" << endl;
	print_array(prova);

	cout << "The array 2" << endl;
	List_to_Array(loca, proveta);
	print_array(loca);


	getchar();

	cout << "The list with a component from the array" << endl;
	proveta.Get_from_Arr(prova,3,3);
	proveta.print();

	cout << "The array with components from the list" << endl;
	List_to_Array(prova, proveta);
	

	print_array(prova);


	system("pause");
	return 0;

}

template<class T>
void List_to_Array(Array<T>& arr, Lists<T>& list) {

	if (arr.numElems > 0) {

		for (int i = 0; i < arr.numElems; i++) {
			arr[i] = list.getValue(i);
		}
	}

	else {
		for (int i = 0; i < arr.memSize; i++) {
			arr.insert(i, list.getValue(i));
		}
	}
	
	
}

template<class T>
void print_array(const Array<T>& arr) {
	
	for (int i = 0; i < arr.numElems; i++) {
		cout<<arr[i]<<"|";
	}
	cout << endl;
}