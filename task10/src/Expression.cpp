#include "Expression.h"

#include <iostream>

Expression::Expression(const string &expr) : expr(expr) {

}

string remove_unused_spaces(const string &expr) {
  string no_extra_spaces_str = "";
  bool space = false;
  for (int i = 0; i < expr.length(); i++) {
    char c = expr.at(i);
    if (c == ' ') {
      if (!space) {
        space = true;
        no_extra_spaces_str += ' ';
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
