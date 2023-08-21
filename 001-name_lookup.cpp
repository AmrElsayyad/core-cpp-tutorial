#include <stdio.h>

namespace Foo {
    namespace Bar {
        template <typename T> struct Meow {
            void purr() {
                puts(__PRETTY_FUNCTION__);
            }
        };
    }

    using Bar::Meow;    // This drags out Foo::Bar::Meow so it can be used as Foo::Meow
}

template <> struct Foo::Meow<int> {
    void purr() {
        puts(__PRETTY_FUNCTION__);
    }
};

int main() {
    using Foo::Meow;
    Meow<long> l;
    l.purr();

    Meow<int> i;
    i.purr();
}
