#include <iostream>
using namespace std;

#include "interpreter.h"
using namespace AEDI::interpreter;

int main () {
  ios_base::sync_with_stdio(false);
  string s;
  while (cin >> s) {
    if (s == "mcuac")
      process_mcuac();
    else if (s == "pcuac")
      process_pcuac();
    else if (s == "last")
      process_last();
    else if (s == "follow")
      process_follow();
    else if (s == "date")
      process_date();
    else if (s == "tag")
      process_tag();
    else if (s == "exit")
      break;
  }
}
