#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <utility>

using namespace std;

struct Expression {
  const string &expr;
  pair<int,int> left, right;
  Expression *exprLeft, *exprRight;

  Expression(const string &expr);
};

string remove_unused_spaces(const string &expr);

#endif // EXPRESSION_H
