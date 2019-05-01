#ifndef DEQUE_H
#define DEQUE_H
#include <string>

#include "DequeInterface.h"

template<typename T>
class Deque : public DequeInterface<T> {
public:
	Deque(void) {
		capacity(DEFAULT_CAPACITY)
        num_items(0)
        front_index(0)
        rear_index(DEFAULT_CAPACITY - 1)
        the_data(new T[DEFAULT_CAPACITY]) {}
	}
	~Deque(void) {}

	/** Insert item at front of deque */
	void push_front(const T& value) {
    	// Determine if the capacity needs to be increased.
    	if (num_items == capacity) {
        	reallocate();
    	}
    	num_items++;
		rear_index = (rear_index + 1) % capacity;
		the_data[rear_index] = value;
	}

	/** Insert item at rear of deque */
	void push_back(const T& value) {
    	// Determine if the capacity needs to be increased.
    	if (num_items == capacity) {
        	reallocate();
    	}
    	num_items++;
		rear_index = (rear_index + 1) % capacity;
		the_data[rear_index] = value;
	}

	/** Remove the front item of the deque */
	void pop_front(void) {
		offset++;
    	if (offset == DEFAULT_CAPACITY) {
        	delete[] the_data.front();
        	the_data.pop_front();
        	offset = 0;
   		}
    	num_items--;
	}

	/** Remove the rear item of the deque */
	void pop_back(void) {
		num_items--;
   		front_index = (front_index + 1) % capacity;
   		return;
	}

	/** Return the front item of the deque (Do not remove) */
	T& front(void) {}

	/** Return the rear item of the deque (Do not remove) */
	T& back(void) {}

	/** Return the number of items in the deque */
	size_t size(void) const {
		return num_items;
	}

	/** Return true if deque is empty */
	bool empty(void) const {}

	/** Return item in deque at index (0 based) */
	T& at(size_t index) {}

	/** Return the deque items */
	std::string toString(void) const {}

	T& deque<T>::operator[](size_t i) {
   		if (i >= num_items) {
			throw std::out_of_range("Invalid index deque::operator[]");
		}
		else if (i >= (capacity - front_index)) {
			data_index = i - (capacity - front_index);
		}
		else {
			data_index = front_index + i;
		}
		return the_data[data_index];
	}

private:
    size_t capacity()
    size_t num_items()
    size_t front_index()
    size_t rear_index()
    T* the_data()
    void reallocate() {
		size_t new_capacity = 2 * capacity;
   		Item_Type* new_data = new T[new_capacity];
   		size_t j = front_index;
   		for (size_t i = 0; i < num_items; i++) {
      		new_data[i] = the_data[j];
      		j = (j + 1) % capacity;
   		}
   		front_index = 0;
   		rear_index = num_items - 1;
   		capacity = new_capacity;
   		std::swap(the_data, new_data);
   		delete[] new_data;
	}

};
#endif // DEQUE_H