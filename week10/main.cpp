#include <common.h>
#include <iostream>
#include <exception>
#include <Matrix.h>

i32 main() {

    try {

        std::cout << "char "    <<  sizeof(char)    << '\n';
        std::cout << "short "   <<  sizeof(short)   << '\n';
        std::cout << "int "     <<  sizeof(int)     << '\n';
        std::cout << "float "   <<  sizeof(float)   << '\n';
        std::cout << "double "  <<  sizeof(double)  << '\n';
        std::cout << "int* "    <<  sizeof(int*)    << '\n';
        std::cout << "double* " <<  sizeof(double*) << '\n';

        std::cout << "\nMatrix sizes\n";
        Numeric_lib::Matrix<i32> a(10);
        Numeric_lib::Matrix<i32> b(100);
        Numeric_lib::Matrix<f64> c(10);
        Numeric_lib::Matrix<i32, 2> d(10, 10);
        Numeric_lib::Matrix<i32, 3> e(10, 10, 10);
        std::cout << "1D i32 10 elem "       << sizeof(a) << '\n';
        std::cout << "1D i32 100 elem "      << sizeof(b) << '\n';
        std::cout << "1D f64 10 elem "       << sizeof(c) << '\n';
        std::cout << "2D i32 10*10 elem "    << sizeof(d) << '\n';
        std::cout << "3D i32 10*10*10 elem " << sizeof(e) << '\n';

        std::cout << "number of elements\n";
        
        std::cout << "a:\t" << a.size() << '\n';
        std::cout << "b:\t" << b.size() << '\n';
        std::cout << "c:\t" << c.size() << '\n';
        std::cout << "d:\t" << d.size() << '\n';
        std::cout << "e:\t" << e.size() << '\n';
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