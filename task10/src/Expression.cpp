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
  cout << expr.substr(left.first, left.second - left.first) << endl;
  if (op == OR) cout << " OR " << endl;
  else if (op == AND) cout << " AND " << endl;
  cout << expr.substr(right.first, right.second - right.first) << endl;
  if (exprLeft != nullptr) {
    exprLeft->print();
  }
  if (exprRight != nullptr) {
    exprRight->print();
  }
}

 
int Expression::calculate(int bits, const vector<char> &characters) {
  int next;
  int l = 0, r = 0;
  int result = 0;
  int ch_ind = 0;
  if (op == OR || op == AND) {
    if (leftSimple) {
      Token t;
      bool is_not = false;
      t = get_token_from(expr, left.first, next);
      if (t.type == NOT) {
        t = get_token_from(expr, next, next);
        is_not = true;
      }
      for (int i = 0; i < characters.size(); i++) {
        if (characters[i] == t.var) {
          ch_ind = i;
        }
      }
      //l = ((bits & (1 << ((int)t.var - 65))) >> ((int)t.var - 65)) % 2;
      l = ((bits & (1 << ch_ind)) >> (ch_ind)) % 2;
      if (is_not) {
        l++;
        l %= 2;
      }
    }
    else {
      l = exprLeft->calculate(bits, characters);
    }
    if (rightSimple) {
      Token t;
      bool is_not = false;
      t = get_token_from(expr, right.first, next);
      if (t.type == NOT) {
        t = get_token_from(expr, next, next);
        is_not = true;
      }
      for (int i = 0; i < characters.size(); i++) {
        if (characters[i] == t.var) {
          ch_ind = i;
        }
      }
      //r = ((bits & (1 << ((int)t.var - 65))) >> ((int)t.var - 65)) % 2;
      r = ((bits & (1 << ch_ind)) >> (ch_ind)) % 2;
      if (is_not) {
        r++;
        r %= 2;
      }
    }
    else {
      r = exprRight->calculate(bits, characters);
    }
  }
  if (op == OR) {
    result = l | r;
  }
  else if (op == AND) {
    result = l & r;
  }
  return result;
}
bool is_simple(const string &expr) {
  int i = 0;
  bool isSimple = true;
  while (1) {
    Token t = get_token_from(expr, i, i);
    if (t.type == UNDEFINED || i == -1) break;
    if (t.type == AND || t.type == OR) {
      isSimple = false;
    }
  }
  return isSimple;
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

  int next;

  string leftStr = expr.substr(left.first, left.second - left.first);
  leftStr = remove_unused_spaces(leftStr);
  leftSimple = is_simple(leftStr);
  //cout << leftStr << endl;
  //cout << is_simple(leftStr) << endl;

  op = (TokenType) code;
  //if (op == OR) cout << " OR " << endl;
  //else if (op == AND) cout << " AND " << endl;

  string rightStr = expr.substr(right.first, right.second - right.first);
  rightStr = remove_unused_spaces(rightStr);
  rightSimple = is_simple(rightStr);
  //cout << rightStr << endl;
  //cout << is_simple(rightStr) << endl;

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
