#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <utility>

using namespace std;

enum TokenType {
  OR, AND, NOT, VAR, UNDEFINED
};

struct Token {
  TokenType type;
  char var;

  void print();
};

int split_by_last_operation(const std::string &expr, pair<int,int> bounds, pair<pair<int,int>,pair<int,int>> &split);

Token get_token_from(const std::string &expr, int ind, int &next);


#endif // TOKEN_H
