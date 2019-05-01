#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>
#include "SetInterface.h"

using namespace std;

template <class Type>
class NodeWithData {
public:
	NodeWithData(Type value) {
		data = value;
		nextNode = NULL;
	}
	Type data;
	NodeWithData * nextNode;
};

template <class Type>
class Set : public SetInterface<Type> {
public:
	Set() {
		headNode = NULL;
	}
	NodeWithData<Type> * headNode;
	virtual bool inList(Type myValue) {
		NodeWithData<Type> * currentNode = headNode;
		while (currentNode != NULL) {
			if (myValue == currentNode->data) {
				return true;
			}
			currentNode = currentNode->nextNode;
		}
		return false;
	}

	virtual bool insert(Type myValue) {
		NodeWithData<Type> * currentNode = headNode;
		if (headNode == NULL) {
			NodeWithData<Type> * node = new NodeWithData<Type>(myValue);
			headNode = node;
			return true;
		}
		if (headNode->data > myValue) {
			NodeWithData<Type> * node = new NodeWithData<Type>(myValue);
			node->nextNode = headNode;
			headNode = node;
			return true;
		}
		if (headNode->data == myValue) {
			return false;
		}
		while (currentNode != NULL){
			if (currentNode->nextNode != NULL){
				if (inList(myValue)) {
					return false;
				}
				if (currentNode->nextNode->data < myValue) {
					currentNode = currentNode->nextNode;
				}
				else if (currentNode->nextNode->data == myValue) {
					currentNode = currentNode->nextNode;
				}
				else {
					NodeWithData<Type> * node = new NodeWithData<Type>(myValue);
					node->nextNode = currentNode->nextNode;
					currentNode->nextNode = node;
					return true;
				}
			}
			else {
				NodeWithData<Type> * node = new NodeWithData<Type>(myValue);
				currentNode->nextNode = node;
				return true;
			}
		}
	}

	virtual size_t size() const {
		int counter = 0;
		NodeWithData<Type> * currentNode = headNode;
		while (currentNode != NULL) {
			currentNode = currentNode->nextNode;
			counter += 1;
		}
		return counter;
	}

	virtual void clear() {
		NodeWithData<Type> * previousNode = NULL;
		while (headNode != NULL) {
			previousNode = headNode;
			headNode = headNode->nextNode;
			delete previousNode;
		}	
	}

	virtual size_t count(const Type& myValue) {
		NodeWithData<Type> * currentNode = headNode;
		while (currentNode != NULL) {
			if (myValue == currentNode->data) {
				return 1;
			}
			currentNode = currentNode->nextNode;
		}
		return 0;
	}

	friend ostream& operator<< (ostream& os, const Set<Type>& T) {
		string strList = "";
		NodeWithData<Type> * currentNode = T.headNode;
		if (T.headNode == NULL) {
			os << " Empty";
			return os;
		}
		while (currentNode != NULL) {
			os << currentNode->data;
			if (currentNode->nextNode != NULL) {
				os << ", ";
			}
			currentNode = currentNode->nextNode;
		}
		return os;
	}
	
	virtual string toString() const {
		string strList = "";
		NodeWithData<Type> * currentNode = headNode;
		ostringstream oss;
		oss << "[";
		if (headNode == NULL) {
			return " Empty";
		}
		while (currentNode != NULL) {
			oss << currentNode->data;
			if (currentNode->nextNode != NULL) {
				oss << ", ";
			}
			currentNode = currentNode->nextNode;
		}
		oss << "]";
		return oss.str();

	}
};

template <typename KEY, typename VALUE>
class hash_map {
private:
	size_t capacity;
	pair<KEY, VALUE>* myPairs;
public:
	hash_map<KEY, VALUE>() : myPairs(new pair<KEY, VALUE>[31]), capacity(31) {}
	~hash_map<KEY, VALUE>() {
		for (size_t i = 0; i < capacity; ++i) {
			myPairs[i].second.clear();
		}
		delete[] myPairs;
	}

	VALUE& operator[](const KEY& key) {
		size_t hash = key[0];
		for (size_t i = 1; i < key.length(); ++i) {
			hash = hash * 3 + key[i];
		}
		hash %= capacity;
		cout << endl << "Key=" << key << ", hash=" << hash;
		int k = 1;
		while (1) {
			if (myPairs[hash].first.length()) {
				if (myPairs[hash].first == key) break;
				hash = (hash + k) % capacity;
				k += 2;
				continue;
			}
			myPairs[hash].first = key;
			break;
		}
		return myPairs[hash].second;
	}
	
	friend ostream& operator<< (ostream& os, const hash_map<KEY, VALUE>& HM) {
		for (size_t i = 0; i < HM.capacity; ++i) {

			if (HM.myPairs[i].first.length()) {
				os << endl << "[" << i << ":";
				os << HM.myPairs[i].first << "->" << HM.myPairs[i].second << "]";
			}
		}
		return os;
	}

	size_t count(const KEY& key) {
		int size = 0;
		for (size_t i = 0; i < capacity; ++i) {
			if (key == myPairs[i].first) {
				size += 1;
				cout << "yes";
			}
		}
		return size;
	}

	void clear();
	size_t size() const;
	size_t max_size() const;

	string toString() const {
		ostringstream os;
		for (size_t i = 0; i < capacity; ++i) {
			if (myPairs[i].first.length()) {
				os << endl << "[" << i << ":";
				os << myPairs[i].first << "->" << myPairs[i].second << "]";
			}
		}
		return os.str();
	}
};

string boolTransform(bool boolValue) {
	if (boolValue == true) {
		return "true";
	}
	return "false";
}

int strToInt(string value) {
	int number;
	istringstream iss(value);
	iss >> number;
	return number;
}


int main(int argc, char * argv[]) {
	if (argc < 3) {
        cerr << "Please provide name of input and output files\n";
        return 1;
    }

    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input\n";
        return 1;
    }

    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {

        in.close();
        cerr << "Unable to open " << argv[2] << " for output\n";

    }

	string myArray[100];
	string line = "";
	string currentType = "";
	int listSize = 0;
	int numberOfPokemon = 0;
	int numberOfMoves = 0;
	int numberOfEffectivities = 0;
	int numberOfIneffectivities = 0;
	Set<int> myListInt;
	Set<string> myListString;
	hash_map<string, string> pokemon;
	hash_map<string, string> moves;
	hash_map<string, Set<string>> efficiency;
	hash_map<string, Set<string>> inefficiency;
	currentType = "STRING";

	while (getline(infile, line)) {
		if (line == "INT") {
			currentType = "INT";
			out << line << " " << "true" << endl;
			myListInt.clear();

		}
		else if (line == "STRING") {
			currentType = "STRING";
			out << line << " " << "true" << endl;
			myListString.clear();
		}
		
		else if (line.substr(0, 4) == "Set:") {
			
			if (currentType == "INT") {
				int value = strToInt(line.substr(5, line.length()));
				out << line << endl;
				out << myListInt.toString() << endl;
				myListInt.clear();
			}
			else {
				string setString;
				istringstream iss(line);
				iss >> setString;
				while (iss >> setString) {
					myListString.insert(setString);
				}
				out << line << endl;
				out << myListString.toString() << endl;
				myListString.clear();
			}
		}

		else if (line.substr(0, 8) == "Pokemon:") {
			string setString;
			string map2;
			istringstream iss(line);
			iss >> setString;
			iss >> setString;
			iss >> map2;
			if (pokemon[setString] == "") {
				numberOfPokemon += 1;
			}
			out << line << endl;
			pokemon[setString] = map2;
		}

		else if (line.substr(0, 5) == "Move:") {
			string setString;
			string map2;
			istringstream iss(line);
			iss >> setString;
			iss >> setString;
			iss >> map2;
			if (moves[setString] == "") {
				numberOfMoves += 1;
			}
			out << line << endl;
			moves[setString] = map2;
		}
		else if (line.substr(0, 4) == "Move") {
			out << "Moves:" << numberOfMoves << "/31";
			out << moves << endl;
		}
		else if (line.substr(0, 7) == "Pokemon") {
			out << "Pokemon:" << numberOfPokemon << "/31";
			out << pokemon << endl;
		}

		else if (line.substr(0, 10) == "Effective:") {
			string hashFirstValue;
			string setFirstValue;
			string setValues;
			string effectiveTitle;
			istringstream iss(line);
			iss >> effectiveTitle;
			iss >> hashFirstValue;			
			int temp = 0;
			out << "| " << efficiency[hashFirstValue].toString() << " |" << endl;
			if (efficiency[hashFirstValue].toString() == " Empty") {
				numberOfEffectivities += 1;
			}
			out << line << endl;
			while (iss >> setValues) {
				efficiency[hashFirstValue].insert(setValues);
			}	
		}
		else if (line.substr(0, 13) == "Effectivities") {
			out << endl << "Effectivities: " << numberOfEffectivities << "/31";
			out << efficiency << endl;
		}

		else if (line.substr(0, 12) == "Ineffective:") {
			string hashFirstValue;
			string setFirstValue;
			string setValues;
			string effectiveTitle;
			istringstream iss(line);
			Set<string> myListNewString;
			iss >> effectiveTitle;
			iss >> hashFirstValue;	
			int temp = 0;
			if (inefficiency[hashFirstValue].toString() == " Empty") {
				numberOfIneffectivities += 1;
			}
			out << line << endl;
			while (iss >> setValues) {
				inefficiency[hashFirstValue].insert(setValues);
			}
		}

		else if (line.substr(0, 15) == "Ineffectivities") {
			out << endl << endl << "Ineffectivities:" << numberOfIneffectivities << "/31";
			out << inefficiency << endl;
		}

		else if (line.substr(0, 7) == "Battle:") {
			string pokemon1;
			string move1;
			string pokemon2;
			string move2;
			istringstream iss(line);
			iss >> pokemon1;
			iss >> pokemon1;
			iss >> move1;
			iss >> pokemon2;
			iss >> move2;
			out << line << endl;
			int damage1To2 = efficiency[moves[move1]].count(pokemon[pokemon2])
				- inefficiency[moves[move1]].count(pokemon[pokemon2]);
			int damage2To1 = efficiency[moves[move2]].count(pokemon[pokemon1])
				- inefficiency[moves[move2]].count(pokemon[pokemon1]);
			out << pokemon1 << " (" << move1 << ") vs " << pokemon2 << " (" << move2 << ")" << endl;
			if ((damage1To2) > 0) {
				out << pokemon1 << "'s " << move1 << " is super effective against " << pokemon2 << endl;
			}
			else if ((damage1To2) < 0) {
				out << pokemon1 << "'s " << move1 << " is ineffective against " << pokemon2 << endl;
			}
			else {
				out << pokemon1 << "'s " << move1 << " is effective against " << pokemon2 << endl;
			}
			if ((damage2To1) > 0) {
				out << pokemon2 << "'s " << move2 << " is super effective against " << pokemon1 << endl;
			}
			else if ((damage2To1) < 0) {
				out << pokemon2 << "'s " << move2 << " is ineffective against " << pokemon1 << endl;
			}
			else {
				out << pokemon2 << "'s " << move2 << " is effective against " << pokemon1 << endl;
			}

			if ((damage1To2 - damage2To1) > 0) {
				out << "In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon1 << " wins!" << endl << endl;
			}
			else if ((damage1To2 - damage2To1) < 0) {
				out << "In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon2 << " wins!" << endl << endl;
			}
			else
			{
				out << "The battle between " << pokemon1 << " and " << pokemon2 << " is a tie." << endl << endl;
			}
		}
	}
	myListInt.clear();
	myListString.clear();
	out.close();
	return 0;
}


