#include <iostream>
#include <memory>
using namespace std;

void meow(const string&) {
    cout << __PRETTY_FUNCTION__ << endl;
}

template <int N> void meow(const char (&)[N]) {
    cout << __PRETTY_FUNCTION__ << endl;
}

/* This function takes a constant reference to T */
template <typename T> void foo(const T&) {
    cout << __PRETTY_FUNCTION__ << endl;
}

/* This function takes a constant pointer to T */
template <typename T> void foo(const T*) {
    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T> void helper(const T&, false_type) {
    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T> void helper(const T&, true_type) {
    cout << __PRETTY_FUNCTION__ << endl;
}

template <typename T> void bar(const T& p) {
    helper(p, typename is_pointer<T>::type());
}

struct Base {};
struct Derived : Base {};
struct MoreDerived : Derived {};

void baz(Base *) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void baz(Derived *) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void qux(const shared_ptr<Base>&) {
    cout << __PRETTY_FUNCTION__ << endl;
}

void qux(const shared_ptr<Derived>&) {
    cout << __PRETTY_FUNCTION__ << endl;
}

int main() {
    meow("purr");
    string st("cat");
    meow(st);
    
    int * p1 = nullptr;
    foo(p1); // This would resolve to foo(const (int*)&)
    
    const int * p2 = nullptr;
    foo(p2); // This would resolve to foo(const (int)*)

    bar(p1);
    bar(1729);

    MoreDerived * md = nullptr;
    baz(md);

    shared_ptr<Derived> spd;
    qux(spd);

    // shared_ptr<MoreDerived> spmd;
    // qux(spmd); // This would fail
}