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
  cout << s << endl;
  for (int i = 0; i < s.length(); i++) {
    cout << i << " " << s.at(i) << endl;
  }
  cout << endl;
  //int i = 0;
  pair<pair<int,int>,pair<int,int>> bounds = split_by_last_operation(s, pair<int,int>(0, s.length()));
  cout << bounds.first.first << endl;
  /*while (i != -1) {
    Token t = get_token_from(str, i, i);
    t.print();
  }*/
  return 0;
}
