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
        virtual void pvf() = 0;
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

class D2 : public D1 {

    public:
        void pvf() override {

        }
    private:
};

class B2 {

    public:
        virtual void pvf() = 0;
    private:
};
class D21 : public B2 {

    public:
        std::string str;
        void pvf() override {
            global_print("sc", str.c_str(), '\n');
        }
    private:
};
class D22 : public B2 {

    public:
        int num;
        void pvf() override {
            global_print("ic", num, '\n');
        }
    private:
};

void f(B2& b2) {

    b2.pvf();
}

i32 main(i32 argc, const char** argv) {

    byte mem[512];
    init_global_print(make_linear_allocator(mem, 512));

    D2 d2;
    d2.f();
    d2.vf();
    d2.pvf();

    D21 d21;
    D22 d22;
    f(d21);
    f(d22);

    global_io_flush();
    return 0;
}