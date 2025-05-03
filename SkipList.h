#pragma once

namespace SkipLists {

	struct Node {
		int key;
		Node** forward;
		Node(int key, int level);

		~Node();
	};



	class SkipList {
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

		void Insert(int key);
		void Remove(int key);
		bool Contains(int key) const;
		void Print() const;
		void Clear();
	};



}