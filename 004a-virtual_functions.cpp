#include <iostream>
#include <memory>
using namespace std;

class Shape {
public:
    Shape() {}
    virtual ~Shape() {}

    virtual void draw(int x, int y) {
        cout << __PRETTY_FUNCTION__ << " with x = " << x << " and y = " << y << endl;
    }

private:
    // To make the class non-copiable and non-assignable
    // You can use "= delete" instead
    Shape(const Shape&);
    Shape& operator=(const Shape&);
};

class Polygon : public Shape {
public:
    virtual void draw(int x, int y) {
        cout << __PRETTY_FUNCTION__ << " with x = " << x << " and y = " << y << endl;
    }
};

class Evilgon : public Shape {
public:
    virtual void draw(double x, double y) 
    // This attribute will make it fail because it's not matching the base signature:
    // override 
    {
        cout << __PRETTY_FUNCTION__ << " with x = " << x << " and y = " << y << endl;
    }
};

class Triangle final : public Polygon {
public:
    virtual void draw(int x, int y) override {
        cout << __PRETTY_FUNCTION__ << " with x = " << x << " and y = " << y << endl;
    }
};

// This would fail because class Triangle is final
// class BermudaTriangle : public Triangle {
// public:
//     virtual void draw(double x, double y) {
//         cout << __PRETTY_FUNCTION__ << " with x = " << x << " and y = " << y << endl;
//     }
// };

int main() {
    shared_ptr<Shape> shape = make_shared<Polygon>();
    shape->draw(11, 22);
    shape = make_shared<Evilgon>();
    shape->draw(33, 44);
    shape->draw(33.0f, 44.0f);
}
