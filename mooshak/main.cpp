#include <iostream>
using namespace std;

#include "interpreter.h"
using namespace AEDI::interpreter;

int main () {
  ios_base::sync_with_stdio(false);
  while (read_command());
}
