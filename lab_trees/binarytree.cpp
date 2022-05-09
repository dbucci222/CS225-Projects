/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	mirror(root);
	return;
}

/**
 * Private helper function for public mirror() function.
*/
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) const {
	
	if (subRoot == NULL) {
		return;
	}

	mirror(subRoot->left);
	mirror(subRoot->right);

	Node* old_left = subRoot->left;
	Node* old_right = subRoot->right;

	subRoot->left = old_right;
	subRoot->right = old_left;

	return;
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list of output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const {

	InorderTraversal<T> trav(getRoot());
	T prev = T();

	for (auto it = trav.begin(); it != trav.end(); ++it) {
		T compare = (*it)->elem;
		if (compare < prev) {
			return false;
		}
		prev = compare;
	}

	return true;

}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const {
	return isOrderedRecursive(getRoot());
}

/**
 * Primary helper function for isOrderedRecursive().
 * 
 * @return a boolean telling if the tree is properly ordered or not
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* treeNode) const {
	if (treeNode == NULL) {
		return true;
	}
	T element = treeNode->elem;
	bool current = true;

	if (treeNode->left != NULL && treeNode->left->elem > element) {
		current = false;
	}
	if (treeNode->right != NULL && treeNode->right->elem < element) {
		current = false;
	}

	bool left = isOrderedRecursiveLeft(treeNode->left, element);
	bool right = isOrderedRecursiveRight(treeNode->right, element);

	if (!current || !left || !right) {
		return false;
	}

	return true;

}


/**
 * Secondary helper function for isOrderedRecursive(). Checks branches.
 *
 * @return a boolean telling if the tree is properly ordered or not
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursiveRight(Node* treeNode, T thisShouldBeLess) const {
	if (treeNode == NULL) {
		return true;
	}
	T element = treeNode->elem;
	bool current = true;

	if (treeNode->left != NULL && treeNode->left->elem > element) {
		current = false;
	}
	if (treeNode->right != NULL && treeNode->right->elem < element) {
		current = false;
	}

	if (treeNode->elem < thisShouldBeLess) {
		current = false;
	}

	bool left = isOrderedRecursiveRight(treeNode->left, thisShouldBeLess);
	bool right = isOrderedRecursiveRight(treeNode->right, thisShouldBeLess);

	if (!current || !left || !right) {
		return false;
	}

	return true;
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursiveLeft(Node* treeNode, T thisShouldBeGreater) const {
	if (treeNode == NULL) {
		return true;
	}
	T element = treeNode->elem;
	bool current = true;

	if (treeNode->left != NULL && treeNode->left->elem > element) {
		current = false;
	}
	if (treeNode->right != NULL && treeNode->right->elem < element) {
		current = false;
	}

	if (treeNode->elem > thisShouldBeGreater) {
		current = false;
	}

	bool left = isOrderedRecursiveLeft(treeNode->left, thisShouldBeGreater);
	bool right = isOrderedRecursiveLeft(treeNode->right, thisShouldBeGreater);

	if (!current || !left || !right) {
		return false;
	}

	return true;
}