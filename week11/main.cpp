#include <common.h>
#include <iostream>
#include <exception>

template<typename T>
class A {
    public:
        virtual void Print() = 0;
};

template<typename T>
class B : public A<T> {

    public:
        void Print() override {
            std::cout << "Hello I am a B" << std::endl;
        }
    private:
};

i32 main() {

    try {

        auto b = new B<int>();
        delete b;
        
        std::cout.flush();
        return 0;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch(...) {
        std::cerr << "uknown exception" << std::endl;
        return 2;
    }

}