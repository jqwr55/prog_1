#include <common.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>

template <typename T>
struct S {

        S(const T v) : val(v) {}
        S() : val{} {}
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

    os.clear();
    os.ignore();
    return os;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const S<T>& v) {
    os << v.GetVal();
    return os;
}
template <typename T>
std::istream& operator >> (std::istream& os, S<T>& v) {
    os >> v.GetVal();
    return os;
}

template<typename T, u32 n, typename = std::enable_if_t< !std::is_same<T, char>::value> >
std::ostream& operator << ( std::ostream& os, const T(&v)[n] ) {

    os << '{';
    for(u32 i = 0; i < n; i++) {
        os << v[i] << ' ';
    }
    os << '}';
    return os;
}
template<typename T, std::size_t n>
std::istream& operator >> (std::istream& os, T(&v)[n] ) {

    for(u32 i = 0; i < n; i++) {
        T val;

        if( !(os >> val) ) {
            
            os.clear();
            os.ignore();

            for(; i < n; i++) {
                v[i] = {};
            }
            break;
        }
        v[i] = val;
    }
    return os;
}

template <class T, std::size_t n>
std::ostream& operator << (std::ostream& os, const std::array<T, n>& v) {

    os << '{';
    for(u32 i = 0; i < n; i++) {
        os << v[i] << ' ';
    }
    os << '}';
    return os;
}
template <class T, std::size_t n>
std::istream& operator >> (std::istream& os, std::array<T, n>& v) {

    for(u32 i = 0; i < n; i++) {
        T val;
        if(!(os >> val)) {

            os.clear();
            os.ignore();

            for(; i < n; i++) {
                v[i] = {};
            }
            break;
        }
        v[i] = val;
    }
    return os;
}

i32 main() {

    try {

        S<std::array<i32, 5>> s0;
        S< i32[5] > s1;
        S< std::array<char, 5> > s2;

        std::cin >> s0;
        std::cout << s0 << std::endl;

        std::cin >> s1;
        std::cout << s1 << std::endl;

        std::cin >> s2;
        std::cout << s2 << std::endl;

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