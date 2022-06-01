#include <common.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <algorithm>

struct Item {

    std::string name;
    i32 iid;
    f64 value;
};
std::ifstream& operator >> (std::ifstream& is, Item& out) {

    is >> out.name;
    is >> out.iid;
    is >> out.value;
    return is;
}
std::ostream& operator << (std::ostream& os, const Item& i) {

    os << i.name << ' ' << i.iid << ' ' << i.value;
    return os;
}
bool cmp_strs(const std::string& s0, const std::string& s1) {

    for (int i = 0; i< s0.length(); ++i) {
        if (i == s1.length()) return false;
        char xx = tolower(s0[i]);
        char yy = tolower(s1[i]);
        if (xx < yy) return true;
        if (yy < xx) return false;
    }
    if (s0.length()== s1.length()) return false;
    return true;
}

template<typename T0, typename T1>
void read_into_map_from_cin(std::map<T0, T1>& map) {

    T0 i0;
    T1 i1;
    for(; std::cin >> i0 >> i1;) {

        if(std::cin.bad()) {
            break;
        }
        map[i0] = i1;
    }
    std::cin.clear();
    std::cin.ignore();
}
template<typename T0, typename T1>
void print_map(std::map<T0,T1>& map) {
    for(auto& i : map) {
        std::cout << i.first << ' ' << i.second << std::endl;
    }
}
template<typename T>
void print_vector(const std::vector<T>& vec) {
    for(auto& i : vec) {
        std::cout << i << std::endl;
    }
}

i32 main(i32 argc, const char* argv[]) {
    
    try {

        // ---- vector ----
        std::vector<Item> vi;
        std::ifstream file("./week08/items");
        for(Item i; file >> i; vi.push_back(i));

        std::sort(vi.begin(), vi.end(),
            [](const Item& i0, const Item& i1) {
                return cmp_strs(i0.name, i1.name);
            });
        std::sort(vi.begin(), vi.end(),
            [](const Item& i0, const Item& i1) {
                return i0.iid < i1.iid;
            });
        std::sort(vi.begin(), vi.end(),
            [](const Item& i0, const Item& i1) {
                return i0.value < i1.value;
            });

        std::cout << "vi contents" << std::endl;
        for(auto it = vi.rbegin(); it != vi.rend(); it++) {
            std::cout << *it << std::endl;
        }

        vi.insert(vi.begin(), {"horse shoe", 99, 12.34});
        vi.insert(vi.begin(), {"Cannon S400", 9988, 499.95});


        vi.erase(std::find_if(vi.begin(), vi.end(), 
            [](const Item& i){ return i.name == "horse shoe";}));
        vi.erase(std::find_if(vi.begin(), vi.end(), 
            [](const Item& i){ return i.iid == 0;}));


        // ---- list ----
        std::list<Item> li;
        file.close();
        file.open("./week08/items");
        for(Item i; file >> i; li.push_back(i));
        file.close();


        std::cout << "\nli contents" << std::endl;
        for(auto it = li.rbegin(); it != li.rend(); it++) {
            std::cout << *it << std::endl;
        }

        li.insert(li.begin(), {"horse shoe", 99, 12.34});
        li.insert(li.begin(), {"Cannon S400", 9988, 499.95});

        li.remove_if(
            [](const Item& item) { return item.name == "apple" || item.name == "banana"; }
        );
        li.remove_if(
            [](const Item& item) { return item.iid == 10 || item.iid == 12; }
        );

        // ---- map ----
        std::map<std::string, int> msi;
        for(auto& i : vi) {
            msi[i.name] = i.iid;
        }

        std::cout << "\nmsi contents" << std::endl;
        print_map(msi);

        msi.clear();
        std::cout << "\nEnter (string, int) pairs" << std::endl;
        read_into_map_from_cin(msi);
        std::cout << std::endl;
        int sum = 0;

        std::cout << "msi contents" << std::endl;
        for(auto& i : msi) {
            std::cout << i.first << ' ' << i.second << std::endl;
            sum += i.second;
        }
        std::cout << "Sum: " << sum << std::endl;

        // ---- map 2 ----
        std::map<int, std::string> mis;
        for(auto& i : msi) {
            mis[i.second] = i.first;
        }

        // ---- vector ----
        std::cout << "\nfloat file(vd) contents" << std::endl;
        std::vector<f64> vd;
        std::ifstream floatFile("./week08/floats");
        for(f64 i; floatFile >> i; vd.push_back(i));
        print_vector(vd);
        std::cout << std::endl;

        std::cout << "(vd[i] vi2[i])" << std::endl;
        std::vector<int> vi2;
        f64 vdSum = 0;
        int vi2Sum = 0;
        for(auto& i : vd) {
            vi2.push_back(i);
            std::cout << i << ' ' << vi2.back() << std::endl;
            vdSum += i;
            vi2Sum += vi2.back();
        }
        std::cout << "vd sum: " << vdSum << " vi2 sum: " << vi2Sum << " diff: " << vdSum - (f64)vi2Sum << std::endl;

        std::cout << "\nvd reversed" << std::endl;
        std::reverse(vd.begin(), vd.end());
        print_vector(vd);

        auto mean = vdSum / vd.size();
        std::cout << "vd mean: " << mean << std::endl;

        std::vector<f64> vd2;
        for(auto& i : vd) {
            if(i < mean) {
                vd2.push_back(i);
            }
        }
        std::sort(vd2.begin(), vd2.end());

        std::cout << "\nvd2 contents" << std::endl;
        print_vector(vd2);

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