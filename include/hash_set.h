#ifndef AEDI_hash_set_H_
#define AEDI_hash_set_H_

#include <iterator>
#include <functional>
#include <list>

namespace AEDI {

template <class HashSet>
class hash_iterator;

template <class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key> >
class hash_set {
 public:
  // types:
  typedef Key                      key_type;
  typedef Key                      value_type;
  typedef Hash                     hasher;
  typedef Pred                     key_equal;
  typedef hash_iterator<hash_set>  iterator;
  typedef hash_iterator<hash_set>  const_iterator;
  typedef int                      size_type;
  typedef ptrdiff_t                difference_type;

  hash_set();
  ~hash_set();

  iterator end() const;

  bool empty() const;
  size_type size() const;

  iterator insert(const value_type& obj);
  //void erase(iterator position);

  // Pos: User won't modify the reference returned
  // in a way that can alter it's hash value. If
  // that happens, it leads to undefined behavior.
  template <class T>
  iterator find(const T& obj) const;

 private:
  typedef std::list<value_type*>   bucket;
  friend iterator;
  static const int kArrDefaultSize;

  size_type size_;
  hasher hasher_;
  key_equal comparator_;
  bucket* arr_;
  size_type arrSize_;

  void refactor();
};

}  // namespace AEDI

#include "hash_set.hpp"

#endif
