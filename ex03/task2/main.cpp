
#include <iostream>

using namespace std;

class A {
public:
int a;
    A(){a=4;};
};

A* return_wrong_ptr(){
    A a = A();
    A *b=&a;
    return b;
}

A& return_wrong_ref(){
    A a=A();
    A &b=a;
    return b;
}

int main(int argc, char*argv)
{
    cout << return_wrong_ptr() << endl;
    cout << return_wrong_ptr()->a << endl;


   // cout << return_wrong_ref() << endl;
    cout << return_wrong_ref().a << endl;
}