#include <common.h>
#include <exception>
#include <string>
#include <iostream>

class B1 {

    public:
        void f() {
            std::cout << "B1::f\n";
        }
        virtual void vf() {
            std::cout << "B1::vf\n";
        }
    private:
};

class D1 : public B1 {

    public:
        void vf() override {

        }
        void f() {
        }
    private:
};


i32 main(i32 argc, const char** argv) {

    try {

        B1 b1;
        b1.f();
        b1.vf();

        D1 d1;
        d1.f();
        d1.vf();

        B1& b1Ref = d1;
        b1Ref.f();
        b1Ref.vf();
		return 0;
	}
	catch(std::exception& e) {
		std::cerr << "exception caught " << e.what() << std::endl;
		return 1;
	}
	catch(...) {
		std::cerr << "Uknown exception" << std::endl;
		return 2;
	}

    return 0;
}