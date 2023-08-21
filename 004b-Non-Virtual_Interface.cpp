/* 
NVI stands for Non-Virtual Interface. 
NVI allows us to refactor before and after code fragments at the base class. 
The NVI idiom is based on 4 guidelines outlined by Herb Sutter in his article named “Virtuality”. 
Quoting Herb:
#1: Prefer to make interfaces nonvirtual, using Template Method design pattern.
#2: Prefer to make virtual functions private.
#3: Only if derived classes need to invoke the base implementation of a virtual function, 
    make the virtual function protected.
#4: A base class destructor should be either public and virtual, or protected and nonvirtual.
NVI is an implementation of the Template Method Pattern using dynamic dispatch in C++.
A pattern is more general than an idiom, and languages may use different idioms to implement the pattern.
 */
#include <iostream>
#include <memory>
using namespace std;

class Shape {
public:
    Shape() {}
    virtual ~Shape() {}

    void draw(int x, int y) {
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";

        cout << __PRETTY_FUNCTION__ << " with x = " << x << " and y = " << y << endl;

        do_draw(x, y);

        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    }

private:
    // Private to make the class non-copiable and non-assignable
    // You can use "= delete" instead
    Shape(const Shape&);
    Shape& operator=(const Shape&);

    virtual void do_draw(int x, int y) = 0;
};

class Polygon : public Shape {
private:
    virtual void do_draw(int x, int y) override {
        cout << __PRETTY_FUNCTION__ << " with x = " << x << " and y = " << y << endl;
    }
};

int main() {
    shared_ptr<Shape> shape = make_shared<Polygon>();
    shape->draw(11, 22);
}
