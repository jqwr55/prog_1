#include <common.h>
#include <iostream>
#include <exception>

template<typename T>
void PrintOut(const T& t) {

    for(u32 i = 0; i < t.size(); i++) {
        std::cout << t[i] << std::endl;
    }
};

template<typename T, u32 N>
struct MyArray {
    // implementation is small enough to have it inside class

    using IteratorT = T*;
    using ConstIteratorT = const T*;

    T elems[N];
    T& operator[](u32 i) {
        if(i >= N) {
            throw std::runtime_error("out of bounds access");
        }
        return elems[i];
    }
    const T& operator[](int i) const {
        if(i >= N) {
            throw std::runtime_error("out of bounds access");
        }
        return elems[i];
    }

    // lower case for compatibiltiy with PrintOut etc...
    u32 size() const {
        return N;
    }
    IteratorT begin() {
        return elems;
    }
    IteratorT end() {
        return elems + N;
    }
    ConstIteratorT begin() const {
        return elems;
    }
    ConstIteratorT end() const {
        return elems + N;
    }


    u32 SizeOf() const {
        return N * sizeof(T);
    }
};

template<typename T>
class DefaultAllocator {

    public:
        T* Allocate(u32 count) {
            return (T*)malloc(count * sizeof(T));
        }
        void Free(T* ptr) {
            free(ptr);
        }
        void Construct(T* memory, const T& elem) {
            new(memory) T(elem);
        }
        void Construct(T* memory, T&& elem) {

            new(memory) T(std::move(elem));
        }
        void Destruct(T* objs, u32 count) {
            for(u32 i = 0; i < count; i++) {
                objs[i].~T();
            }
        }
};

// ----Vector----
template <class T, typename Alloc = DefaultAllocator<T>>
class MyVector {
public:

    using IteratorT = T*;
    using ConstIteratorT = const T*;

    // default ctor
    MyVector();

    // with default capacity
    MyVector(u32 size);
    
    // with default capacity initialized with T initial
    MyVector(u32 size, const T& initial);

    // copy ctor
    MyVector(const MyVector<T, Alloc>& v);

    // initializer list
    MyVector(std::initializer_list<T> list);

    // dtor
    ~MyVector();

    u32 capacity() const;
    u32 size() const;
    bool empty() const;

    IteratorT begin();
    IteratorT end();
    ConstIteratorT begin() const;
    ConstIteratorT end() const;

    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();

    void reserve(u32 capacity);
    void resize(u32 size);

    T& at(u32 i);
    T& operator[](u32 i);
    const T& operator[](u32 i) const;
    MyVector<T, Alloc>& operator = (const MyVector<T, Alloc>& other);

    void clear();
private:
    T* elemsBegin;
    u32 elemsCount;
    u32 elemsCapacity;
    Alloc allocator;
};

template <class T, typename Alloc>
std::ostream& operator << (std::ostream& os, const MyVector<T, Alloc>& v) {
    os << '{';
    for(u32 i = 0; i < v.size(); i++) {
        os << v[i] << ' ';
    }
    os << '}';
    return os;
}
template <typename T, u32 N>
std::ostream& operator << (std::ostream& os, const MyArray<T, N>& v) {
    os << '{';
    for(u32 i = 0; i < N; i++) {
        os << v[i] << ' ';
    }
    os << '}';
    return os;
}

template <class T, typename Alloc>
MyVector<T, Alloc>::MyVector() : elemsCapacity{0}, elemsCount{0}, elemsBegin{nullptr} { }

template <class T, typename Alloc>
MyVector<T, Alloc>::MyVector(const MyVector<T, Alloc>& v) :
    elemsCount(v.elemsCount),
    elemsCapacity(v.elemsCapacity),
    elemsBegin(allocator.Allocate(v.elemsCount)) {
   
    for(u32 i = 0; i < elemsCount; i++) {

        allocator.Construct(elemsBegin + i, v.elemsBegin[i]);
    }
}

template <class T, typename Alloc>
MyVector<T, Alloc>::MyVector(u32 size) : elemsCapacity(size), elemsCount(size), elemsBegin(allocator.Allocate(size)) {

    for(u32 i = 0; i < size; i++) {

        allocator.Construct(elemsBegin + i, T());
    }
}

template <class T, typename Alloc>
MyVector<T, Alloc>::MyVector(u32 size, const T& initial) :
    elemsCount(size),
    elemsCapacity(size),
    elemsBegin(allocator.Allocate(size)) {

    for(u32 i = 0; i < size; i++) {

        allocator.Construct(elemsBegin + i, initial);
    }
}

template <class T, typename Alloc>
MyVector<T, Alloc>& MyVector<T, Alloc>::operator = (const MyVector<T, Alloc>& v) {

    allocator.Destruct(elemsBegin, elemsCount);

    if(elemsCapacity < v.elemsCapacity) {

        allocator.Free(elemsBegin);
        elemsBegin = allocator.Allocate(v.elemsCapacity);
        elemsCapacity = v.elemsCapacity;
    }

    elemsCount = v.elemsCount;
    for(u32 i = 0; i < elemsCount; i++) {
        allocator.Construct(elemsBegin + i, v.elemsBegin[i]);
    }

    return *this;
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::IteratorT MyVector<T, Alloc>::begin() {
    return elemsBegin;
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::IteratorT MyVector<T, Alloc>::end() {
    return elemsBegin + size();
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::ConstIteratorT MyVector<T, Alloc>::begin() const {
    return elemsBegin;
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::ConstIteratorT MyVector<T, Alloc>::end() const {
    return elemsBegin + size();
}

template<typename T, typename Alloc>
T& MyVector<T, Alloc>::front() {
    return elemsBegin[0];
}

template<typename T, typename Alloc>
T& MyVector<T, Alloc>::back() {
    return elemsBegin[elemsCount - 1];
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::push_back(const T& v) {
    
    if(elemsCount >= elemsCapacity) {
        reserve(elemsCapacity +5);
    }
    elemsBegin[elemsCount++] = v;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::pop_back() {
    elemsCount--;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::reserve(u32 capacity) {
    
    if(elemsBegin == nullptr) {
        elemsCount = 0;
        elemsCapacity = 0;
    }

    if(capacity > elemsCapacity) {

        T* tmp = allocator.Allocate(capacity);

        u32 cpyCount = elemsCount;
        for(u32 i = 0; i < cpyCount; i++) {
            
            allocator.Construct(tmp + i, elemsBegin[i]);
        }

        elemsCapacity = capacity;
        allocator.Destruct(elemsBegin, elemsCount);
        allocator.Free(elemsBegin);
        elemsBegin = tmp;
    }
    
}

template<typename T, typename Alloc>
u32 MyVector<T, Alloc>::size()const {
    return elemsCount;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::resize(u32 size) {

    if(elemsBegin == nullptr) {
        elemsCount = 0;
        elemsCapacity = 0;
    }

    T* tmp = allocator.Allocate(size);

    u32 cpyCount = elemsCount;
    if(size < cpyCount) {
        cpyCount = size;
    }
    for(u32 i = 0; i < cpyCount; i++) {
        
        allocator.Construct(tmp + i, elemsBegin[i]);
    }

    elemsCapacity = size;
    allocator.Destruct(elemsBegin, elemsCount);
    allocator.Free(elemsBegin);
    elemsBegin = tmp;
    elemsCount = cpyCount;
}

template<typename T, typename Alloc>
T& MyVector<T, Alloc>::at(u32 i) {
    if(i >= elemsCount) {
        throw std::runtime_error("out of bounds access");
    }
    return elemsBegin[i];
}
template<typename T, typename Alloc>
T& MyVector<T, Alloc>::operator[](u32 i) {
    if(i >= elemsCount) {
        throw std::runtime_error("out of bounds access");
    }
    return elemsBegin[i];
}
template<typename T, typename Alloc>
const T& MyVector<T, Alloc>::operator[](u32 i) const {
    if(i >= elemsCount) {
        throw std::runtime_error("out of bounds access");
    }
    return elemsBegin[i];
}

template<typename T, typename Alloc>
u32 MyVector<T, Alloc>::capacity()const {
    return elemsCapacity;
}

template<typename T, typename Alloc>
MyVector<T, Alloc>::MyVector(std::initializer_list<T> list) : 
    elemsCount(list.size()),
    elemsBegin(allocator.Allocate(list.size() ) ),
    elemsCapacity(list.size()) {

    for(u32 i = 0; i < list.size(); i++) {

        allocator.Construct(elemsBegin + i, list.begin()[i]);
    }
}

template<typename T, typename Alloc>
MyVector<T, Alloc>::~MyVector() {
    allocator.Destruct(elemsBegin, elemsCount);
    allocator.Free(elemsBegin);
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::clear() {
    elemsCapacity = 0;
    elemsCount = 0;
    elemsBegin = 0;
}



// ----List----

template<typename T> 
class List {
    public:

    private:
};