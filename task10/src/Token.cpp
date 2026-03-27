#include "Token.h"
#include <cctype>
#include <iostream>
#include <string>

pair<pair<int,int>,pair<int,int>> split_by_last_operation(const std::string &expr) {
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

void Token::print() {
  if (this->type == UNDEFINED) {
    cout << "UNDEFINED" << endl;
  }
  else if (this->type == VAR) {
    cout << this->var << endl;
  }
  else if (this->type == AND) {
    cout << "AND" << endl;
  }
  else if (this->type == OR) {
    cout << "OR" << endl;
  }
  else {
    cout << "NOT" << endl;
  }
}

Token get_token_from(const std::string &expr, int ind, int &next) {
  char c = expr.at(ind);
  while (!isalpha((int)c)) {
    ind++;
    if (ind == expr.length()) {
      break;
    }
    c = expr.at(ind);
  }
  int end = ind;
  while (isalpha((int)c)) {
    end++;
    if (expr.length() == end) break;
    c = expr.at(end);
  }
  next = (end == expr.length() ? -1 : end);
  std::string sub = expr.substr(ind, end - ind);
  //std::cout << sub << std::endl;
  Token token;
  if (sub.length() == 1) {
    token.type = TokenType::VAR;
    token.var = sub.at(0);
  }
  else if (sub == "AND") {
    token.type = TokenType::AND;
  }
  else if (sub == "OR") {
    token.type = TokenType::OR;
  }
  else if (sub == "NOT") {
    token.type = TokenType::NOT;
  }
  else {
    token.type = TokenType::UNDEFINED;
  }
  return token;
}
