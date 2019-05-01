#include "ExpressionManager.h"
#include <stack>
#include <sstream>
#include <string>

bool ExpressionManager::isUnbalanced() {

    bool isUnbalanced = false;
    std::stack<string> balancedStack;

    std::stringstream SS(this->expression_);
    string currentString;
    while(SS >> currentString) {

        if (isLeftParen(currentString)) {

            balancedStack.push(currentString);

        }
        else if (isRightParen(currentString) && !balancedStack.empty()) {

            if (isPair(balancedStack.top(), currentString)) {

                balancedStack.pop();

            }
            else {

                isUnbalanced = true;
                break;

            }

        }
    }

    if (!balancedStack.empty()) {

        isUnbalanced = true;

    }
    return isUnbalanced;

}

bool ExpressionManager::hasIllegalOperator(string currentString) {

    bool hasIllegalOperator = true;
    if (isOperator(currentString) || isOperand(currentString) || isLeftParen(currentString) || isRightParen(currentString)) {

        hasIllegalOperator = false;

    }
    return hasIllegalOperator;

}


bool ExpressionManager::isLeftParen(string currentStr) {

    bool isLeftParen = false;
    if (currentStr == "(" || currentStr == "[" || currentStr == "{") {
        isLeftParen = true;
    }
    return isLeftParen;

}

bool ExpressionManager::isRightParen(string currentStr) {

    bool isRightParen = false;
    if (currentStr == ")" || currentStr == "]" || currentStr == "}") {

        isRightParen = true;

    }
    return isRightParen;

}

bool ExpressionManager::isPair(string left, string right) {

    bool isPair = false;
    if((left == "(" && right == ")") || (left == "[" && right == "]") || (left == "{" && right == "}")) {

        isPair = true;

    }
    return isPair;

}

bool ExpressionManager::isOperator(string input) {

    bool isOperator = false;
    if (input == "+" || input == "-" || input == "*" || input == "/" || input == "%") {

        isOperator = true;

    }
    return isOperator;

}

bool ExpressionManager::isOperand(string input) {

    bool isOperand = true;
    try {

        stoi(input);

    } catch(invalid_argument const &e) {

        isOperand = false;

    }
    return isOperand;

}

bool ExpressionManager::isNumber(string input) {}

bool ExpressionManager::precedence(string operatr) {}

int ExpressionManager::value(void) {


}

string ExpressionManager::infix(void) {

    string returnString;
    try {

        if(this->expression_.empty()) {

            throw string ("Invalid Expression");

        }
        else if (isUnbalanced()) {

            throw string ("Unbalanced");

        }

        stringstream ss(expression_);
        string currentString;
        int operandCount = 0;
        int operatorCount = 0;
        while (ss >> currentString) {

            if (isOperator(currentString)) {

                operatorCount++;

            }
            else if(isOperand(currentString)) {

                operandCount++;

            }

            if (operandCount - operatorCount >= 2) {

                return "Missing Operator";

            }
            else if (operandCount - operatorCount <= -1) {

                return "Missing Operand";

            }

            if(hasIllegalOperator(currentString)) {

                throw string ("Illegal Operator");

            }

        }

        if (operandCount - operatorCount <= 0) {

            throw string ("Missing Operand");

        }

        returnString = expression_;

    } catch(string const &e) {

        returnString = e;

    }
    return returnString;

}

string ExpressionManager::postfix(void) {


}

string ExpressionManager::prefix(void) {

    return "NOT IMPLEMENTED";

}

string ExpressionManager::toString(void) const {


}