#ifndef AEDI_DATABASE_H_
#define AEDI_DATABASE_H_

#include <iostream>
#include <string>
#include <list>
#include <cmath>

#include "date.h"
#include "cuac.h"
#include "avl_tree.h"
#include "hash_set.h"

namespace AEDI {

class Database {
 public:
  Database();
  ~Database();

  int size() const;
  void emplace(const Cuac* obj);

  int print_last_n(std::ostream& os, int n) const;
  int print_by_user(std::ostream& os, const std::string& user) const;
  int print_by_date(std::ostream& os, const Date& from, const Date& to) const;
  int print_by_tag(std::ostream& os, const std::string& tag) const;

 private:
  struct TreeComp {
    inline bool operator() (const Cuac* lhs, const Cuac* rhs) const {
      return *lhs < *rhs;
    }
  };

  struct HashElement {
    std::list<const Cuac*> cuacs;
    // Pre: cuacs is not empty
    inline const std::string& user() const { return cuacs.front()->user(); }
  };

  struct HashComp {
    inline bool operator() (const HashElement& lhs, const HashElement& rhs) const {
      return lhs.user() == rhs.user();
    }
    inline bool operator() (const HashElement& lhs, const std::string& s) const {
      return lhs.user() == s;
    }
  };

  struct UserHash {
    static const int kHashBase = 31;
    static const int kMOD = 1e9+7;
    int operator() (const std::string& s) const {
      long long r = 0, b = 1;
      for (int i = 0; i < (int) s.size(); i++) {
        r = (b*r + std::abs((int)s[i]))%kMOD;
        b = (b*kHashBase)%kMOD;
      }
      return r;
    }

    int operator() (const HashElement& el) const {
      return operator() (el.user());
    }
  };

  hash_set<HashElement, UserHash, HashComp> cuac_by_user_;
  avl_tree<const Cuac*, TreeComp> cuac_tree_;

};

}  // namespace AEDI

#endif
