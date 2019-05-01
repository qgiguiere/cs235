template<class T>
class Node {
public:

	T data;
	Node<T>* next;

	Node(T value, Node<T>* n = NULL) {
		data = value;
		next = n;
	}

	T getData(){
		return data;
	}

	void setData(T newdata){
		data = newdata;
	}

	Node<T>* getNext(){
		return next;
	}

	void setNext(Node<T>* n){
		next = n;
	}
};