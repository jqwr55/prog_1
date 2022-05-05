#include <common.h>
#include <exception>
#include <string>
#include <iostream>
#include <vector>

struct Person {
    public:
        Person(std::string first, std::string last, int a) : firstName(first), lastName(last), age(a) {

            if( a < 0 || a > 150 ) {
                throw std::runtime_error("Age error");
            }
            if(!CheckString(first) || !CheckString(last) && first.size() > 0 && last.size() > 0) {
                throw std::runtime_error("invalid character in name");;
            }
        }
        Person() {}

        const std::string& LastName() const {
            return lastName;
        }
        const std::string& FirstName() const {
            return firstName;
        }
        const int& Age() const {
            return age;
        }
        std::string& GetFirstName() {
            return firstName;
        }
        std::string& GetLastName() {
            return lastName;
        }
        int& GetAge() {
            return age;
        }
    private:
        bool CheckString(const std::string& str) const {

            const char invalidChars[] = {';', ':', '\"', '\'', '[', ']', '*', '&', '^', '%', '$', '#', '@', '!'};
            for(u32 i = 0; i < str.size(); i++) {
                for(u32 k = 0; k < SIZE_OF_ARRAY(invalidChars); k++) {
                    if(invalidChars[k] == str[i]) {
                        return false;
                    }
                }
            }
            return true;
        }
        std::string firstName;
        std::string lastName;
        int age;
};
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.FirstName() << ' ' << p.LastName() << ' ' << p.Age();
    return os;
}
std::istream& operator>>(std::istream& os, Person& p) {
    os >> p.GetFirstName();
    os >> p.GetLastName();
    os >> p.GetAge();
    return os;
}

i32 main(i32 argc, const char** argv) {

    try {

        std::cout << "Enter Persons" << std::endl;
        std::vector<Person> persons;
        for(Person p; std::cin >> p;) {
            persons.push_back(p);
        }
        for(const auto& i : persons) {
            std::cout << i << std::endl;
        }

        // Person error test
        Person("%", "Goofy", 10);
       return 0;
    }
    catch(std::exception& e) {
	    std::cerr << e.what() << std::endl;
		return 1;
	}
	catch(...) {
	    std::cerr << "uknown exception caught" << std::endl;
		return 2;
	}

}