#include <common.h>
#include <iostream>
#include <exception>

template<typename T>
class A {
    public:
        virtual T& Get() = 0;
        virtual ~A() {}

        T item;
};

template<typename T>
class B : public A<T> {

    public:
        B(T in) {
            item = in;
        }
        ~B() override {
            
        }
        T& Get() override {
            return item;
        }
    private:
};

i32 main() {

    try {

        auto b = new B<int>(0);
        delete b;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch(...) {
        std::cerr << "uknown exception\n";
        return 2;
    }

    std::cout.flush();
    return 0;
}