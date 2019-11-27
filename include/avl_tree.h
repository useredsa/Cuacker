#ifndef AEDI_AVL_TREE_H_
#define AEDI_AVL_TREE_H_

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cassert>

namespace AEDI {

template <class Tree>
class avl_iterator;

template <class Key, class Compare = std::less<Key> >
class avl_tree {
 public:
  // types:
  typedef Key                     key_type;
  typedef Key                     value_type;
  typedef Compare                 key_compare;
  typedef Compare                 value_compare;
  typedef Key&                    reference;
  typedef const Key&              const_reference;
  typedef Key*                    pointer;
  typedef const Key*              const_pointer;
  typedef avl_iterator<avl_tree>  iterator;
  typedef avl_iterator<avl_tree>  const_iterator;
  typedef ptrdiff_t               difference_type;
  typedef int                     size_type;

  avl_tree();
  ~avl_tree();

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  size_type size() const;

  iterator insert(const value_type& obj);
  //void erase(iterator position); // Could be added

  iterator find(const value_type& obj) const;
  iterator lower_bound(const value_type& obj) const;
  iterator upper_bound(const value_type& obj) const;

 private:
  struct Node;
  struct insert_functor;
  friend iterator;

  size_type size_;
  Node root_;
  value_compare comparator_;

  static int height(Node* node);
  static int balance_factor(Node* node);
  static void rotate_left(Node** node);
  static void rotate_right(Node** node);
};

}  // namespace AEDI

#include "avl_tree.hpp"

#endif
