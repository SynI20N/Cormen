#include "doubly_linked_list.hpp"
#include <iostream>

int main() {
    DoublyLinkedList<std::string> list;
    list.prepend("leonid");
    list.prepend("roma");
    list.prepend("pavel");
    list.prepend("mise");
    Node<std::string>* node = list.search("haha");
    if(!node) {
        std::cout << "Значение не найдено" << '\n';
    }
    else {
        std::cout << "Нашли значение" << '\n';
    }
    std::cout << list << '\n';
    list.reverse();
    std::cout << list << '\n';
    list.remove("leonid");
    std::cout << list << '\n';
    return 0;
}