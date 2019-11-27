
namespace AEDI {

template <class Key, class Compare>
struct avl_tree<Key, Compare>::Node {
  int height;
  Node *left_child, *right_child;
  Node *prev, *next;
  const value_type val;

  Node(Node* prev, Node* next, const value_type& val) :
    height(0),
    left_child(nullptr),
    right_child(nullptr),
    prev(prev),
    next(next),
    val(val)
  { }
  ~Node() { delete left_child; delete right_child; }
};

template <class Key, class Compare>
avl_tree<Key, Compare>::avl_tree() : size_(0), root_(nullptr, nullptr, value_type()) {
  root_.next = &root_;
}

template <class Key, class Compare>
avl_tree<Key, Compare>::~avl_tree() { delete root_.left_child; } // Nodes free their children

template <class Key, class Compare> inline
typename avl_tree<Key, Compare>::iterator avl_tree<Key, Compare>::begin() {
  return iterator(root_.next);
}

template <class Key, class Compare> inline
typename avl_tree<Key, Compare>::const_iterator avl_tree<Key, Compare>::begin() const {
  return const_iterator(root_.next);
}

template <class Key, class Compare> inline
typename avl_tree<Key, Compare>::iterator avl_tree<Key, Compare>::end() {
  return iterator(&root_);
}

template <class Key, class Compare> inline
typename avl_tree<Key, Compare>::const_iterator avl_tree<Key, Compare>::end() const {
  return const_iterator(&root_);
}

template <class Key, class Compare> inline
bool avl_tree<Key, Compare>::empty() const { return size_ == 0; }

template <class Key, class Compare> inline
typename avl_tree<Key, Compare>::size_type avl_tree<Key, Compare>::size() const { return size_; }

template <class Key, class Compare> inline
int avl_tree<Key, Compare>::height(Node* node) {
  if (node == nullptr) return -1;
  return node->height;
}

template <class Key, class Compare> inline
int avl_tree<Key, Compare>::balance_factor(Node* node) {
  if (node == nullptr) return 0;
  return height(node->left_child)-height(node->right_child);
}

template <class Key, class Compare>
void avl_tree<Key, Compare>::rotate_left(Node** node) {
  Node* tmp = (*node)->left_child; // Pre: node->left_child != nullptr
  (*node)->left_child = tmp->right_child;
  tmp->right_child = *node;
  *node = tmp;
}

template <class Key, class Compare>
void avl_tree<Key, Compare>::rotate_right(Node** node) {
  Node* tmp = (*node)->right_child; // Pre: node->right_child != nullptr
  (*node)->right_child = tmp->left_child;
  tmp->left_child = *node;
  *node = tmp;
}

template <class Key, class Compare>
struct avl_tree<Key, Compare>::insert_functor {
  const value_type& to_insert;
  Node* location;
  avl_tree<Key, Compare>& parent;

  insert_functor(const value_type& to_insert, avl_tree<Key, Compare>& parent) :
    to_insert(to_insert), parent(parent) { }

  void operator() (Node** node_ptr) {
    if (*node_ptr == nullptr) { // Insert here
      if (parent.empty()) { // Special case for first insert
        assert(node_ptr == &parent.root_.left_child);
        *node_ptr = new Node(&parent.root_, &parent.root_, to_insert);
        parent.root_.prev = parent.root_.next = *node_ptr;
      } else if (parent.comparator_(to_insert, location->val)) {  // Insert as left child
        *node_ptr = new Node(location->prev, location, to_insert);
        location->prev->next = *node_ptr;
        location->prev = *node_ptr;
      } else {  // Insert as right child
        *node_ptr = new Node(location, location->next, to_insert);
        location->next->prev = *node_ptr;
        location->next = *node_ptr;
      }
      parent.size_++;
      location = *node_ptr; // Set to know where the new node was inserted
      return;
    }

    location = *node_ptr; // Set to know parent of inserted node

    if (parent.comparator_(to_insert, (**node_ptr).val)) {
      operator()(&(**node_ptr).left_child); // Insert in left subtree
      if (balance_factor(*node_ptr) > 1) {  // node is left heavy
        if (balance_factor((**node_ptr).left_child) > 0) rotate_left(node_ptr);
        else {
          rotate_right(&(**node_ptr).left_child);
          rotate_left(node_ptr);
        }
      }
    } else if (parent.comparator_((**node_ptr).val, to_insert)) {
      operator()(&(**node_ptr).right_child); // Insert in right subtree
      if (balance_factor(*node_ptr) < -1) {  // node is right heavy
        if (balance_factor((**node_ptr).right_child) < 0) rotate_right(node_ptr);
        else {
          rotate_left(&(**node_ptr).right_child);
          rotate_right(node_ptr);
        }
      }
    } else return; // Node already inserted

    // Update height
    (**node_ptr).height = std::max(height((**node_ptr).left_child), height((**node_ptr).right_child))+1;
  }
};

template <class Key, class Compare> inline
typename avl_tree<Key, Compare>::iterator avl_tree<Key, Compare>::insert(const value_type& obj) {
  insert_functor functor(obj, *this);
  functor(&root_.left_child);
  return iterator(functor.location);
}

template <class Key, class Compare>
typename avl_tree<Key, Compare>::iterator avl_tree<Key, Compare>::find(const value_type& obj) const {
  Node* at = root_.left_child;
  while (at != nullptr) {
    if (comparator_(obj, at->val))
      at = at->left_child;
    else if (comparator_(at->val, obj))
      at = at->right_child;
    else
      return iterator(at);
  }
  return end();
}

template <class Key, class Compare>
typename avl_tree<Key, Compare>::iterator avl_tree<Key, Compare>::lower_bound(const value_type& obj) const {
  Node* went_left_at = nullptr;
  Node* at = root_.left_child;
  while (at != nullptr) { //TODO use prev instead
    if (comparator_(obj, at->val)) {
      went_left_at = at;
      at = at->left_child;
    } else if (comparator_(at->val, obj)) {
      at = at->right_child;
    } else {
      return iterator(at);
    }
  }
  if (went_left_at == nullptr) return end();
  return iterator(went_left_at);
}

template <class Key, class Compare>
typename avl_tree<Key, Compare>::iterator avl_tree<Key, Compare>::upper_bound(const value_type& obj) const {
  Node* went_left_at = nullptr;
  Node* at = root_.left_child;
  while (at != nullptr) {
    if (comparator_(obj, at->val)) {
      went_left_at = at;
      at = at->left_child;
    } else {
      at = at->right_child;
    }
  }
  if (went_left_at == nullptr) return end();
  return iterator(went_left_at);
}

template <class Tree>
class avl_iterator {
public:
  typedef std::bidirectional_iterator_tag  iterator_category;
  typedef const typename Tree::key_type    value_type;
  typedef const typename Tree::Node*       pointer;

  avl_iterator(pointer node) : node_(node) { }

  value_type& operator* () { return node_->val; }
  value_type* operator->() { return &(operator*()); }

  avl_iterator& operator++();
  avl_iterator  operator++(int);
  avl_iterator& operator--();
  avl_iterator  operator--(int);

  bool operator==(const avl_iterator& rhs) { return node_ == rhs.node_; }
  bool operator!=(const avl_iterator& rhs) { return !(*this == rhs); }

private:
  pointer node_;
};

template <class Tree>
avl_iterator<Tree>& avl_iterator<Tree>::operator++() {
  node_ = node_->next;
  return *this;
}

template <class Tree>
avl_iterator<Tree> avl_iterator<Tree>::operator++(int) {
  avl_iterator tmp(*this);
  ++(*this);
  return tmp;
}

template <class Tree>
avl_iterator<Tree>& avl_iterator<Tree>::operator--() {
  node_ = node_->prev;
  return *this;
}

template <class Tree>
avl_iterator<Tree> avl_iterator<Tree>::operator--(int) {
  avl_iterator tmp(*this);
  --(*this);
  return tmp;
}

}  // namespace AEDI
