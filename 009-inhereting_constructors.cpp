#include <iostream>
using namespace std;

struct A {
    A() = delete;
    explicit A(const char *) { cout << __PRETTY_FUNCTION__ << endl; }
    A(int, int) { cout << __PRETTY_FUNCTION__ << endl; }
};

struct B : A {
    using A::A;
};

int main() {
    B b1("meow");
    B b2(10, 20);
}