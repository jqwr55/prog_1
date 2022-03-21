#include <common.h>
#include <exception>
#include <string>

class B1 {

    public:
        void f() {
            global_print("s", "B1::f\n");
        }
        virtual void vf() {
            global_print("s", "B1::vf\n");
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

    byte mem[512];
    init_global_print(make_linear_allocator(mem, 512));

    B1 b1;
    b1.f();
    b1.vf();

    D1 d1;
    d1.f();
    d1.vf();

    B1& b1Ref = d1;
    b1Ref.f();
    b1Ref.vf();

    

    global_io_flush();
    return 0;
}