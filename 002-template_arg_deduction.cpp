#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Note: There are not template argument deduction for class/struct templates

template <typename T> void meow(T one, T two) {
    cout << one << " " << two << endl;
}

// template argument deduction can't work in this case
// because template argument deduction can't look after scope resolution operator "::"
// Note: using templates with arguments like this is not recommended
template <typename T> void purr(typename make_unsigned<T>::type t) {
    /*
    Why doesn't template argument deduction work in this case?
    Because, if the source type is, for example, int or unsigned int, both 
    would result in the destination type being unsigned int. So, this makes 
    it not possible for template argument deduction to deduce the source type.
    */
    cout << t << endl;
}

int main() {
    meow<int>(17, 29);      // explicitly specifying template argument types
    // use this instead
    meow(17, 29);           // using template argument deduction
    // meow(17, 29L);              // This would fail because the two arguments have different types
    /* you can explicitly specify the argument types to resolve the ambiguity, 
       but passing the arguments with the correct types is a better approach */
    meow<long>(17, 29L);
    meow<int>(17, 29L);
    // purr(1234);
    purr<int>(1234);            // you have to explicitly specify the template argument type

    vector<int> v;
    v.push_back(1);
    v.push_back(7);
    v.push_back(2);
    v.push_back(9);

    sort(v.begin(), v.end());

    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << endl;
    }
}
