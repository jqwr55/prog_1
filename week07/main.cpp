#include <common.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>


template<typename it0_t, typename it1_t>
it1_t copy(it0_t src_begin, it1_t src_end, it1_t dst) {

    for(it0_t it = src_begin; it != src_end; it++,dst++) {
        *dst = *it;
    }
    return dst;
}

template<typename C>
void print(const C& c) {

    for(const auto& it : c) {
        std::cout << it << std::endl;
    }
}

i32 main() {

    i32 arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<i32> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<i32> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    i32 arr2[SIZE_OF_ARRAY(arr)];
    copy(arr2, arr2+10, arr);

    std::vector<i32> vec2 = vec;
    std::list<i32> list2 = list;

    std::for_each(arr2, arr2+10, 
        [](i32& v) {v+=2;});
    std::for_each(vec.begin(), vec.end(), 
        [](i32& v) {v+=3;});
    std::for_each(list.begin(), list.end(), 
        [](i32& v) {v+=5;});

    copy(arr, arr+10, vec.begin());
    copy(list.begin(), list.end(), arr);

    auto posVec = std::find(vec.begin(), vec.end(), 3);
    if(posVec != vec.end()) {
        std::cout << "vec contains the value 3 at: " << std::distance(posVec, vec.end()) << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }

    auto posList = std::find(list.begin(), list.end(), 27);
    if(posList != list.end()) {
        std::cout << "list contains the value 27 at: " << std::distance(posList, list.end()) << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }

    print(vec);
    print(list);

    return 0;
}