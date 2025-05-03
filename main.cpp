#include <iostream>

#include "SkipList.h"

using namespace std;

using namespace SkipLists;

int main() {
	srand((unsigned)time(0)); // rand() seed
	SkipList list(3, 0.5);

	list.Insert(3);
	list.Insert(6);
	list.Insert(7);
	list.Insert(9);
	list.Insert(12);
	list.Insert(19);
	list.Insert(17);
	list.Insert(26);
	list.Insert(21);
	list.Insert(25);
	list.Print();

	if(list.Contains(19)) {
		cout << "Contains 19\n";
	} else {
		cout << "Does not contain 19\n";
	}

	list.Remove(19);
	list.Print();

	if(list.Contains(19)) {
		cout << "Contains 19\n";
	} else {
		cout << "Does not contain 19\n";
	}
}