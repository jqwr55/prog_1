#include <fstream>
#include <iostream>
#include <exception>
#include <random>


int main() {

    try {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(-100, 1000);

        std::ofstream file("./week08/floats");
        for(int i = 0; i < 16; i++) {
            file << distr(eng) << std::endl;
        }

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

    return 0;
}