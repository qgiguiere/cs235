#ifndef STATION_H
#define STATION_H
#include <string>

#include "Vector.h"
#include "Queue.h"
#include "Stack.h"

template<typename T>
class Station {
public:
	Station(T newCar) {
        this->turntableCar = newCar;
    }
	~Station(void) {}

	string addCar(const T& value) {

    }
	string removeCar(void) {}
	string topCar(void) {}
    string addStack(void) {}
    string removeStack(void) {}
    string topStack(void) {}
    string sizeStack(void) {}
    string addQueue(void) {}
    string removeQueue(void) {}
    string topQueue(void) {}
    string sizeQueue(void) {}
    string find(T) {}
	std::string toString(void) const {}

private:
    Vector<T> train(void) 
    Stack<T> stack(void) 
    Queue<T> queue(void) 
    T turnTableCar(void) 
    T* the_data(void) 
    bool empty(void) 

};
#endif // STATION_H