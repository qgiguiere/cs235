#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H

#include "ExpressionManagerInterface.h"
#include <sstream>
#include <vector>
#include <string>

using std::string;

class ExpressionManager : public ExpressionManagerInterface {

private:

   std::string expression_;

   std::vector<std::string> inFix_;

   std::vector<std::string> postFix_;

   std::vector<std::string> preFix_;

   const std::string operators = "([{ -+  */% ";

public:
	
	ExpressionManager();
   // ExpressionManager(string exp) :
     //   expression_(exp), inFix_(NULL), postFix_(NULL), preFix_(NULL) { }
	~ExpressionManager();

    virtual int value(void); /** Return the integer value of the infix expression */

    virtual string infix(void); /** Return the infix expression / rejects invalid */

    virtual string postfix(void); /** Return a postfix representation */

    virtual string prefix(void); /** (BONUS) Return a prefix representation */

    virtual string toString() const; /** Return the infix vector'd expression items */
    
    virtual bool isUnbalanced(void);

    virtual bool hasIllegalOperator(string);



};

#endif // EXPRESSION_MANAGER_H