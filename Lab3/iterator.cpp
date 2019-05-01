#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "myArray.h"
using namespace std;
#define BONUS 0

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif


int main(int argc, char * argv[])
{
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

    MyArray<int> numbers(MAX_ARRAY_SIZE);
	//std::ostream& out = std::cout;

    int i;
    //ifstream in(argv[1]);
    while (in >> i) {
        numbers.push_back(i);
    }

    out << numbers << endl << endl;
    out << endl << endl;


	out << "ITERATORS:";
    out << endl << "begin(): " << numbers.begin();
    out << endl << "end(): " << numbers.end();
    out << endl << endl;

	out << "SEQUENTIAL:" << endl;
	MyArray<int>::Iterator iter1 = numbers.begin();
	out << "iter1: " << iter1 << endl;
	for (; iter1 != numbers.end(); ++iter1)
		out << *iter1 << " ";
	out << endl << endl;

#if (BONUS)
	out << "PRIME:" << endl;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (isPrime(numbers[i])) out << numbers[i] << " ";
	}
	out << endl << endl;
#endif
	return 0;
}