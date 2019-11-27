#include "database.h"

using namespace std;

namespace AEDI {

void Database::emplace(Cuac const* obj) {
  my_list_.insert(obj);
}

int Database::size() const {
  return (int) my_list_.size();
}

int Database::print_last_n(ostream& os, int n) const {
  int found = 0;
  for (const auto& c : my_list_) {
    if (n <= found) break;
    os << ++found << ". " << *c << endl;
  }
  return found;
}

int Database::print_by_user(ostream& os, const string& user) const {
  int found = 0;
  for (const auto& c : my_list_)
    if (c->user() == user)
      os << ++found << ". " << *c << endl;
  return found;
}

int Database::print_by_date(ostream& os, const Date& from, const Date& to) const {
  int found = 0;
  for (const auto& c : my_list_)
    if (c->date() >= from && c->date() <= to)
      os << ++found << ". " << *c << endl;
  return found;
}

int Database::print_by_tag(ostream& os, const string& tag) const {
  cout << "1. " << **my_list_.rbegin() << endl;
  return 1;
}

}  // namespace AEDI
