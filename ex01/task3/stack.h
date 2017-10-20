#ifndef UIBK_703807_EX01_TASK3_STACK_H_
#define UIBK_703807_EX01_TASK3_STACK_H_

#include <initializer_list>
#include <vector>

class Stack {
    std::vector<int> data;

  public:
    Stack() = default;
    Stack(std::initializer_list<int> l) : data(l) {}

    bool empty() const;
    std::size_t size() const;

    void push(int value);
    int pop();
    int peek();
};

#endif  // UIBK_703807_EX01_TASK3_STACK_H_
