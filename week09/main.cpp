#include <regex>
#include <iostream>
#include <string>
#include <fstream>

int main() {

    std::ifstream in {"file.txt"}; // input file
    
    if (!in) {
        std::cerr << "no file\n";
        return 1;
    } 
    std::regex pat{R"(\w{2}\s*\d{5}(–\d{4})?)"}; // postal code pattern

    int lineno = 0;
    for (std::string line; getline(in,line); ) { 
        // read input line into input buffer
        ++lineno;
    
        std::smatch matches; // matched strings go here
        if (std::regex_search(line, matches, pat)) {
            std::cout << lineno << ": " << matches[0] << '\n';
        }
    }

    return 0;
}