#include "token.h"
#include <cctype>
#include <iostream>
#include <string>

std::pair<int,int> last_operation_bounds(const std::string &expr) {
  // эти переменные описывают уровень вложенности скобок
  int level = 0;
  int min_level = 10;
  for (int i = 0; i < expr.length(); i++) {
    if (expr.at(i) == '(') {
      level++;
    }
    else if (expr.at(i) == ')') {
      level--;
    }
    else {

    }
  }
}

Token get_token_from(const std::string &expr, int ind) {
  while (!isalpha((int)expr.at(ind))) {
    ind++;
  }
  int end = ind;
  while (isalpha((int)expr.at(end))) {
    std::cout << expr.at(end);
    end++;
  }
  std::cout << std::endl;
  std::string sub = expr.substr(ind, end - 1);
  std::cout << sub << std::endl;
  return Token::NOT;
}
