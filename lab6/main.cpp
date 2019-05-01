#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stack>
#include <fstream>
#include <istream>

#include "Station.h"

using namespace std;

int main (int argc, char * argv[]) {
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

    string line, command;
    while (getline(in, line)) {
        Station<size_t>* newStation;
        istringstream iss(line);
        iss >> command;
        //out << command << endl;
        if (command == "Add:station") {
            int num;
            iss >> num;
            out << "Add:station " << num <<  " OK" << endl;

            newStation = new Station<size_t>(data);
        }
        else if (command == "Remove:station") {
            out << "Remove:station OK" << endl;
        }
        else if (command == "Train:") {
            out << "Train: "
            for(int i = 0; i < num_items; ++i) {
                out << vector.at(i) << " ";
            }
            out << endl;
        }
        else if (command == "Add:queue") {
            out << "Add:queue OK" << endl;
        }
        else if (command == "Remove:queue") {
            out << "Remove:queue OK" << endl;
        }
        else if (command == "Add:stack") {
            out << "Add:stack OK" << endl;
        }
        else if (command == "Remove:stack") {
            out << "Remove:stack OK" << endl;
        }
        else if (command == "Top:station") {
            
        }
        else if (command == "Top:queue") {
            
        }
        else if (command == "Top:stack") {
            
        }
        else if (command == "Size:queue") {
            
        }
        else if (command == "Size:stack") {
            
        }
        else if (command == "Find:") {
            
        }
    }

    return 0;
}