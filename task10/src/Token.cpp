#include "Token.h"
#include <cctype>
#include <iostream>
#include <string>

int split_by_last_operation(const std::string &expr, pair<int,int> bounds, pair<pair<int,int>,pair<int,int>> &split) {
  // эти переменные описывают уровень вложенности скобок
  int level = 0;
  int min_level = 10;
  int i1 = 0;
  TokenType min_prior = NOT;
  int min_op_id = 0;
  int op_length = 3;
  int operator_count = 0;
  for (int i = bounds.first; i < bounds.second; i++) {
    if (expr.at(i) == '(') {
      level++;
    }
    else if (expr.at(i) == ')') {
      level--;
    }
    else {
      if (i1 >= i) continue;
      i1 = i;
      Token token = get_token_from(expr, i1, i1);
      if (token.type != VAR && token.type != UNDEFINED) {
        operator_count++;
      }
      if (i == -1) break;
      i--;
      //cout << "char: " << expr.at(i) << endl;
      // определяем последнюю операцию
      if (level <= min_level && token.type != VAR) {
        if (min_prior == OR) {
          if (token.type == OR) {
            min_op_id = i;
            min_level = level;
            min_prior = token.type;
          }
        }
        else if (min_prior == AND) {
          if (token.type != NOT) {
            min_op_id = i;
            min_level = level;
            min_prior = token.type;
          }
        }
        else if (min_prior == NOT) {
          min_op_id = i;
          min_level = level;
          min_prior = token.type;
        }
      }
      //cout << level << ": ";
      //token.print();
      //cout << "=====" << endl;
    }
    if (min_prior == OR) op_length = 2;
  }
  if (operator_count == 0 || (operator_count == 1 && level == NOT)) return 1;
  split.first.first = bounds.first;
  split.first.second = min_op_id + 1;
  split.second.first = min_op_id + 1 + op_length;
  split.second.second = bounds.second;
  return 0;
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
