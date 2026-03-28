#include "Expression.h"
#include "Token.h"
#include <iostream>
#include <string>

using namespace std;

// (A AND B) OR (C AND NOT D)
int main (int argc, char *argv[]) {
  string str;
  getline(cin, str);
  //cout << str << endl;
  //get_token_from(str, 0);

  str = remove_unused_spaces(str);
  /*int i = 0;
  while (1) {
    Token t = get_token_from(str, i, i);
    t.print();
    if (i == -1) break;
  }*/
  Expression expr(str);
  return 0;
}
