#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <queue>

#include "Deque.h"

template<typename T>
class Queue
{
public:
	Queue(void) {}
	~Queue(void) {}


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
    Deque<T> container(void)
    
};
#endif // QUEUE_H