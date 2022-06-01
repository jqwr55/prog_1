#include <generic_containers.h>
#include <vector>


MyVector<double> Fill() {
    
    MyVector<double> ret;
    for(u32 i = 0; i < 10; i++) {
        ret.push_back(i * 2);
    }

    return ret;
}

void TestMyVector() {

    MyVector<double> mv;
    std::cout << mv.capacity() << std::endl;

    std::cout << std::endl;
    for(u32 i = 0; i < 18; i++) {
        mv.push_back(8.5);
        std::cout << mv.capacity() << std::endl;
    }

    MyVector<double> mv2(mv);
    std::cout << std::endl;
    for(u32 i = 0; i < mv2.size(); i++) {
        std::cout << mv2.at(i) << ' ';
    }
    std::cout << std::endl;

    MyVector<double> mv3{15.2, 18.6, 128.1};
    std::cout << std::endl;
    for(const auto& e : mv3) {
        std::cout << e << ' ';
    }

    mv3 = mv;
    std::cout << std::endl;
    for(u32 i = 0; i < mv3.size(); i++) {
        std::cout << mv3[i] << ' ';
    }
    std::cout << std::endl;

    MyVector<double> mv4 = Fill();
    std::cout << std::endl;
    for(u32 i = 0; i < mv4.size(); i++) {
        std::cout << mv4[i] << ' ';
    }

    MyVector<double> mv5{15.2, 18.6, 128.1};
    mv5 = Fill();


    std::cout << std::endl;
    std::cout << mv5 << std::endl;

    std::cout << std::endl;
    MyVector<double> mv6(10);
    std::cout << mv6.capacity() << std::endl;
}

i32 main() {

    TestMyVector();


    return 0;
}