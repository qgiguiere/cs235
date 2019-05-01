#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <string>
#include <stack>
#include "ExpressionManagerInterface.h"
#include "ExpressionManager.h"
using namespace std;

int main(int argc, char* argv[]) {

    VS_MEM_CHECK               // enable memory leak check

    if (argc < 3) {

        cerr << "Please provide name of input and output files";
        return 1;

    }

    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {

        cerr << "Unable to open " << argv[1] << " for input";
        return 2;

    }

    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {

        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;

    }

    out << endl;
    ExpressionManager* expressionObj = new ExpressionManager();
    // process input strings
    string line, command;
    while (getline(in, line)) {

        try {

            if (line.empty()) continue;

            istringstream iss(line);
            iss >> command;
            if (command == "Expression:") {

                string mathExpression = line.substr(command.size() + 1);
                delete expressionObj;
                expressionObj = new ExpressionManager(mathExpression);
                out << "Expression: " << mathExpression << endl;
                continue;

            }
            else if(command == "Infix:") {

                string infixString = expressionObj->infix();
                out << "Infix: " << infixString << endl << endl;
                continue;

            }
            else if (command == "Postfix:") {

                continue;

            }
            else if (command == "Prefix:") {

                continue;

            }
            else {

//                throw string ("Invalid Command");

            }
        }
        catch (exception& e) {

            out << e.what() << endl;

        }
    }

    return 0;

}
