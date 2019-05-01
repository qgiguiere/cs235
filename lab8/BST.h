#ifndef BST_H
#define BST_H
#include <string>
#include "BSTInterface.h"

using namespace std;

template<typename T>
class BST : public BSTInterface<T> {
private:
	struct Node {
		Node(T newData, Node* newLeft, Node* newRight) {
			data = newData;
			left = newLeft;
			right = newRight;
		}
		T data;
		Node* left;
		Node* right;
	};
	Node* root;

	void swap(Node*& first, Node*& second) {
		Node* temp = new Node(first->data, NULL, NULL);
		first->data = second->data;
		second->data = temp->data;
		delete temp;
	}

	bool add(const T& newNode, Node*& newRoot);

	bool remove(const T& oldNode, Node*& theRoot);

	bool print(Node* newRoot, int level, stringstream& output) const;

	size_t sizeTree(const Node* theRoot) const {
		if (theRoot == NULL) {
			return 0;
		}
		else {
			return 1 + sizeTree(theRoot->left) + sizeTree(theRoot->right);
		}
	}
	
	void clear(Node* theRoot) {
		if (theRoot != NULL) {
			if (theRoot->left != NULL) {
				clear(theRoot->left);
			}
			if (theRoot->right != NULL) {
				clear(theRoot->right);
			}
			delete theRoot;
		}
	}

	string found(T value, const Node* theRoot) const {
		if (theRoot == NULL) {
			return "not found";
		}
		else if (theRoot->data == value) {
			return "found";
		}
		else if (value < theRoot->data) {
			return found(value, theRoot->left);
		}
		else {
			return found(value, theRoot->right);
		}
	}

public:
	BST(void) {
		root = NULL;
	}
	virtual ~BST(void) {
		clearTree();
	}

	virtual bool addNode(const T& newNode)  {
		return add(newNode, root);
	}

	virtual bool removeNode(const T& oldNode) {
		return remove(oldNode, root);
	}

	virtual bool clearTree() {
		clear(root);
		root = NULL;
		return true;
	}

	virtual std::string toString() const {
		if (root == NULL) {
			return " empty";
		}
		stringstream output;
		int level = 1;
		output << endl << "  " << level << ":";
		while (print(root, level, output)) {
			output << endl << "  " << ++level << ":";
		}
		return output.str();
	}

	friend ostream& operator<< (ostream& os, const BST& myBST) {
		os << myBST.toString();
		return os;
	}

	size_t size() const {
		return sizeTree(root);
	}
	
	std::string find(const T& value) const  {
		return found(value, root);
	}
};

template <typename T> bool BST<T>::add(const T& newNode, Node*& newRoot) {
	if (newRoot == NULL) {
		newRoot = new Node(newNode, NULL, NULL);
		return true;
	}
	else if (newRoot->data == newNode) {
		return false;
	}
	else if (newNode < newRoot->data) {
		return add(newNode, newRoot->left);
	}
	else {
		return add(newNode, newRoot->right);
	}
}

template <typename T> bool BST<T>::remove(const T& oldNode, Node*& theRoot) {
	if (theRoot == NULL) {
		return false;
	}
	else if (theRoot->data == oldNode) {
		Node* currentNode = theRoot;
		if (theRoot->left == NULL) {
			theRoot = theRoot->right;
			delete currentNode;
		}
		else {
			Node* previousNode = currentNode;
			currentNode = currentNode->left;
			while (currentNode->right != NULL) {
				previousNode = currentNode;
				currentNode = currentNode->right;
			}
			if (previousNode != theRoot) {
				previousNode->right = currentNode->left;
			}
			else {
				theRoot->left = currentNode->left;
			}
			swap(theRoot, currentNode);
			delete currentNode;
		}
		return true;
	}
	else if (oldNode < theRoot->data) {
		return remove(oldNode, theRoot->left);
	}
	else {
		return remove(oldNode, theRoot->right);
	}
}


template<typename T> bool BST<T>::print(Node* newRoot, int level, stringstream& output) const {
	if (newRoot == NULL) {
		return false;
	}
	if (level == 1) {
		output << " " << newRoot->data;
		if ((newRoot->left != NULL) || (newRoot->right != NULL)) {
			return true;
		}
		else {
			return false;
		}
	}
	if ((level == 2) && newRoot->left == NULL && newRoot->right != NULL) {
		output << " _";
	}
	bool left = print(newRoot->left, level - 1, output);
	bool right = print(newRoot->right, level - 1, output);
	if ((level == 2) && newRoot->left != NULL && newRoot->right == NULL) {
		output << " _";
	}
	return left || right;
}


#endif //BST_H