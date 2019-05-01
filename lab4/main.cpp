#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedList.h"

using namespace std;

int main(int argc, char * argv[]) {    
    if (argc < 3) {
        cerr << "Please provide name of input and output files" << endl;
        return 1;
    }
    
    cout << "Input file: " << argv[1] << endl;
    ifstream in;   
    in.open(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    
    cout<< "Output file: " << argv[2] << endl;
    ofstream out;
    out.open(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }
    cout<< endl;
        
    string inputString;
    
    while(!in.eof()) {
        in >> inputString;
        out << inputString;
        
        while (inputString == "INT") {
            out << " true" << endl;
            LinkedList<int> myLinkedList;
            in >> inputString;
            out << inputString << " ";
            while (inputString != "INT" && inputString != "STRING") {
                if (inputString == "insertHead") {
                    int headValue;
                    in >> headValue;
                    out << headValue << " ";
                    bool ToF = myLinkedList.insertHead(headValue);
                    out << ((ToF) ? "true" : "false") << endl; 
                    
                }
                else if (inputString == "insertTail") {
                    int tailValue;
                    in >> tailValue;
                    out << tailValue << " ";
                    bool ToF = myLinkedList.insertTail(tailValue);
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "insertAfter") {
                    int beforeValue;
                    int afterValue;
                    in >> beforeValue >> afterValue;
                    out << beforeValue << " " << afterValue << " ";
                    bool ToF = myLinkedList.insertAfter(beforeValue, afterValue);
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "remove") {
                    int removeValue;
                    in >> removeValue;
                    out << removeValue << " ";
                    bool ToF = myLinkedList.remove(removeValue);
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "at") {
                    int index;
                    in >> index;
                    out << index << " ";
                    
                    try {   
                        int val = myLinkedList.at(index);
                        out << val << " true" << endl;
                    }
                    catch (...){
                        out << "Invalid Index" << endl;
                    }
                }
                else if (inputString == "size") {
                    size_t size = myLinkedList.size();
                    out << size << endl;
                }
                else if (inputString == "clear") {
                    bool ToF = myLinkedList.clear();
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "printList") {
                    out << myLinkedList << endl;    

                }
                else {
                    out << "couldn't read command" << endl;
                }
                
                if (in.eof()) { 
                    myLinkedList.clear();
                    in.close();
                    out.close();
                    myLinkedList.~LinkedList();
                    return 0;
                }
                in >> inputString;
                out << inputString << " ";  
            }
        }
        
        while (inputString == "STRING") {
            out << "true" << endl;
            LinkedList<string> myLinkedList;
            in >> inputString;
            out << inputString << " ";
            while (inputString != "INT" && inputString != "STRING") {
                if (inputString == "insertHead") {
                    string headValue;
                    in >> headValue;
                    out << headValue << " ";
                    bool ToF = myLinkedList.insertHead(headValue);
                    out << ((ToF) ? "true" : "false") << endl; 
                }
                else if (inputString == "insertTail") {
                    string tailValue;
                    in >> tailValue;
                    out << tailValue << " ";
                    bool ToF = myLinkedList.insertTail(tailValue);
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "insertAfter") {
                    string beforeValue;
                    string afterValue;
                    in >> beforeValue >> afterValue;
                    out << beforeValue << " " << afterValue << " ";
                    bool ToF = myLinkedList.insertAfter(beforeValue, afterValue);
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "remove") {
                    string removeValue;
                    in >> removeValue;
                    out << removeValue << " ";
                    bool ToF = myLinkedList.remove(removeValue);
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "at") {
                    int index;
                    in >> index;
                    out << index << " ";
                    
                    try {  
                        string val = myLinkedList.at(index);
                        out << val << " true" << endl;
                    }
                    catch (int e){
                        out << "Invalid Index" << endl;
                    }
                }
                else if (inputString == "size") {
                    size_t size = myLinkedList.size();
                    out << size << endl;
                }
                else if (inputString == "clear") {
                    bool ToF = myLinkedList.clear();
                    out << ((ToF) ? "true" : "false") << endl;
                }
                else if (inputString == "printList") {
                    out << myLinkedList << endl;    
                }
                else {
                    out << "Couldn't read command" << endl;
                }
                
                if (in.eof() == true) { 
                    myLinkedList.clear();
                    in.close();
                    out.close();
                    myLinkedList.~LinkedList();
                    return 0;
                }
                in >> inputString;  
                out << inputString << " ";
            }
        }
    }
    
    in.close();
    out.close();
    return 0;
}
