#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>

#include "Deque.h"

template<typename T>
class Vector {
public:
	Vector(size_t newData) {
		new container(newData);
	}
	~Vector(void) {}


	void push_back(const T& value) {
        container.push_back(value);
    }

	void pop_back(void) {
        container.pop_back();
    }

	T& back(void) {

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
#endif // VECTOR_H