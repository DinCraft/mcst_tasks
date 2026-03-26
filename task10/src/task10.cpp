#include "token.h"
#include <iostream>
#include <string>

using namespace std;

int main (int argc, char *argv[]) {
  string str;
  getline(cin, str);
  //cout << str << endl;
  for (int i = 0; i < 20; i++) {
    cout << i << endl;
    get_token_from(str, i);
  }
  //get_token_from(str, 0);
  return 0;
}
