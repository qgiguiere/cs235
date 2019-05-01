#include "ExpressionManagerInterface.h"
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>
#include <stack>
#include <stdexcept>
#include <sstream>

class ExpressionManager : public ExpressionManagerInterface {
private:
	string expression_;
	const string operators = "([{ -+  */% )]}";
	const string openParen = "([{";
	const string closeParen = ")]}";
	const string mathOperators = "-+*/%";
	std::stack<char> operatorsStack;
	std::stack<int> math;
	string postfixString = "";
	string prefixString = "";

public:
	ExpressionManager() {}

	ExpressionManager(string exp) :
		expression_(exp) { }

	virtual ~ExpressionManager() { }

	bool isOpenParen(char ch) {
		return openParen.find(ch) != string::npos;
	}

	bool isCloseParen(char ch) {
		return closeParen.find(ch) != string::npos;
	}

	bool isParen(char ch) {
		if (closeParen.find(ch) != string::npos) {
			return true;
		}
		else if (openParen.find(ch) != string::npos) {
			return true;
		}
		else {
			return false;
		}
	}

	void setExpression(string ex) {
		this->expression_ = ex;
	}

	int precedence(char op) {
		if (isCloseParen(op)) {
			return 3;
		}
		else if (op == '*' || op == '/' || op == '%') {
			return 2;
		}
		else if (op == '+' || op == '-') {
			return 1;
		}
		else {
			return 0;
		}
	}

	bool isBalanced(const string expression) {
		std::stack<char> s;

		std::istringstream infixTokens(expression_);
		char nextToken;

		while (infixTokens >> nextToken) {
			if (isOpenParen(nextToken)) {
				s.push(nextToken);
			}
			else if (isCloseParen(nextToken)) {
				if (s.empty()) {
					return false;
				}
				else {
					char topCh = s.top();
					s.pop();
					if (!(openParen.find(topCh) == closeParen.find(nextToken))) {
						return false;
					}
				}
			}
		}
		if (s.empty()) {
			return true;
		}
		else {
			return false;
		}

	}

	bool isOperator(char ch) const {
		return operators.find(ch) != string::npos;
	}

	bool isMathOperator(char ch) const {
		return mathOperators.find(ch) != string::npos;
	}

	bool wrongOperator(const string ex) {
		std::istringstream infixTokens(ex);
		char nextToken;

		while (infixTokens >> nextToken) {
			if (!(isalnum(nextToken))) {
				if (!isOperator(nextToken)) {
					return true;
				}
			}
		}
		return false;
	}

	bool isMissingOperator(const string ex) {
		std::stringstream os(ex);
		bool num = 0;
		string token;

		while (os >> token) {
			if (isMathOperator(token[0])) {
				if (num == true) {
					return true;
				}
				num = true;
			}
			else {
				num = false;
			}
		}
		return false;
	}

	bool isMissingOperand(const string ex) {
		char lastCh = expression_[expression_.size() - 1];
		
		if (lastCh == 32) {
			expression_.pop_back();
		}

		if (isMathOperator(expression_[0]) || isMathOperator(expression_[expression_.size() - 1])) {
			return true;
		}

		std::stringstream os(ex);
		bool op = 0;
		string token;

		while (os >> token) {
			if (isMathOperator(token[0])) {
				if (op == true) {
					return true;
				}
				op = true;
			}
			else {
				op = false;
			}
		}
		return false;
	}

	void processOperator (char op) {
		if (operatorsStack.empty() || isOpenParen(op)) {
			operatorsStack.push(op);
		}
		else {
			if (precedence(op) > precedence(operatorsStack.top()) && precedence(op) != 3) {
				operatorsStack.push(op);
			}
			else {
				if (precedence(op) == 3) {
					char match;
					switch (op) {
					case ')':
						match = '(';
						break;
					case ']':
						match = '[';
						break;
					case '}':
						match = '{';
						break;
					}

					while (operatorsStack.top() != match) {
						if (!(isParen(operatorsStack.top()))) {
							postfixString += operatorsStack.top();
							postfixString += " ";
							operatorsStack.pop();
						}

					}
					if (operatorsStack.top() == match) {
						operatorsStack.pop();
					}
					
				}
				else {
					while (!(operatorsStack.empty()) && precedence((operatorsStack.top())) >= precedence(op))	{
						postfixString += operatorsStack.top();
						postfixString += " ";
						operatorsStack.pop();
					}
					operatorsStack.push(op);
				}

			}
		}
	}

	//evaluate operator for the value
	int evalOp(char op) {
		int rhs = math.top();
		math.pop();
		int lhs = math.top();
		math.pop();

		int result = 0;

		switch (op) {
		case '+': result = lhs + rhs;
			break;
		case '-': result = lhs - rhs;
			break;
		case '*': result = lhs * rhs;
			break;
		case '/': result = lhs / rhs;
			break;
		case '%': result = lhs % rhs;
			break;
		}

		return result;
	}

	virtual int value(void) {
		postfix();
		postfixString.pop_back();

		while (!math.empty()) {
			math.pop();
		}

		std::stringstream tokens(postfixString);
		char next;

		while (tokens >> next) {
			if (isdigit(next)) {
				tokens.putback(next);
				int value;
				tokens >> value;
				math.push(value);
			}
			else {
				int answer = 0;
				answer = evalOp(next);


				math.push(answer);
			}
		}

		if (!math.empty()) {
			int finalAnswer = math.top();
			math.pop();
			if (math.empty()) {
				return finalAnswer;
			}
		}
		
	}

	virtual std::string infix(void) {
		if (!(isBalanced(expression_))) {
			return "Unbalanced";
		}
		else if (isMissingOperand(expression_)) {
			return "Missing Operand";
		}
		else if (wrongOperator(expression_)) {
			return "Illegal Operator";
		}
		else if (isMissingOperator(expression_)) {
			return "Missing Operator";
		}
		else {
			return expression_;
		}
	}

 	virtual std::string postfix(void) {
		if (isBalanced(expression_)) {
			std::stringstream prefix(expression_);
			postfixString = "";

			while (!operatorsStack.empty()) {
				operatorsStack.pop();
			}

			std::istringstream infixTokens(expression_);
			string nextToken;

			while (infixTokens >> nextToken) {
				if (isalnum(nextToken[0])) {
					postfixString += nextToken;
					postfixString += " ";
				}
				else {
					processOperator(nextToken[0]);
				}
			}
			while (!operatorsStack.empty()) {
				char op = operatorsStack.top();
				if (!isOpenParen(operatorsStack.top()) && !isCloseParen(operatorsStack.top())) {
					postfixString += op;
					postfixString += " ";
				}
				operatorsStack.pop();
			}
			return postfixString;
		}
		else {
			return "Unbalanced";
		}
	}


	virtual std::string prefix(void) {
		postfix();
		std::stack<string> prefixStack;
		std::istringstream infixTokens(postfixString);
		string nextToken;

		while (infixTokens >> nextToken) {
			if (isalnum(nextToken[0])) {
				prefixStack.push(nextToken);
			}
			else {
				string num1 = prefixStack.top();
				prefixStack.pop();
				string num2 = prefixStack.top();
				prefixStack.pop();

				prefixString = nextToken  + num2 + num1;
				prefixStack.push(prefixString);
			}
		}
		return prefixStack.top();
	}

	virtual std::string toString(void) const {
		std::stringstream iss;
		std::vector<string> infixVector;
		std::istringstream infixTokens(expression_);
		string nextToken;

		while (infixTokens >> nextToken) {
			infixVector.push_back(nextToken);
		}

		for (size_t i = 0; i < infixVector.size(); i++) {
			iss << infixVector[i] << " ";
		}
		return iss.str();
	}


};


#endif
