/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

#include "quackfun.h"

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s) {
	if (s.empty()) {
		return T();
	}
	if (s.size() == 1) {
		return s.top();
	}
	T top = s.top();
	s.pop();
	T cur_sum = 0;
	if (!s.empty()) {
		cur_sum = top + sum(s);
	}
	s.push(top);
	return cur_sum;

	
	
	// stub return value (0 for primitive types). Change this!
	// Note: T() is the default value for objects, and 0 for
    // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
	stack<char> char_stack;
	bool balanced = true;
	while (!input.empty()) {
		if (input.front() == '[') {
			char_stack.push(input.front());
			input.pop();
		}
		else if (input.front() == ']') {
			if (!char_stack.empty()) {
				char_stack.pop();
				input.pop();
			}
			else {
				balanced = false;
				break;
			}
		}
		else {
			input.pop();
		}
	}

	if (balanced == true && !char_stack.empty()) {
		balanced = false;
	}

	return balanced;

}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
	queue<T> q2;

	int scramble_const = 1;

	while (!q.empty()) {
		for (int i = 0; i < scramble_const; i++) {
			if (q.empty()) {
				break;
			}
			if (scramble_const % 2 == 1) {
				q2.push(q.front());
			}
			else {
				s.push(q.front());
			}
			if (!q.empty()) {
				q.pop();
			}
		}
		while (!s.empty()) {
			q2.push(s.top());
			s.pop();
		}
		scramble_const += 1;
	}

	q2.swap(q);

}
}
