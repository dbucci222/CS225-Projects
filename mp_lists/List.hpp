/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include "List.h"

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
	length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
	return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
	ListNode* current = head_;
	ListNode* next;
	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
	
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
	ListNode * newNode = new ListNode(ndata);
	ListNode* front = head_;

	newNode->prev = NULL;

	if (head_ != NULL) {
		newNode->next = front;
		front->prev = newNode;
		head_ = newNode;
	}
	else { 
		head_ = newNode;
		tail_ = newNode;
	}
	
	
	length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
	ListNode* newNode = new ListNode(ndata);

	newNode->next = NULL;
	newNode->prev = tail_;

	if (tail_ != NULL) {
		tail_->next = newNode;
		tail_ = newNode;
	}
	else {
		tail_ = newNode;
		head_ = newNode;
	}


	length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
	  curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
	ListNode* current = head_;
	while (current != NULL) {
		if (current->next == NULL) {
			break;
		}
		else if (current->next->next == NULL) {
			break;
		}
		ListNode* node1 = current;
		ListNode* prev1 = current->prev;
		ListNode* node2 = current->next;
		ListNode* node3 = current->next->next;
		ListNode* next3 = node3->next;

		if (current == head_) {
			node1->next = next3;
			if (next3 != NULL) {
				next3->prev = node1;
			}
			node3->next = node1;
			node1->prev = node3;
			node2->prev = NULL;
			head_ = node2;

			if (current->next == NULL) {
				current = tail_;
			}
			current = current->next;
			continue;
		}

		node1->next = next3;
		if (next3 != NULL) {
			next3->prev = node1;
		}
		node3->next = node1;
		node1->prev = node3;
		node2->prev = prev1;
		prev1->next = node2;

		if (current->next == NULL) {
			current = tail_;
		}
		current = current->next;
	}
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {

	ListNode* reverseHead = endPoint;
	ListNode* reverseTail = startPoint;
	
	ListNode* postReverse = endPoint->next;
	ListNode* preReverse = startPoint->prev;
	
	ListNode* current = reverseHead;
	
	while (current != reverseTail) {
		ListNode* theNext = current->prev;
		current->next = theNext;
		current = current->next;
	}

	current = reverseHead;
	ListNode* previous = preReverse;

	//I added this
	auto temp = startPoint;
	startPoint = endPoint;
	endPoint = temp;
	
	reverseHead->prev = preReverse;
	if (preReverse != NULL) {
		preReverse->next = reverseHead;
	}
	else {
		head_ = reverseHead;
	}

	reverseTail->next = postReverse;
	if (postReverse != NULL) {
		postReverse->prev = reverseTail;
	}
	else {
		tail_ = reverseTail;
	}

	current = reverseHead;

	while (current != postReverse) {
		if (previous != NULL) {
			current->prev = previous;
			previous = current;
			current = current->next;
		}
		else {
			current->prev = previous;
			previous = current;
			current = current->next;
		}

	}

	std::cout << std::endl;
	
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {

	ListNode* startPoint = head_;
	ListNode* current = head_;
	int i = 1; 

	while (current != NULL) {
		if (i == n) {
			reverse(startPoint, current);
			startPoint = current->next;
			current = current->next;
			i = 1;
			continue;
		}
		else if (current->next == NULL) {
			reverse(startPoint, current);
		}
		current = current->next;
		i++;
	}
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {

	ListNode* current1 = first;
	ListNode* current2 = second;
	ListNode* newHead;

	if (first == NULL && second == NULL) {
		return NULL;
	}
	else if (first == NULL) {
		return second;
	}
	else if (second == NULL) {
		return first;
	}

	if (current1->data < current2->data) {
		newHead = current1;
		current1 = current1->next;
	}
	else {
		newHead = current2;
		current2 = current2->next;
	}

	ListNode* current = newHead;

	while (current != NULL) {
		if (current1 == NULL && current2 != NULL) {
			while (current2 != NULL) {
				current->next = current2;
				current = current->next;
				current2 = current2->next;
			}
			current->next = NULL;
		}
		else if (current1 != NULL && current2 == NULL) {
			while (current1 != NULL) {
				current->next = current1;
				current = current->next;
				current1 = current1->next;
			}
			current->next = NULL;
		} 
		else if (current1->data < current2->data) {
			current->next = current1;
			current1 = current1->next;
		}
		else {
			current->next = current2;
			current2 = current2->next;
		}
		current = current->next;
	}

	current = newHead->next;
	ListNode* previous = newHead;

	while (current != NULL) {
		current->prev = previous;
		previous = previous->next;
		current = current->next;
	}
	
	first = newHead;
	second = NULL;

	return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
	
	if (chainLength == 1) {
		return start;
	}

	int splitPoint = chainLength / 2;

	ListNode* secondHead = split(start, splitPoint);

	start = mergesort(start, splitPoint);
	secondHead = mergesort(secondHead, chainLength - splitPoint);

	return merge(start, secondHead);

}


