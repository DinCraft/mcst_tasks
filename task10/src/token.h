#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <utility>

enum Token {
  AND, OR, NOT
};

std::pair<int,int> last_operation_bounds(const std::string &expr);

Token get_token_from(const std::string &expr, int ind);


#endif // TOKEN_H
