#include <iostream>
#include <memory>
#include <stdexcept>

class IHashFunction {
public:
  virtual int64_t Hash(int64_t key);
};

class DivisionMethod : public IHashFunction {
private:
  uint64_t capacity;

public:
  DivisionMethod(uint64_t m) : capacity(m) {}
  ~DivisionMethod() {}
  virtual int64_t Hash(int64_t key) { return key % capacity; }
};

template <typename K, typename V> class HashTable {
private:
  LinkedList<AugDataEntry<K, V>> *table;
  std::shared_ptr<IHashFunction> hash_func;
  uint64_t capacity;

public:
  HashTable(uint64_t size = 10, std::shared_ptr<IHashFunction> obj =
                                    std::make_shared<DivisionMethod>())
      : capacity(size), hash_func{std::move(obj)} {
    table = new LinkedList<HashTableEntry<K, V>>[capacity];
  }

  ~HashTable() {}

  void insert(const HashTableEntry<K, V> &item) {
    table[hash_func.get()->Hash(item.key)].prepend(item);
  }

  HashTableEntry<K, V> *search(K key) {
    return table[hash_func.get()->Hash(key)].search(key);
  }

  void remove(const HashTableEntry<K, V> &item) {
    table[hash_func.get()->Hash(item.key)].remove(item);
  }
};
