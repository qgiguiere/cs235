#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "BST.h"



#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;


int main(int argc, char** argv) {
	VS_MEM_CHECK
		if (argc < 3) {
			return 1;
		}
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	BST<string> strings;
	BST<int> ints;

	outputFile << boolalpha;
	bool userString = false;
	bool userInt = false;
	string line;
	while (getline(inputFile, line)) {
		outputFile << line << " ";
		if (line == "INT") {
			userInt = true;
			userString = false;
			outputFile << userInt << endl;
			continue;
		}
		if (line == "STRING") {
			userString = true;
			userInt = false;
			outputFile << userString << endl;
			continue;
		}
		int pos;
		pos = line.find_first_of(" ");
		string key = line.substr(0, pos);

		if (key == "add") {
			if (userString) {
				outputFile << strings.addNode(line.substr(pos + 1));
			}
			else if (userInt) {
				outputFile << ints.addNode(stoi(line.substr(pos + 1)));
			}
			else {
				outputFile << "Error";
			}
		}

		else if (key == "find") {
			if (userString) {
				outputFile << strings.find(line.substr(pos + 1));
			}
			else if (userInt) {
				outputFile << ints.find(stoi(line.substr(pos + 1)));
			}
			else {
				outputFile << "Error";
			}
		}

		else if (key == "remove") {
			if (userString) {
				outputFile << strings.removeNode(line.substr(pos + 1));
			}
			else if (userInt) {
				outputFile << ints.removeNode(stoi(line.substr(pos + 1)));
			}
			else {
				outputFile << "Error";
			}
		}

		else if (line == "size") {
			if (userString) {
				outputFile << strings.size();
			}
			else if (userInt) {
				outputFile << ints.size();
			}
			else {
				outputFile << "Error";
			}
		}

		else if (line == "clear") {
			if (userString) {
				outputFile << strings.clearTree();
			}
			else if (userInt) {
				outputFile << ints.clearTree();
			}
			else {
				outputFile << "Error";
			}
		}

		else if (line == "print") {
			if (userString) {
				outputFile << ":" << strings;
			}
			else if (userInt) {
				outputFile << ":" << ints;
			}
			else {
				outputFile << "Error";
			}
		}

		else {
			outputFile << false;
		}

		outputFile << endl;
	}


	inputFile.close();
	outputFile.close();

	return 0;
}