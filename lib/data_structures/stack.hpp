#include <stdexcept>

/**
 * @brief Стек
 */
template <typename T> class Stack {
private:
  T *array_;
  int capacity_;
  int top_;

public:
  /**
   * @brief Конструктор класса Стек
   *
   * @param size вместимость стека
   */
  Stack(int size = 10) : top_(-1) {
    if (size < 0) {
      throw std::length_error("Size should be positive");
    }
    capacity_ = size;
    array_ = new T[capacity_];
  }

  /**
   * @brief Деструктор класса Стек
   */
  ~Stack() { delete[] array_; }

  /**
   * @brief Добавить элемент в стопку
   *
   * @param element ссылка на неизменяемый элемент
   */
  void push(const T &element) {
    if (top_ >= capacity_ - 1) {
      throw std::overflow_error("Stack overflow");
    }
    array_[++top_] = element;
  }

  /**
   * @brief Достать элемент из стопки
   *
   * @returns T - элемент с вершины Стека
   */
  T pop() {
    if (is_empty()) {
      throw std::underflow_error("Stack underflow");
    }
    return array_[top_--];
  }

  /**
   * @brief Проверить Стек на пустоту
   *
   * @returns Пуст ли Стек?
   */
  bool is_empty() const { return top_ == -1; }
};