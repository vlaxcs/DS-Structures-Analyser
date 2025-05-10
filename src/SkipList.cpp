#include "SkipList.h"

#include <cmath>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <random>

using namespace std;
using namespace SkipLists;

Node::Node(int key, int level) {
	this->key = key;
	forward = new Node*[level + 1];
	memset(forward, 0, sizeof(Node*) * (level + 1));
}
Node::~Node() {
	delete[] forward;
}



SkipList::SkipList() : maxLevel(16), p(0.5f), level(0) {
	head = new Node(-1, maxLevel);
}
SkipList::SkipList(int expectedSize) : p(0.5f), level(0) {
	maxLevel = ceil(log(expectedSize) / std::log(p / 2));
	head = new Node(-1, maxLevel);
}
SkipList::SkipList(int maxLevel, float p) : maxLevel(maxLevel), p(p), level(0) {
	head = new Node(-1, maxLevel);
}
SkipList::~SkipList() {
	Clear();
}
void SkipList::Clear() {
	Node* current = head;
	while (current != 0) {
		Node* next = current->forward[0];
		delete current;
		current = next;
	}
}



int SkipList::GetRandomLevel() const {
	float r = (float)rand()/RAND_MAX;
	int level = 0;
	while (r < p && level < maxLevel) {
		level++;
		r = (float)rand()/RAND_MAX;
	}
	return level;
}

void SkipList::Insert(int key) {
	Node* current = head;
	Node* update[maxLevel + 1];

	for(int i = level; i>= 0; i--) {
		while(current->forward[i] != NULL && current->forward[i]->key <= key) {
			current = current->forward[i];
		}
		update[i] = current;
	}


	current = current->forward[0];
	// if(current != NULL && current->key == key) return;

	int randLevel = GetRandomLevel();
	if(randLevel > level) {
		for(int i = level + 1; i < randLevel + 1; i++) {
			update[i] = head;
		}
		level = randLevel;
	}

	Node* n = new Node(key, randLevel);
	for(int i = 0; i <= randLevel; i++) {
		n->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = n;
	}
}
void SkipList::Remove(int key) {
	Node* current = head;

	Node* update[maxLevel + 1];
	memset(update, 0, sizeof(Node*) * (maxLevel + 1));
	for(int i = level; i >= 0; i--) {
		while(current->forward[i] != NULL && current->forward[i]->key < key) {
			current = current->forward[i];
		}
		update[i] = current;
	}

	current = current->forward[0];

	if(current == NULL || current->key != key) return;

	for(int i=0;i<=level;i++) {
		if(update[i]->forward[i] != current)
			break;

		update[i]->forward[i] = current->forward[i];
	}

	while(level>0 && head->forward[level] == NULL) {
		level--;
	}

	delete current;
}

bool SkipList::Contains(int key) const {
	int currentLevel = level;
	Node* current = head;
	while(current != NULL) {
		if(current->key == key) return true;
		while(current->forward[currentLevel] == NULL || current->forward[currentLevel]->key > key) {
			currentLevel--;
			if(currentLevel < 0) return false;
		}
		current = current->forward[currentLevel];
	}
	return false;
}



void SkipList::Print() const {
	for(int i = level; i >= 0; i--) {
		Node* crnt = head->forward[i];
		Node* bottomLevelCrnt = head->forward[0];
		while(crnt != NULL) {
			while(bottomLevelCrnt->key != crnt->key) {
				bottomLevelCrnt = bottomLevelCrnt->forward[0];
				cout << "----";
			}
			cout << std::setfill('-') << std::setw(3) << crnt->key << "-";
			crnt = crnt->forward[i];
			bottomLevelCrnt = bottomLevelCrnt->forward[0];
		}
		while(bottomLevelCrnt != NULL) {
			bottomLevelCrnt = bottomLevelCrnt->forward[0];
			cout << "----";
		}
		cout << endl;
	}
};
