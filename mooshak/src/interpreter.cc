#include "interpreter.h"

#include <iostream>
using namespace std;

#include "date.h"
#include "cuac.h"

namespace AEDI {

using std::string;
using std::cout;

void interpreter::process_mcuac() {
  MCuac *m = new MCuac();
  cin >> *m;
  global_db.emplace(m);
  cout << global_db.size() << " cuac" << endl;
}

void interpreter::process_pcuac() {
  PCuac *p = new PCuac();
  cin >> *p;
  global_db.emplace(p);
  cout << global_db.size() << " cuac" << endl;
}

void interpreter::process_last() {
  int n, total;
  cin >> n;
  cout << "last " << n << endl;
  total = global_db.print_last_n(cout, n);
  cout << "Total: " << total << " cuac" << endl;
}

void interpreter::process_follow() {
  string user;
  cin >> user;
  cout << "follow " << user << endl;
  int total = global_db.print_by_user(cout, user);
  cout << "Total: " << total << " cuac" << endl;
}

void interpreter::process_date() {
  Date from, to;
  cin >> from >> to;
  cout << "date " << from << " " << to << endl;
  int total = global_db.print_by_date(cout, from, to);
  cout << "Total: " << total << " cuac" << endl;
}

void interpreter::process_tag() {
  string tag;
  cin >> tag;
  cout << "tag " << tag << endl;
  int total = global_db.print_by_tag(cout, tag);
  cout << "Total: " << total << " cuac" << endl;
}

}  //namespace AEDI
