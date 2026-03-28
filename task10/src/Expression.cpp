#include "Expression.h"

#include "Token.h"
#include <iostream>

Expression::Expression(const string &expr) : Expression(expr, pair<int,int>(0, expr.length())) {
  
  if (remove_unused_spaces(expr) != expr) {
    cout << "expr should have no unused spaces (call remove_unused_spaces before)" << endl;
    return;
  }
}

void Expression::print() {
  if (exprLeft != nullptr) {
    exprLeft->print();
  }
  cout << expr.substr(left.first, left.second - left.first) << endl;
  if (op == OR) cout << " OR " << endl;
  else if (op == AND) cout << " AND " << endl;
  cout << expr.substr(right.first, right.second - right.first) << endl;
  if (exprRight != nullptr) {
    exprRight->print();
  }
}

Expression::Expression(const string &expr, pair<int,int> bounds) : expr(expr) {
  pair<pair<int,int>,pair<int,int>> split_bounds;
  int code = split_by_last_operation(expr, bounds, split_bounds);
  op = TokenType::VAR;
  exprLeft = nullptr;
  exprRight = nullptr;
  if (code == -1) return;
  left = split_bounds.first;
  right = split_bounds.second;

  string leftStr = expr.substr(left.first, left.second - left.first);
  leftStr = remove_unused_spaces(leftStr);
  //cout << leftStr << endl;

  op = (TokenType) code;
  //if (op == OR) cout << " OR " << endl;
  //else if (op == AND) cout << " AND " << endl;

  string rightStr = expr.substr(right.first, right.second - right.first);
  rightStr = remove_unused_spaces(rightStr);
  //cout << rightStr << endl;

  exprLeft = new Expression(expr, left);
  exprRight = new Expression(expr, right);
}

string remove_unused_braces(const string &expr) {
  if (expr.at(0) == '(' && expr.at(expr.length() - 1) == ')') {
    return expr.substr(1, expr.length() - 2);
  }
  return expr;
}

string remove_unused_spaces(const string &expr) {
  string no_extra_spaces_str = "";
  bool space = false;
  for (int i = 0; i < expr.length(); i++) {
    char c = expr.at(i);
    if (c == ' ') {
      if (!space) {
        space = true;
        if (i != 0) {
          no_extra_spaces_str += ' ';
        }
      }
    }
    else {
      no_extra_spaces_str += c;
      space = false;
    }
  }
  string result = "";
  for (int i = 0; i < no_extra_spaces_str.length(); i++) {
    char c = no_extra_spaces_str.at(i);
    if (c == ' ' && i != 0 && i != no_extra_spaces_str.length() - 1) {
      if (isalpha(no_extra_spaces_str.at(i - 1)) && isalpha(no_extra_spaces_str.at(i + 1))) {
        result += ' ';
      }
    }
    else {
      result += c;
    }
  }
  return result;
}
