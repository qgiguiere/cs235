#ifndef STACK_H
#define STACK_H
#include <string>
#include <stack>

#include "Deque.h"

template<typename T>
class Stack {
public:
	Stack(void) {}
	~Stack(void) {}


	void push_back(const T& value) {
        container.push_back(value);
    }

	void pop_back(void) {
        container.pop_back();
    }

	size_t size(void) const {

    }

	size_t size(void) const {

    }

	T& at(size_t index) {

    }

	std::string toString(void) const {

    }

private:
    Deque<T> container(void) {

    }
};
#endif // STACK_H