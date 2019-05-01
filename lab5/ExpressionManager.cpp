#include "ExpressionManager.h"
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stack>

using namespace std;

string intToString(int in) {
	stringstream ss;
	ss << in;
	string out = ss.str();
	return out;
}
int stringToInt(string in) {
	stringstream ss;
	ss.str(in);
	int out;
	ss >> out;
	return out;
}
bool isNum(string in) {
	stringstream ss;
	ss.str(in);
	int out;
	ss >> out;
	if (ss.fail() || !ss.eof())
		return false;
	return true;
}

ExpressionManager::ExpressionManager(){}
ExpressionManager::~ExpressionManager(){}

string ExpressionManager::infix() {
    string infixExpression;
	stringstream in;
	stringstream out;
	in.str(infixExpression);
	stack<int> ops;
	string temp;
	while (!in.fail() || !in.eof()) {
		in >> temp;
		if (in.fail())
			break;
		if (isNum(temp)) {
			out << temp << ' ';
		} 
        else if (temp[0] == '(') {
			ops.push(temp[0]);
		} 
        else if (temp[0] == ')') {
			while (ops.top() != '(') {
				out << (char) ops.top() << ' ';
				ops.pop();
			}
			ops.pop();
		} 
        else if (temp[0] == '*' || temp[0] == '/' || temp[0] == '%') {
			if (ops.size() != 0) {
				while (ops.top() == '*' || ops.top() == '/' || ops.top() == '%') {
					out << (char) ops.top() << ' ';
					ops.pop();
					if (ops.size() == 0) {
						break;
                    }
				}
			}
			ops.push(temp[0]);
		} 
        else if (temp[0] == '-' || temp[0] == '+') {
			if (ops.size() != 0) {
				while (ops.top() == '*' || ops.top() == '/' || ops.top() == '%'
						|| ops.top() == '-' || ops.top() == '+') {
					out << (char) ops.top() << ' ';
					ops.pop();
					if (ops.size() == 0) {
						break;
                    }
				}
			}
			ops.push(temp[0]);
		} 
        else {
			return "invalid";
		}
	}
	while (ops.size() != 0) {
		out << (char) ops.top();
		if (ops.size() != 1) {
			out << ' ';
        }
		ops.pop();
	}
	return out.str();
}