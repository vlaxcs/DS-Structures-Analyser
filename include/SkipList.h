#pragma once

#include "DataStructure.h"

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

	void insert(int key);
	void erase(int key);
	[[nodiscard]] bool search(int key) const;
	void Print() const;
	void Clear();

	~SkipList();
};
