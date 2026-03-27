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

  string s = remove_unused_spaces(str);
  //int i = 0;
  split_by_last_operation(s);
  /*while (i != -1) {
    Token t = get_token_from(str, i, i);
    t.print();
  }*/
  return 0;
}
