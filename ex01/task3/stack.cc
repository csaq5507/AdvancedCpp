#include "stack.h"

#include <cassert>

using namespace std;

bool Stack::empty() const { return data.empty(); }

size_t Stack::size() const { return data.size(); }

void Stack::push(int value) { data.push_back(value); }

int Stack::pop() {
    assert(!data.empty());
    int v = data.back();
    data.pop_back();
    return v;
}

int Stack::peek() {
    assert(!data.empty());
    return data.back();
}
