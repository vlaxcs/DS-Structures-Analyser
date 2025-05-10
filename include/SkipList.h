#pragma once

#include "DataStructure.h"

namespace SkipLists {

	struct Node {
		int key;
		Node** forward;
		Node(int key, int level);

		~Node();
	};



	class SkipList : public DataStructure {
		int maxLevel;
		float p;
		int level;
		Node* head;

		int GetRandomLevel() const;

	public:
		SkipList();
		SkipList(int expectedSize);
		SkipList(int maxLevel, float p);
		~SkipList();

		void insert(int key);
		void erase(int key);
		bool search(int key) const;
		void Print() const;
		void Clear();
	};



}