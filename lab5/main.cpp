#include "ExpressionManagerInterface.h"
#include "ExpressionManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char * argv[]) {
	if (argc < 3) {
		cerr << "Need name of input and output files";
		return 1;
	}

	ifstream in(argv[1]);
	if (!in) {
		cerr << "Failed to open " << argv[1] << " for input";
		return 2;
	}
	
	ofstream out(argv[2]);
	if (!out) {
		cerr << "Failed to open " << argv[2] << " for output";
		return 3;
	}

	string line, command;
	ExpressionManagerInterface* currentExpression = new ExpressionManager();
	while (getline(in, line)) {
		try {
			if (line.size() == 0) continue;
			istringstream iss(line);
			iss >> command;

			if (command == "Expression:") {
				out << line << endl;
				string expression = line.substr(12, line.find("\n"));
				currentExpression->setExpression(expression);
			}
			else if (command == "Infix:") {
				out << "Infix: ";
				out << currentExpression->infix() << endl;
			}
			else if (command == "Postfix:") {
				out << "Postfix: ";
				out << currentExpression->postfix() << endl;
			}
			else if (command == "Prefix:") {
				out << "Prefix: ";
				out << currentExpression->prefix() << endl;
			}
			else if (command == "Value:") {
				out << "Value: ";
				out << currentExpression->value() << endl;
			}

		}
		catch (std::exception& e) {
			out << e.what() << endl;
		}

	}

	delete currentExpression;

		return 0;
}
