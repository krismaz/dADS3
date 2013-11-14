#ifndef VEBSEARCHTREE_H
#define VEBSEARCHTREE_H

template<class vebTree_t>
class VebSearchTree {
private:
	vebTree_t tree;
public:
	void Insert(unsigned int x) {
		tree.Insert(x);
	}

	void Remove(unsigned int x) {
		tree.Delete(x);
	}

	unsigned int Predecessor(unsigned int x) {
		return tree.Predecessor(x);
	}

	unsigned int Min() {
		return tree.Min();
	}
};

#endif