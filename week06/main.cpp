#include <common.h>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct S {
        S(const T v) : val(v) {}
        const T& GetVal() const;
        T& GetVal();

        S& operator = (const T&);
    private:
        T val;
};

template<typename T>
const T& S<T>::GetVal() const {
    return val;
}
template<typename T>
T& S<T>::GetVal() {
    return val;
}
template<typename T>
S<T>& S<T>::operator = (const T& v) {
    val = v;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    os << '{';
    for(u32 i = 0; i < v.size(); i++) {
        os << v[i] << ' ';
    }
    os << '}';
    return os;
}
template <typename T>
std::istream& operator >> (std::istream& os, std::vector<T>& v) {
    for(T i; os >> i;) {
        v.push_back(i);
    }
    return os;
}

template<typename T>
void read_val(T& v) {
    std::cin >> v.GetVal();
}

i32 main() {

    try {
        S<i32> s0(0);
        S<char> s1('q');
        S<f64> s2 = 3.14;
        S<std::string> s3("Hello");
        S<std::vector<i32>> s4({0,1,2,3,4});

        std::cout << s0.GetVal() << std::endl;
        std::cout << s1.GetVal() << std::endl;
        std::cout << s2.GetVal() << std::endl;
        std::cout << s3.GetVal() << std::endl;
        std::cout << s4.GetVal() << std::endl;

        std::cout << "enter an int" << std::endl;
        read_val(s0);
        std::cout << "enter a char" << std::endl;
        read_val(s1);
        std::cout << "enter a double" << std::endl;
        read_val(s2);
        std::cout << "enter a string" << std::endl;
        read_val(s3);
        std::cout << "enter multiple ints" << std::endl;
        read_val(s4);

        std::cout << s0.GetVal() << std::endl;
        std::cout << s1.GetVal() << std::endl;
        std::cout << s2.GetVal() << std::endl;
        std::cout << s3.GetVal() << std::endl;
        std::cout << s4.GetVal() << std::endl;
    
        return 0;
	}
	catch(std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "Some exception" << std::endl;
		return 2;
	}

}