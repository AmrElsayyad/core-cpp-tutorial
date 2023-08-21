#include <initializer_list>
#include <iostream>

template<typename T>
void print_impl(const T &t)
{
    std::cout << t << '\n';
}

template<typename ... T>
void print(const T& ... t)
{
    /* 
        The comma operator will evaluate the first expression then the second 
        and finally return the second. We do this because initializer_list<int>
        expects a list of ints, and we only care about invoking the function. 
    */
    (void)std::initializer_list<int>{ (print_impl(t), 0)... };
}

int f1()
{
    std::cout << "f1\n";
    return 1;
}

int f2()
{
    std::cout << "f2\n";
    return 2;
}

int main()
{
    print("Hello", "World", 1, 2, 3, 5.3f);
    
    /*
    order of evaluation for "gcc and g++" is from right to left
    so f2 is invoked first and its output was retrieved
    then f1 is invoked second and its output was retrieved
    finally the print function is invoked with arguments 1, 2

    but for "clang" the order of evaluation is left to right
    so f1 is invoked first and its output was retrieved
    then f2 is invoked second and its output was retrieved
    finally the print function is invoked with arguments 1, 2
    */
    print(f1(), f2());
}
