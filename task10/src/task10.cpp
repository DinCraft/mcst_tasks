#include "Expression.h"
#include "Token.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

// (A AND B) OR (C AND NOT D)
int main (int argc, char *argv[]) {
  string str;
  getline(cin, str);
  //cout << str << endl;
  //get_token_from(str, 0);

  str = remove_unused_spaces(str);
  int i = 0;
  set<char> alpha;
  while (1) {
    Token t = get_token_from(str, i, i);
    if (t.type == VAR) {
      alpha.insert(t.var);
    }
    if (i == -1) break;
  }
  if (str.at(0) != '(') {
    str = '(' + str + ')';
  }
  Expression expr(str);
  vector<char> characters = vector<char>(alpha.begin(), alpha.end());
  sort(characters.begin(), characters.end());
  for (int i = 0; i < characters.size(); i++) {
    cout << characters[i] << " ";
  }
  cout << "Result" << endl;
  int total = (int)pow(2, characters.size());
  for (int i = 0; i < total; i++) {
    int v = 0;
    int sum = 0;
    for (int j = 0; j < characters.size(); j++) {
      v = (1 << j) - ((i) & (1 << (j)));
      v = (1 << j);
      int n = ((i & (1 << (characters.size() - j - 1))) >> (characters.size() - j - 1));
      //cout << ((i & (1 << (characters.size() - j - 1))) >> (characters.size() - j - 1)) << " v: " << v << " ";
      cout << n << " ";
      sum += v * n;
    } 
    cout << expr.calculate(sum, characters) << endl;
  }
  //expr.print();
  return 0;
}
