#ifndef DOUBLY_LINKED_HPP
#define DOUBLY_LINKED_HPP

#include <memory>
#include <ostream>

/**
 * @brief Ячейка
 */
template <typename V> struct Node {
  std::unique_ptr<V> val; // Значение
  Node<V> *next; // Указатель на следующий элемент
  Node<V> *prev; // Указатель на предыдущий элемент

  Node(const V &some_val) { val = std::make_unique<V>(some_val); }
  Node(const Node<V> &other) {
    V value(*(other.val));
    val = std::make_unique<V>(value);
    next = other.next;
    prev = other.prev;
  }
};

/**
 * @brief Двусвязный список
 *
 * @param T тип значений
 */
template <typename T> class DoublyLinkedList {
  typedef Node<T> ListNode;

private:
  ListNode *head_; // Указатель на начало списка

public:
  /**
   * @brief Конструктор класса двусвязный список
   */
  DoublyLinkedList() : head_{} {}

  /**
   * @brief Деструктор класса двусвязный список
   */
  ~DoublyLinkedList() {
    ListNode *next = head_->next;
    ListNode *curr = head_;
    do {
      delete curr;
      curr = next;
      next = next->next;
    } while (curr != head_);
  }

  /**
   * @brief Поиск элемента по значению
   *
   * @param key искомое значение
   * @returns множественная ссылка на ячейку
   */
  ListNode* search(const T &key) {
    if (!head_) {
      return nullptr;
    }
    ListNode *curr = head_;
    while (curr->next != head_ && *(curr->val) != key) {
      curr = curr->next;
    }
    if (*(curr->val) == key) {
      return curr;
    }
    return nullptr;
  }

  /**
   * @brief Вставить значение в начало списка
   *
   * @param val значение для вставки
   */
  void prepend(const T &val) {
    ListNode *n = new ListNode(val);
    if (head_ != nullptr) {
      n->next = head_;
      n->prev = head_->prev;
      head_->prev->next = n;
      head_->prev = n;
    } else {
      n->next = n;
      n->prev = n;
    }
    head_ = n;
  }

  /**
   * @brief Удаление элемента по ссылке
   *
   * @param x ссылка на ячейку
   */
  void remove(ListNode *x) {
    x->prev->next = x->next;
    x->next->prev = x->prev;
    if (head_ == x) {
      head_ = x->next;
    }
    delete x;
  }

  /**
   * @brief Удаление элемента по значению
   *
   * @param val значение, которое надо удалить
   */
  void remove(const T &val) {
    ListNode* n = search(val);
    if (n) {
      remove(n);
    }
  }

  /**
   * @brief Оператор вывода списка в поток
   *
   * @param os поток вывода
   * @param l двусвязный список
   * @returns ссылка на обновленный поток вывода
   */
  template <typename V>
  friend std::ostream &operator<<(std::ostream &os,
                                  const DoublyLinkedList<V> &l) {
    if (l.head_ == nullptr) {
      return os;
    }
    ListNode *x = l.head_;
    do {
      os << "{" << *(x->val) << "}=";
      x = x->next;
    } while (x != l.head_);
    return os;
  }

  /**
   * @brief Инвертировать список
   */
  void reverse() {
    if (head_ == nullptr) {
      return;
    }
    ListNode *curr = head_;
    do {
      std::swap(curr->next, curr->prev);
      curr = curr->prev;
    } while (curr != head_);
    head_ = curr->next;
  }
};

#endif
