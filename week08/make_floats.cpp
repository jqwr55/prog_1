#include <fstream>
#include <random>


int main() {

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(-100, 1000);

    std::ofstream file("./week08/floats");
    for(int i = 0; i < 16; i++) {
        file << distr(eng) << std::endl;
    }

    return 0;
}