#ifndef MYARRAY_H
#define MYARRAY_H
#define MAX_ARRAY_SIZE	1000
using std::ostream;
using std::ostringstream;

template<typename T>
class MyArray {
private:
	size_t m_size;
	T* m_array;
public:
	MyArray(const size_t maxSize) : m_size(0) { m_array = (T*)malloc(maxSize * sizeof(T)); }
	void push_back(T item) { m_array[m_size++] = item; }

	class Iterator {
	private:
		size_t mi_index;
		size_t mi_size;
		T* mi_aptr;
	public:
		Iterator(T* array, size_t size, size_t index) : mi_aptr(array), mi_size(size), mi_index(index) { }
		// not-equal
		bool operator!= (const Iterator& other) const {
			if (mi_index == other.mi_index) {
				return false;
			}
			return true;
		} 
		// pre-increment ++
		Iterator& operator++ () {
			++mi_index;
			//return *this; 
		} 
		// dereference
		T& operator*() const { return mi_aptr[mi_index]; }   
		std::string toString() const {
			ostringstream out;
			out << "size=" << mi_size << " index=" << mi_index;
			return out.str();
		}
		friend std::ostream& operator<< (std::ostream& os, const Iterator& iter) {
			os << iter.toString();
			return os;
		}
	};
	// pointer to first element 
	Iterator begin() { return MyArray<T>::Iterator(m_array, m_size, 0); }   
	// pointer AFTER last element
	Iterator end() { return MyArray<T>::Iterator(m_array, m_size, m_size); } 

	std::string toString() const {
		ostringstream out;
		int numElements = 0;
		for (int i = 0; i < m_size; i++) {
			out << m_array[i] << " ";
			numElements++;
			if (numElements == 10) {
				out << std::endl;
				numElements = 0;
			}
		}
		return out.str();
	}
	friend std::ostream& operator<< (std::ostream& os, const MyArray<T>& myArray) {
		os << myArray.toString();
		return os;
	}
	~MyArray() {
		free(m_array);
	}
};
#endif //MYARRAY_H