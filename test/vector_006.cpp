#include "std_lib_facilities.h"

class My_out_of_range{};

struct No_default {
	No_default(int k) { a = k; }
	int a = 0;
	int b = 0;
};

// A is an allocator for type T
template<typename T, typename A = allocator<T>>
class My_vector {
	A alloc;
	T* elem;
	long unsigned int sz;	// size
	int space;				// capacity

	void debug(const string& str) {
		cerr << this << "->" << str << " elem: " << elem << endl;
	}

public:

	using size_type = unsigned long;
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;

	iterator begin() 				{ return elem; 			}
	const_iterator begin() const 	{ return elem; 			}
	iterator end() 					{ return elem + sz; 	}
	const_iterator end() const 		{ return elem + sz; 	}
	iterator back() 				{ return elem + sz - 1; }

	My_vector(): sz{0}, elem{nullptr}, space{0} {}

	explicit My_vector(int s): sz(s), elem{alloc.allocate(s)}, space(s) {
		for (int i = 0; i < s; ++i) {
			alloc.construct(&elem[i], T());
		}
	}

	My_vector(initializer_list<T> lst): 
		sz(lst.size()),
		elem{alloc.allocate(sz)},
		space(lst.size()) {

		for(int i = 0; i < sz; ++i) {
			alloc.construct(&elem[i], *(lst.begin()+i));
		}
	}

	My_vector(const My_vector& arg): 
		sz{arg.sz},
		elem{alloc.allocate(sz)},
		space{arg.sz} {
		for (int i = 0; i < sz; ++i)  {
			alloc.construct(&elem[i], arg[i]);
		}
	}

	// copy
	My_vector& operator=(const My_vector& arg) {
		
		// self assignment
		if(this == &arg) return *this;

		// if there is enough space simply copy
		if(arg.sz <= space) {
			
			for(int i = 0; i < arg.sz; ++i) {

				alloc.construct(&elem[i], arg[i]);
			}

			// call dtor on unnecessary elements but keep the memory
			for(int i = arg.sz; i < sz; ++i) {
				alloc.destroy(&elem[i]);
			}
			
			sz = arg.sz;
			return *this;
		}

		// allocate memory
		T* p = alloc.allocate(arg.sz);
		for(int i = 0; i < arg.sz; ++i) {
			// copy
			alloc.construct(&p[i], arg[i]);
		}

		// free memory
		alloc.deallocate(elem, space);
		
		elem = p;
		sz = arg.sz;
		space = arg.space;
		return *this;
	}

	My_vector(My_vector&& arg):
		sz{arg.sz},
		elem{arg.elem},
		space{arg.space} {
		
		arg.sz = 0;
		arg.space = 0;
		arg.elem = nullptr;
	}

	// move asssignment operator overload
	My_vector& operator=(My_vector&& arg) {
		
		for(int i = 0; i < sz; ++i) {
			alloc.destroy(&elem[i]); 
		}
		
		// free memory
		alloc.deallocate(elem, space);

		space = arg.space;
		sz = arg.sz;
		elem = arg.elem;
		arg.sz = 0;
		arg.space = 0;
		arg.elem = nullptr;

		return *this;
	}

	// dtor
	~My_vector() { 

		for (int i = 0; i < sz; ++i) {

			// destroy held objects
			alloc.destroy(&elem[i]); 
		}
		// free underlying memory
		alloc.deallocate(elem, space);
	}
	
	long unsigned int size() const { return sz; }
	int capacity() const { return space; }

	T& operator[](int n){ return elem[n]; }
	const T& operator[](int n) const { return elem[n]; }

	T& at(int n) {
		// out of bounds access exception
		if (n < 0 || n >= sz) throw My_out_of_range();
		return elem[n];
	}

	const T& at(int n) const {
		// out of bounds access exception
		if (n < 0 || n >= sz) throw My_out_of_range();
		return elem[n];
	}

	// pre allocate memory
	void reserve(int newalloc) {

		if (newalloc <= space) return;

		// if something throws still free
		unique_ptr<T[]> p { alloc.allocate(newalloc) };

		for (int i = 0; i < sz; ++i) {

			// copy construct
			alloc.construct(&p[i], elem[i]);
		}
		for (int i = 0; i < sz; ++i) {

			// destory
			alloc.destroy(&elem[i]);
		}

		// free memory
		alloc.deallocate(elem, space);

		// no throws, don't free
		elem = p.release();
		space = newalloc;	
	}

	// resize with same values
	void resize(int newsize, T val = T()) {
	
		reserve(newsize);
		for(int i = sz; i < newsize; ++i) {

			// copy construct with val
			alloc.construct(&elem[i], val);
		}
		for(int i = newsize; i < sz; ++i) {

			alloc.destroy(&elem[i]);
		}

		sz = newsize;
	}

	void push_back(const T& d)	 {
		
		// if there is no space. allocate
		if(space == 0) {

			reserve(8);
		} 
		else if(sz == space) {
			// double the memory
			reserve(2*space);
		}	// ha nincs több hely

		// copy construct
		alloc.construct(&elem[sz], d);

		// inc size
		sz++;
	}

	// destroy object at p
	iterator erase(iterator p) {
		
		// out of valid region
		if(p == end()) return p;

		// move objects backwards
		for(auto pos = p + 1; pos != end(); ++pos) {
			*(pos-1) = *pos;
		}

		// destroy the last element
		alloc.destroy(&*(end() - 1));
		sz--;
		return p;
	}

	// place object at p
	iterator insert(iterator p, const T& val) {
		
		// calc index
		int index = p - begin();

		// need more memory
		if(size() == capacity()) {

			// if empty make capacity 8 otherwise double it
			reserve(size() == 0 ? 8 : 2 * capacity());
		}

		// move last element forward
		alloc.construct(elem + sz, *back());
		sz++;

		// insert at
		iterator pp = begin() + index;
		  
		// move everything forward
		for(auto pos = end() - 1; pos != pp; --pos) {
			*pos = *(pos-1);
		}
		
		// actually insert
		*(begin() + index) = val;

		// return the position
		return pp;
	}
};


My_vector<double> fill() {
	My_vector<double> t{10.2, 14.6, 20.1};

	return t;
}

void test_constructors() {
	My_vector<double> mv;
	cout << mv.capacity() << endl;

	for (int i = 0; i < 18; ++i) {
		mv.push_back(8.5);
		cout << mv.capacity() << endl;
	}

	My_vector<double> mv2 (mv);
	
	for(int i = 0; i < mv2.size(); ++i) {
		cout << mv2.at(i) << ' ';
	}
	cout << endl;

	My_vector<double> mv3 {15.2, 18.6, 120.1};

	mv3 = mv;

	for(int i = 0; i < mv3.size(); ++i) {
		cout << mv3.at(i) << ' ';
	}
	cout << endl;

	My_vector<double> mv4 = fill();

	for(int i = 0; i < mv4.size(); ++i) {
		cout << mv4.at(i) << ' ';
	}
	cout << endl;

	My_vector<double> mv5 {15.2, 18.6, 120.1};

	mv5 = fill();

	for(int i = 0; i < mv5.size(); ++i) {
		cout << mv5.at(i) << ' ';
	}
	cout << endl;

	My_vector<double> mv6 (10);
}

My_vector<double> glob(10);

int main() {
	try {

		My_vector<string> smv {"Jack", "Jill", "John", "Jenny", "Béla"};

		for(int i = 0; i < smv.size(); ++i) {
			cout << smv.at(i) << endl;
		}

		auto p = find(smv.begin(), smv.end(), "Jill");

		smv.erase(p);
		smv.insert(p, "Joseph");

		for(const auto& e : smv) {
			cout << e << endl;
		}
		
		return 0;

	} catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
}