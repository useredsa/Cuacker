#include "database.h"

#include <algorithm>

using std::string;
using std::ostream;

namespace AEDI {

Database::Database() { }

Database::~Database() {
  for (const auto& c : cuac_tree_)
    delete c;
}

int Database::size() const {
  return cuac_tree_.size();
}

void Database::emplace(const Cuac* obj) {
  cuac_tree_.insert(obj);

  auto it = cuac_by_user_.find(obj->user());  // Look in hash table
  if (it == cuac_by_user_.end()) {  // obj is the first cuac of a user
    HashElement to_insert;          // Create the entry for a given user
    to_insert.cuacs.push_front(obj);
    it = cuac_by_user_.insert(to_insert);
  } else {                          // The entry for obj->user() already exists
    auto it2 = std::lower_bound(it->cuacs.begin(), it->cuacs.end(), obj, TreeComp());
    it->cuacs.insert(it2, obj);
  }
}

int Database::print_last_n(ostream& os, int n) const {
  int found = 0;
  for (const auto& c : cuac_tree_) {
    if (n == found) break;
    os << ++found << ". " << *c << '\n';
  }
  return found;
}

int Database::print_by_user(ostream& os, const string& user) const {
  int found = 0;
  auto it = cuac_by_user_.find(user);
  if (it != cuac_by_user_.end()) { // If there is an entry in the table for this user
    for (const auto& c : it->cuacs)
      os << ++found << ". " << *c << '\n';
  }
  return found;
}

int Database::print_by_date(ostream& os, const Date& from, const Date& to) const {
  int found = 0;
  const DateCuac* tmp = new DateCuac(to);
  auto it = cuac_tree_.lower_bound(tmp);
  while (it != cuac_tree_.end() && (**it).date() >= from) {
      os << ++found << ". " << **it++ << '\n';
  }
  return found;
}

int Database::print_by_tag(ostream& os, const string& tag) const {
  if (cuac_tree_.size() == 0) return 0;
  os << "1. " << **cuac_tree_.begin() << '\n';
  return 1;
}

}  // namespace AEDI
