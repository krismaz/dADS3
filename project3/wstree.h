#ifndef WSTREE_H
#define WSTREE_H

#include "boost/intrusive/rbtree.hpp"
#include "boost/intrusive/list.hpp"

using namespace boost::intrusive;

inline size_t double_shift(size_t i)
{
    return 1 << (1 << i);
}

class WSNode:public set_base_hook <>, public list_base_hook <> {
  public:
    int key;

    WSNode(int k):key(k) {
    } friend bool operator<(const WSNode & a, const WSNode & b) {
	return a.key < b.key;
    }
    friend bool operator>(const WSNode & a, const WSNode & b) {
	return a.key > b.key;
    }
    friend bool operator==(const WSNode & a, const WSNode & b) {
	return a.key == b.key;
    }

    friend bool operator<(const WSNode & a, const int &b) {
	return a.key < b;
    }
    friend bool operator>(const WSNode & a, const int &b) {
	return a.key > b;
    }
    friend bool operator==(const WSNode & a, const int &b) {
	return a.key == b;
    }
};

class WSTree {
  private:
    rbtree < WSNode > trees[10];
    boost::intrusive::list < WSNode > lists[10];
    size_t max_tree;
  public:
    void Insert(int);
    void Remove(int);
    bool Search(int);
    WSTree():max_tree(10) {
    } void PrintSizes() {
	for (int i = 0; i < max_tree; i++) {
	    std::cout << i << " - " << trees[i].size() << std::endl;
	}
    }
};

void WSTree::Insert(int i)
{
    for (int j = 0; j < max_tree; j++) {
	if (trees[j].size() < double_shift(j)) {
	    WSNode *node = new WSNode(i);
	    trees[j].insert_unique(*node);
	    lists[j].push_back(*node);
	    Search(i);		//TODO:Optimize!
	    return;
	}
    }
}

void WSTree::Remove(int i)
{
    for (int j = 0; j < max_tree; j++) {
	auto it = trees[j].find(i);
	if (it != trees[j].end()) {
	    trees[j].erase(*it);
	    lists[j].remove(*it);
	    delete & (*it);

	    for (int k = j + 1; k < max_tree; k++) {
		if (trees[k].size() == 0) {
		    break;
		}
		auto it2 = lists[k].begin();
		trees[k].erase(*it2);
		lists[k].remove(*it2);
		trees[k - 1].insert_unique(*it2);
		lists[k - 1].push_back(*it2);
	    }
	    return;
	}
    }
}

bool WSTree::Search(int i)
{
    for (int j = 0; j < max_tree; j++) {
	auto it = trees[j].find(i);
	if (it == trees[j].end()) {
	    continue;
	}
	trees[j].erase(*it);
	lists[j].remove(*it);
	trees[0].insert_unique(*it);
	lists[0].push_back(*it);
	for (int k = 0; k < max_tree; k++) {
	    if (trees[k].size() <= double_shift(k)) {
		break;
	    }
	    auto it2 = lists[k].begin();
	    trees[k].erase(*it);
	    lists[k].remove(*it);
	    trees[k + 1].insert_unique(*it);
	    lists[k + 1].push_back(*it);
	}
	return true;
    }
    return false;
}


#endif