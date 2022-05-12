#include <common.h>
#include <iostream>
#include <exception>
#include <Matrix.h>
#include <MatrixIO.h>
#include <cmath>
#include <complex>

i32 main() {

    try {

        int v;
        while(std::cin >> v) {

            if(v >= 0) {
                std::cout << "sqrt " << sqrt(v) << std::endl;
            }
            else {
                std::cout << "no sqrt" << std::endl;
            }
        }

        std::cin.clear();
        std::cin.ignore();

        std::cout << "Enter 10 floats" << std::endl;
        Numeric_lib::Matrix<f64> mat(10);
        for(u32 i = 0; i < 10; i++) {
            f64 n;
            std::cin >> n;
            mat[i] = n;
        }
        std::cout << mat << std::endl;

        std::cout << "Enter dimensions of multiplication table(n,m)" << std::endl;
        i32 n;
        i32 m;
        std::cin >> n >> m;
        Numeric_lib::Matrix<f64, 2> table(n, m);
        for(u32 i = 0; i < n; i++) {
            for(u32 k = 0; k < m; k++) {
                table[i][k] = (i+1) * (k+1);
            }
        }
        std::cout << table << std::endl;

        std::cout << "Enter 10 complex<float> number (r,i)" << std::endl;
        Numeric_lib::Matrix<std::complex<f64>> complexes(10);
        std::complex<f64> sum{};
        for(u32 i = 0; i < 10; i++) {
            std::cin >> complexes[i];
            sum += complexes[i];
        }
        std::cout << "sum of complexes " << sum << ". complexes:\n" << complexes << std::endl;

        std::cout << "Enter 6 integer numbers" << std::endl;
        Numeric_lib::Matrix<int,2> matInt(2,3);
        for(u32 i = 0; i < 6; i++) {
            std::cin >> matInt[i / 3][i % 3];
        }
        std::cout << matInt << std::endl;
        
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

    return 0;
}