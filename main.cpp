#include <iostream>

#include "SkipList.h"
#include "SplayTree.h"

using namespace std;

using namespace SkipLists;

int main() {
	srand((unsigned)time(0)); // rand() seed
	SkipList list(3, 0.5);

	list.insert(3);
	list.insert(6);
	list.insert(7);
	list.insert(9);
	list.insert(12);
	list.insert(19);
	list.insert(17);
	list.insert(17); // Cant hold duplicates
	list.insert(26);
	list.insert(21);
	list.insert(25);
	list.Print();

	if(list.search(19)) {
		cout << "Contains 19\n";
	} else {
		cout << "Does not contain 19\n";
	}

	list.erase(19);
	list.Print();

	if(list.search(19)) {
		cout << "Contains 19\n";
	} else {
		cout << "Does not contain 19\n";
	}

	SplayTree ST;
	ST.insert(11);
	ST.insert(69);
	ST.insert(121);
	ST.insert(15);
	ST.insert(12);
	ST.insert(19);
	ST.search(11);

	ST.POT(ST.getRoot());

	// Teste pentru

	// delete pe splay
	// insert, search, delete-uri
	// combo-uri

}