#include "interpreter.h"

#include <iostream>

#include "date.h"
#include "cuac.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

namespace AEDI {
namespace interpreter {

Database global_db;

void process_mcuac() {
  MCuac *m = new MCuac();
  cin >> *m;
  global_db.emplace(m);
  cout << global_db.size() << " cuac\n";
}

void process_pcuac() {
  PCuac *p = new PCuac();
  cin >> *p;
  global_db.emplace(p);
  cout << global_db.size() << " cuac\n";
}

void process_last() {
  int n, total;
  cin >> n;
  cout << "last " << n << '\n';
  total = global_db.print_last_n(cout, n);
  cout << "Total: " << total << " cuac" << endl;
}

void process_follow() {
  string user;
  cin >> user;
  cout << "follow " << user << '\n';
  int total = global_db.print_by_user(cout, user);
  cout << "Total: " << total << " cuac" << endl;
}

void process_date() {
  Date from, to;
  cin >> from >> to;
  cout << "date " << from << " " << to << '\n';
  int total = global_db.print_by_date(cout, from, to);
  cout << "Total: " << total << " cuac" << endl;
}

void process_tag() {
  string tag;
  cin >> tag;
  cout << "tag " << tag << '\n';
  int total = global_db.print_by_tag(cout, tag);
  cout << "Total: " << total << " cuac" << endl;
}

bool read_command() {
  string s;
  if (!(cin >> s)) return false;  // No more commands
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
  else return false;    // Command exit or anything else

  return true;
}

}  //namespace interpreter
}  //namespace AEDI
