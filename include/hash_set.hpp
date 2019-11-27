
namespace AEDI {

template <class Key, class Hash, class Pred>
const int hash_set<Key, Hash, Pred>::kArrDefaultSize = 500;

template <class Key, class Hash, class Pred>
hash_set<Key, Hash, Pred>::hash_set() : size_(0), arr_(new bucket[kArrDefaultSize]), arrSize_(kArrDefaultSize) { }

template <class Key, class Hash, class Pred>
hash_set<Key, Hash, Pred>::~hash_set() {
  for (size_type i = 0; i < arrSize_; i++)  // Delete all entries
    for (auto& entry : arr_[i])
      delete entry;
  delete[] arr_;
}

template <class Key, class Hash, class Pred> inline
typename hash_set<Key, Hash, Pred>::iterator hash_set<Key, Hash, Pred>::end() const {
  return iterator(nullptr);
}

template <class Key, class Hash, class Pred> inline
bool hash_set<Key, Hash, Pred>::empty() const { return size_ == 0; }

template <class Key, class Hash, class Pred>
void hash_set<Key, Hash, Pred>::refactor() {
  int newArrSize = arrSize_*4;
  bucket* newArr = new bucket[newArrSize];
  for (size_type i = 0; i < arrSize_; ++i) {  // For each element in the table
    for (const auto& entry : arr_[i]) {
      int pos = hasher_(*entry)%newArrSize;   // Find it's new position
      auto it = newArr[pos].begin();
      while (it != newArr[pos].end() && !comparator_(**it, *entry))
        it++;
      if (it == newArr[pos].end()) {
        it = newArr[pos].insert(it, entry);   // And insert it there
      }
    }
  }
  arr_ = newArr;
  arrSize_ = newArrSize;
}

template <class Key, class Hash, class Pred>
typename hash_set<Key, Hash, Pred>::iterator hash_set<Key, Hash, Pred>::insert(const value_type& obj) {
  int pos = hasher_(obj)%arrSize_;  // Find obj's bucket
  auto it = arr_[pos].begin();
  while (it != arr_[pos].end() && !comparator_(**it, obj))
    it++;
  if (it == arr_[pos].end()) {      // If not yet inserted:
    value_type* entry = new value_type;
    *entry = obj;                   // Create entry
    it = arr_[pos].insert(it, entry);
    size_++;
    if (size_ > 2*arrSize_)         // Consider refactoring the table
      refactor();
  }
  return iterator(&**it);
}

template <class Key, class Hash, class Pred>
template <class T>
typename hash_set<Key, Hash, Pred>::iterator hash_set<Key, Hash, Pred>::find(const T& obj) const {
  int pos = hasher_(obj)%arrSize_;
  auto it = arr_[pos].begin();
  while (it != arr_[pos].end() && !comparator_(**it, obj))
    it++;
  if (it == arr_[pos].end())      // If obj wasn't found:
    return end();
  return iterator(&**it);         // Return iterator to object
}

template <class HashSet>
class hash_iterator {
public:
  typedef std::input_iterator_tag                iterator_category;
  typedef typename HashSet::key_type             value_type;
  typedef typename HashSet::key_type*            pointer;

  hash_iterator(pointer it) : val_(it) { }

  value_type& operator* () { return *val_; }
  value_type* operator->() { return &(operator*()); }

  bool operator==(const hash_iterator& rhs) { return val_ == rhs.val_; }
  bool operator!=(const hash_iterator& rhs) { return !(*this == rhs); }

private:
  pointer val_;
};

}  // namespace AEDI
