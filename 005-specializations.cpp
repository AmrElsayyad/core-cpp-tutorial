#include <iostream>
using namespace std;

template <typename T> struct Kitty {
    static void Meow() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

// Explicit Specialization
template <> struct Kitty<const char *> {
    static void Meow() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

// Partial Specialization
template <typename X> struct Kitty<X *> {
    static void Meow() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

template <typename T, typename U> struct Puppy {
    static void Bark() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

template <typename A, typename B> struct Puppy<A*, B> {
    static void Bark() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

template <typename X, typename Y> struct Puppy<X, Y*> {
    static void Bark() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

template <typename T> void foo(T) {
    cout << __PRETTY_FUNCTION__ << endl;
}

// Explicit Specialization
template <> void foo(double) {
    cout << "Specialized " << __PRETTY_FUNCTION__ << endl;
}

// Function Overload
void foo(long) {
    cout << __PRETTY_FUNCTION__ << endl;
}

// This is not a partial specialization, this is an overloaded template
template <typename X> void foo(X *) {
    cout << __PRETTY_FUNCTION__ << endl;
}

// It's not possible to partial specialize a function template

int main() {
    Kitty<int>::Meow();
    Kitty<const char *>::Meow();
    Kitty<double *>::Meow();

    Puppy<int, double>::Bark();
    Puppy<int *, double>::Bark();
    Puppy<int, double*>::Bark();
    // This is ambiguous
    // Puppy<int *, double*>::Bark();

    foo(1729);
    foo(0L);
    foo(1.0);
    foo(static_cast<double *>(nullptr));
}
