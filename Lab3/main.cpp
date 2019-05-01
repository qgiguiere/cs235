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
	VS_MEM_CHECK;

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

	MyArray<int> numbers(MAX_ARRAY_SIZE);

	int temp;
	while (in >> temp)
	{
		numbers.push_back(temp);
	}
	
	out << "myArray:" << endl;
	out << numbers << endl;

	out << "ITERATORS:";
	out << endl << "begin(): " << numbers.begin();
	out << endl << "end(): " << numbers.end();
	out << endl << endl;

	out << "SEQUENTIAL:" << endl;
	MyArray<int>::Iterator iter = numbers.begin();
	for (int i = 0; iter != numbers.end(); ++iter)
	{
		if (!(i++ % 10)) out << endl;
		out << *iter << " ";
	}

#if (BONUS)
	out << "PRIME (Bonus)" << endl;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (isPrime(numbers[i])) out << numbers[i] << " ";
	}
	out << endl << endl;

	out << "FIBONACCI (Bonus)" << endl;
	MyArray<int>::Iterator iter2 = numbers.begin();
	int n1 = *iter2++;
	int n2 = *iter2++;
	while (iter2 != numbers.end())
	{
		if ((n1 + n2) == *iter2)
		{
			out << *iter2 << "=" << n1 << "+" << n2 << " ";
		}
		n1 = n2;
		n2 = *iter2++;
	}
	out << endl << endl;
#endif
	return 0;
}