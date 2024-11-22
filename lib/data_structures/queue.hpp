#include <cmath>
#include <iostream>
#include <stdexcept>

/**
 * @brief Очередь
 */
template <typename T> class Queue {
private:
  T *array_;
  int capacity_;
  int tail_;
  int head_;

public:
  /**
   * @brief Конструктор класса очередь
   *
   * @param size размер очереди
   */
  Queue(int size = 10) : tail_(0), head_(0) {
    if (size < 0) {
      throw std::length_error("Size of the queue should be positive");
    }
    capacity_ = size;
    array_ = new T[capacity_];
  }

  /**
   * @brief Деструктор класса очередь
   */
  ~Queue() { delete[] array_; }

  /**
   * @brief Добавить элемент в очередь
   *
   * @param element ссылка на неизменяемый элемент
   */
  void enqueue(const T &element) {
    if (head_ == tail_ + 1 || tail_ == head_ + capacity_ - 1) {
      throw std::overflow_error("Queue overflow");
    }
    array_[tail_] = element;
    if (tail_ == capacity_ - 1) {
      tail_ = 0;
    } else {
      tail_++;
    }
  }

  /**
   * @brief Снять элемент с очереди
   *
   * @return T элемент очереди
   */
  T dequeue() {
    if (head_ == tail_) {
      throw std::underflow_error("Queue underflow");
    }
    T element = array_[head_];
    if (head_ == capacity_ - 1) {
      head_ = 0;
    } else {
      head_++;
    }
    return element;
  }

  /**
   * @brief Получить размер очереди
   *
   * @return int размер очереди
   */
  int size() {
    if (tail_ > head_) {
      return tail_ - head_;
    } else {
      return capacity_ - abs(head_ - tail_);
    }
  }

  /**
   * @brief Проверка, пустая ли очередь
   *
   * @return bool является ли очередь пустой, или нет
   */
  bool is_empty() {
    if (head_ == tail_) {
      return true;
    }
    return false;
  }

  class Iterator {
  private:
    Queue<T> &queue_;
    int current_;

  public:
    /**
     * @brief Конструктор для итератора
     *
     * @param q ссылка на очередь
     */
    Iterator(Queue<T> &q) : queue_(q), current_(q.head_) {}

    /**
     * @brief Конструктор для итератора
     *
     * @param q ссылка на очередь
     * @param pos позиция в очереди
     */
    Iterator(Queue<T> &q, int pos) : queue_(q), current_(pos) {}

    /**
     * @brief Метод доступа к элементу
     *
     * @return ссылка на текущий элемент
     */
    T &operator*() { return queue_.array_[current_]; }

    /**
     * @brief Продвинуть итератор вперед
     *
     * @return ссылка ни измененный итератор
     */
    Iterator &operator++() {
      current_ = (current_ + 1) % queue_.capacity_;
      return *this;
    }

    /**
     * @brief Оператор сравнения для итератора
     *
     * @return bool - равен ли итератор другому
     */
    bool operator!=(const Iterator &other) const {
      return current_ != other.current_ || &queue_ != &other.queue_;
    }

    /**
     * @brief Оператор присваивания для итератора
     *
     * @param Iterator ссылка на другой итератор
     */
    Iterator &operator=(const Iterator &other) {
      current_ = other.current_;
      queue_ = other.queue_;
      return *this;
    }
  };

  /**
   * @brief Вернуть итератор на начало очереди
   *
   * @return Iterator - новый итератор на начало очереди
   */
  Iterator begin() { return Iterator(*this, head_); }

  /**
   * @brief Вернуть итератор на конец очереди
   *
   * @return Iterator - новый итератор на конец очереди
   */
  Iterator end() { return Iterator(*this, tail_); }
};