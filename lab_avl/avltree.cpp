/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "avltree.h"

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
	
	Node* newLeft = t;
	Node* newT = t->right;

	if (newT == NULL) {
		return;
	}
	Node* transfer = newT->left;
	t = newT;
	newT->left = newLeft;
	newLeft->right = transfer;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here

	Node* newRight = t;
	Node* newT = t->left;

	if (newT == NULL) {
		return;
	}
	Node* transfer = newT->right;
	t = newT;
	newT->right = newRight;
	newRight->left = transfer;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
	updateHeights(root);
	
	if (subtree == NULL) {
		return;
	}

	rebalance(subtree->left);
	rebalance(subtree->right);

	if (!isBalanced(subtree)) {
		RotationType rotation = determineRotation(subtree);
		if (rotation == left) {
			rotateLeft(subtree);
		}
		else if (rotation == right) {
			rotateRight(subtree);
		}
		else if (rotation == leftRight) {
			rotateLeftRight(subtree);
		}
		else if (rotation == rightLeft) {
			rotateRightLeft(subtree);
		}
	}

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
	if (subtree == NULL) {
		root = new Node(key, value);
	} else if (key < subtree->key) {
		if (subtree->left == NULL) {
			Node* toInsert = new Node(key, value);
			toInsert->height = 0;
			subtree->left = toInsert;
		}
		else {
			insert(subtree->left, key, value);
		}
	}
	else if (key > subtree->key) {
		if (subtree->right == NULL) {
			Node* toInsert = new Node(key, value);
			toInsert->height = 0;
			subtree->right = toInsert;
		}
		else {
			insert(subtree->right, key, value);
		}
	}
	rebalance(root);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
	if (subtree == NULL) {
		return;
	}
    if (key < subtree->key) {
		remove(subtree->left, key);
    } else if (key > subtree->key) {
		remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
			delete subtree;
			subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
			Node* leftChild = subtree->left;
			Node* rightChild = subtree->right;
			Node* inOrderPre = leftChild->right;
			Node* prev = leftChild;
			if (inOrderPre == NULL) {
				inOrderPre = leftChild;
			}
			else {
				while (inOrderPre->right != NULL) {
					inOrderPre = inOrderPre->right;
					prev = prev->right;
				}
				prev->right = inOrderPre->left;
				inOrderPre->left = leftChild;
			}
			inOrderPre->right = rightChild;
			delete subtree;
			subtree = inOrderPre;
			
        } else {
			Node* leftChild = subtree->left;
			Node* rightChild = subtree->right;
			delete subtree;
			if (leftChild != NULL) {
				subtree = leftChild;
			}
			else {
				subtree = rightChild;
			}
        }
        
    }
	rebalance(root);
}

template <class K, class V>
bool AVLTree<K, V>::isBalanced(Node*& subtree) {
	if (subtree == NULL) {
		return true;
	}
	int balance = getBalance(subtree);
	if (balance < -1 || balance > 1) {
		return false;
	}
	return true;
}

/**
template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findLastUnbalanced(Node*& subtree) {
	if (subtree == NULL) {
		return NULL;
	}

	Node* leftBal = findLastUnbalanced(subtree->left);
	Node* rightBal = findLastUnbalanced(subtree->right);

	if (leftBal != NULL) {
		return leftBal;
	}
	else if (rightBal != NULL) {
		return rightBal;
	}

	bool bal = isBalanced(subtree);
	if (!bal) {
		return subtree;
	}
	return NULL;

}

*/

template <class K, class V>
typename AVLTree<K, V>::RotationType AVLTree<K, V>::determineRotation(Node*& subroot) {
	
	int balance = getBalance(subroot);
	if (balance > 0) {
		if (getBalance(subroot->left) > 0) {
			return right;
		}
		return leftRight;
	}
	else if (balance < 0) {
		if (getBalance(subroot->right) < 0) {
			return left;
		}
	}
	return rightLeft;
}

template <class K, class V>
int AVLTree<K, V>::getBalance(Node*& subroot) {
	return heightOrNeg1(subroot->left) - heightOrNeg1(subroot->right);
}

template <class K, class V>
int AVLTree<K, V>::updateHeights(Node*& subtree) {
	if (subtree == NULL) {
		return -1;
	}

	int leftSide = updateHeights(subtree->left);
	int rightSide = updateHeights(subtree->right);

	int newHeight = 1 + fmax(leftSide, rightSide);
	subtree->height = newHeight;
	return newHeight;
}

/**
template <class K, class V>
AVLTree<K, V>::rotation AVLTree<K, V>::determineRotation(Node*& subtree, int bal) {
	return leftRotate;
}
*/