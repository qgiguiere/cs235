#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>

using namespace std;

#include "snap.h"
#include "csg.h"
#include "cdh.h"
#include "cr.h"
#include "course.h"
#include "student.h"


int main(int argc, char * argv[]) {

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

   vector<Cr> crs;
   for (string line; getline(in, line);)	/* Read until EOF*/ {
      if ("cr(" == line.substr(0, 3)) {
         // cr('CS101','Turing Aud.').
         string courseName = line.substr(3, line.find(',') - 3);
         line = line.substr(line.find(',') + 1);
         string room = line.substr(0, line.find(')'));
         crs.push_back(Cr(courseName, room));
      }
   }

   string toString() const {
      stringstream out;
      out << "Name = " << getName();
      return out.str();
   }

   friend std::ostream& operator<< (ostream& os, const MyClass& myclass) {
      os << myclass.toString();
      return os;
   }

   cout << endl << "Vectors:" << endl;
   for (unsigned int i = 0; i < myClasses.size(); i++) {
      cout << myClasses[i] << endl;
   }

    return 0;
}