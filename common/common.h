#pragma once
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <memory.h>
#include <sys/mman.h>
#include <unistd.h>

#include <type_traits>
#include <chrono>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u8  bit_mask8;
typedef u16 bit_mask16;
typedef u32 bit_mask32;
typedef u64 bit_mask64;

typedef u8 byte;

static_assert(sizeof(u8)  == 1 && sizeof(i8)  == 1);
static_assert(sizeof(u16) == 2 && sizeof(i16) == 2);
static_assert(sizeof(u32) == 4 && sizeof(i32) == 4);
static_assert(sizeof(u64) == 8 && sizeof(i64) == 8);

typedef float       f32;
typedef double      f64;
typedef long double f128;

static_assert(sizeof(f32)  == 4);
static_assert(sizeof(f64)  == 8);
static_assert(sizeof(f128) == 16);

struct f16 {
    u16 bits;
};

constexpr u64 KILO_BYTE       = 1000 * 1;
constexpr u64 MEGA_BYTE       = 1000 * KILO_BYTE;
constexpr u64 GIGA_BYTE       = 1000 * MEGA_BYTE;
constexpr u64 TERA_BYTE       = 1000 * GIGA_BYTE;
constexpr u64 MICRO_SEC       = 1000 * 1;
constexpr u64 MILI_SEC        = 1000 * MICRO_SEC;
constexpr u64 SECOND          = 1000 * MILI_SEC;
constexpr u64 CACHE_LINE_SIZE = 64;

#define DEBUG_BUILD
#ifdef __GNUC__

    #define _FORCE_INLINE       __attribute__((always_inline))
    #define _NO_INLINE          __attribute__((noinline))
    #define _RESTRICT           __restrict__
    #define _TRAP               __builtin_trap()
    #define _LIKELY(x)          __bultin_expect(x, 1)
    #define _UN_LIKELY(x)       __bultin_expect(x, 0)

    /*
    template <typename T>
    using v2 = T __attribute__((vector_size(sizeof(T) * 2)));
    template <typename T>
    using v4 = T __attribute__((vector_size(sizeof(T) * 4)));
    template <typename T>
    using v8 = T __attribute__((vector_size(sizeof(T) * 8)));

    typedef v2<u64> bit_mask128;
    typedef v4<u64> bit_mask256;
    */
#else
    #ifdef _MSC_VER
    #endif
#endif

#define SIZE_OF_ARRAY(arr) sizeof(arr) / sizeof(arr[0])

void global_io_flush();
void global_print(const char* format ...);
void runtime_panic(const char* file, u32 line);

#define RUNTIME_CHECK(x)                  \
    if(!x) {                              \
        runtime_panic(__FILE__, __LINE__);\
    }                                     \

#ifdef DEBUG_BUILD
    #define LOG_ASSERT(x, y)                                                                     \
        if (!(x)) {                                                                              \
            global_print("c, s, s, s, c, s, c, i, c", '(', #x, ") ", y, ' ', __FILE__, ' ', __LINE__, '\n'); \
            global_io_flush();                                                                   \
            _TRAP;                                                                               \
        }
    #define ASSERT(x)                                                                                           \
        if (!(x)) {                                                                                             \
            global_print("c, s, s, s, c, i, c", '(', #x, ") triggered builtin trap in: ", __FILE__, ' ', __LINE__, '\n'); \
            global_io_flush();                                                                                  \
            _TRAP;                                                                                              \
        }
    #define LOG(x) x;
#else
    #define LOG(x) x;
    #define ASSERT(x) x;
    #define LOG_ASSERT(x, y) x;
#endif

u64 Kilobyte(u64 n);
u64 Megabyte(u64 n);
u64 Gigabyte(u64 n);
u64 Terabyte(u64 n);
u64 Milisecond(u64 n);
u64 Second(u64 n);
u64 Minute(u64 n);
u64 Hour(u64 n);

template<typename T>
T SetBitMaskBit(T mask, u32 bit) {   
    T set = 1 << bit;
    return mask | set;
}
template<typename T>
T ClearBitMaskBit(T mask, u32 bit) {   
    T set = ~(1 << bit);
    return mask & set;
}
template<typename T>
bool GetBitMaskBit(T mask, u32 bit) {
    return bool(mask >> bit);
}
template<typename T>
T SetBitMaskBitTo(T mask, u32 bit, bool to) {
    T set = ~(T(1) << bit);
    T clear = mask & set;
    return clear | (T(to) << bit);
}
template <typename T>
T &Mem(void *mem) {
    return *((T *)mem);
}
template <typename T>
T Min(T t0, T t1) {
    return t0 > t1 ? t1 : t0;
}
template <typename T>
T Max(T t0, T t1) {
    return t0 > t1 ? t0 : t1;
}
template <typename T>
T Abs(T t0) {
    return Max<T>(t0, -t0);
}
template <typename T>
T AbsDiff(T t0, T t1) {
    bool c = t0 > t1;
    T max = c ? t0 : t1;
    T min = c ? t1 : t0;

    return max - min;
}
template <typename T>
T Clamp(T t0, T max, T min) {
    return Min(Max(t0, min), max);
}
template<typename T>
void Swap(T* t0, T* t1) {
    auto tmp = *t0;
    *t0 = *t1;
    *t1 = tmp;
}
template<typename T>
T* GetPointer(void* base, u32 ptr) {  
    return ptr ? (T*)(((byte*)base) + ptr) : nullptr;
}
template<typename T>
T* GetPointer0(void* base, u32 ptr) {  
    return ptr != ~u32(0) ? (T*)(((byte*)base) + ptr) : nullptr;
}
u64 align(u64 n, u64 alignment);
void* align_pointer(void* n, u64 alignment);


union f32_union_u32 {
    f32 f;
    u32 u;
};
f32 f16_to_f32(f16 f);
f16 f32_to_f16(f32 f);

template<typename T>
void meminc(T* dst, T* end) {
    for(; dst != end; dst++) {
        (*dst)++;
    }
}
u32 get_unique(u32* arr, u32 count);

template<typename T>
struct SelfRelativePointer {
    i32 add;
    T* operator*() {
        ASSERT(add != 0);
        return (T*)(&add + add);
    }
    T* operator->() {
        ASSERT(add != 0);
        return (T*)(&add + add);
    }
};
template<typename T>
struct ForwardRelativePointer {
    u32 add;
    T* operator*() {
        ASSERT(add != 0);
        return (T*)(&add + add);
    }
    T* operator->() {
        ASSERT(add != 0);
        return (T*)(&add + add);
    }
};


struct LinearAllocator {
    byte* base;
    u32 cap;
    u32 top;
};

struct ScopedAllocator {
    LinearAllocator* allocator;
    u32 top;
    ScopedAllocator(LinearAllocator* alloc) {
        allocator = alloc;
        top = alloc->top;
    }
    ~ScopedAllocator() {
        allocator->top = top;
    }
};

LinearAllocator make_linear_allocator(void* base, u32 size);
void* linear_allocate(LinearAllocator* stack, u32 size);
void* linear_aligned_allocate(LinearAllocator* stack, u32 size, u32 alignment);
void* linear_allocate_reversed(LinearAllocator* stack, u32 size);
void linear_deallocate(LinearAllocator* stack, u32 size);
void roll_back_linear_allocator(LinearAllocator* stack, void* pos);
void* linear_allocator_top(LinearAllocator* stack);
void* linear_allocator_top_reversed(LinearAllocator* stack);
u32 linear_allocator_free_size(LinearAllocator* stack);

struct SizedFreeList {
    SizedFreeList* next;
    u32 size;
};
struct CoalescingLinearAllocator {
    byte* base;
    SizedFreeList* freed;
    u32 cap;
    u32 top;
};
CoalescingLinearAllocator make_coalescing_linear_allocator(void* mem, u32 size);
void* linear_alloc(CoalescingLinearAllocator* ctx, u32 size);
void linear_free(CoalescingLinearAllocator* ctx, void* mem, u32 size);
void* linear_top(CoalescingLinearAllocator* ctx);

struct CircularAllocator {
    byte* base;
    u32 head;
    u32 cap;
};
CircularAllocator make_circular_allocator(void* mem, u32 size);
void* circular_allocate(CircularAllocator* alloc, u32 size);

struct RingBuffer {
    byte* base;
    u32 head;
    u32 tail;
    u32 cap;
};
RingBuffer make_ring_buffer(void* mem, u32 size);
void* circular_get_write_ptr(RingBuffer* buffer, u32 size);
void* circular_get_read_ptr(RingBuffer* buffer, u32 size);
void circular_advance_write(RingBuffer* buffer, u32 size);
u32 circular_read_size(RingBuffer* buffer, u32 size);
void circular_advance_read(RingBuffer* buffer, u32 size);

struct FreeList {
    FreeList* next;
};
void* free_list_allocate(FreeList** list);
void free_list_free(FreeList** list, void* memory);

template<u32 slab_size>
struct MemoryPool {
    byte* base;
    FreeList* head;
    u32 top;
    u32 poolSize;
};
template<u32 slab_size>
MemoryPool<slab_size> make_memory_pool(void* base, u32 size) {
    static_assert(slab_size >= sizeof(void*));
    ASSERT(size % slab_size == 0);
    base = align_pointer(base, CACHE_LINE_SIZE);
    return {(byte*)base, nullptr, 0, size};
}

template<u32 slab_size>
void* pool_allocate(MemoryPool<slab_size>* pool) {
    static_assert(slab_size >= sizeof(void*));

    if(pool->list.head) {
        return free_list_allocate(&pool->list);
    }
    auto ret = pool->base + pool->top;
    pool->top += slab_size;
    LOG_ASSERT(pool->top <= pool->poolSize, "pool overflow");
    return ret;
}

template<u32 slab_size>
void pool_free(MemoryPool<slab_size>* pool, void* memory) {
    static_assert(slab_size >= sizeof(void*));
    free_list_free(&pool->list, memory);
}

struct PoolBlock {
    u32 next;
    u32 size;
};
template<u32 slab_size>
struct MultiAllocPool {
    byte* base;
    u32 list;
    u32 top;
    u32 poolSize;
};
template<u32 slab_size>
MultiAllocPool<slab_size> make_multi_memory_pool(void* base, u32 size) {
    static_assert(slab_size >= sizeof(void*));
    ASSERT(size % slab_size == 0);
    base = align_pointer(base, CACHE_LINE_SIZE);
    return {(byte*)base, ~u32(0), 0, size};
}
template<u32 slab_size>
void* pool_multi_allocate(MultiAllocPool<slab_size>* pool, u32 size) {

    static_assert(slab_size >= sizeof(void*));
    ASSERT(size % slab_size == 0);

    auto it = GetPointer0<PoolBlock>(pool->base, pool->list);
    PoolBlock* prev = (PoolBlock*)&pool->list;
    while(it) {
        if(it->size >= size) {
            
            prev->next = it->next;
            if(it->size > size) {
                auto fresh_end = (PoolBlock*)((byte*)it + size);
                fresh_end->size = it->size - size;
                fresh_end->next = it->next;
                it->next = (byte*)fresh_end - pool->base;
                prev->next = (byte*)fresh_end - pool->base;
            }
            
            return it;
        }
        prev = it;
        it = GetPointer0<PoolBlock>(pool->base, it->next);
    }
  
    auto ret = pool->base + pool->top;
    pool->top += size;
    LOG_ASSERT(pool->top <= pool->poolSize, "pool overflow");
    return ret;
}

template<u32 slab_size>
void pool_multi_free(MultiAllocPool<slab_size>* pool, void* memory, u32 size) {
    static_assert(slab_size >= sizeof(void*));
    ASSERT(size % slab_size == 0);

    if(!memory) return;
    
    auto block = (PoolBlock*)memory;
    block->next = pool->list;
    block->size = size;
    pool->list = (byte*)memory - pool->base;
}


template<typename T>
struct LocalList {
    LocalList* next;
    u32 count;
    T arr[];
    #define ALLOCATE_LOCAL_LIST(prev, size) prev = (decltype(prev))alloca(size + sizeof(decltype(prev)));
};

_NO_INLINE
void runtime_panic(const char* file, u32 line);

// ------------- shared mutable global state BEGIN --------------------
typedef void(malloc_handler_t)(void*);
extern byte* global_malloc_base;
extern malloc_handler_t* global_out_of_memory_handler;
extern void* global_out_of_memory_user;
extern LinearAllocator io;
// ------------- shared mutable global state END ----------------------

struct MemoryBlockHeader {
    u32 left_ptr;
    u32 right_ptr;
    u32 size;
    static constexpr u32 FREE_BIT_MASK = ~u32(0) >> 1;
};

bool extract_free_bit(u32 mem);
void set_free_bit(MemoryBlockHeader* block);
void clear_free_bit(MemoryBlockHeader* block);
void set_size_in_block(MemoryBlockHeader* block, u32 size);
u32 get_size_in_block(MemoryBlockHeader* block);
MemoryBlockHeader* get_block_ptr(byte* base, u32 smallPtr);

// observes shared global mutable state
MemoryBlockHeader *search_free_block(u32 size);
// mutates shared global state
void init_global_malloc(void *base_, u32 size, malloc_handler_t* handler, void*);
// mutates shared global state

void* global_malloc(u32 size);
// mutates shared global state
void global_free(void *block);

// observes shared global state
void print_heap_info();
// observes shared global state
u32 check_live_mem(void *block);
// observes shared global state
bool check_memory_integrity(void *mem);
// observes shared global state
void check_all_memory(void *check);
// mutates shared global state
void *global_malloc_debug(u32 size);

u32 get_allocation_size_debug(void* mem);
// mutates shared global state
void global_free_debug(void *mem);

struct LocalMallocState {
    MemoryBlockHeader* headBlock;
};

byte* get_local_malloc_base(LocalMallocState state);
LocalMallocState make_local_malloc(byte* base, u32 size);
MemoryBlockHeader *local_search_free_block(LocalMallocState* state, u32 size);
void* local_malloc(LocalMallocState* state, u32 size);
void local_free(LocalMallocState* state, void* block);
void local_malloc_shrink(LocalMallocState* state, void* block, u32 size);
u32 local_malloc_allocation_size(void* block);
void* local_max_malloc(LocalMallocState* state);
void print_local_heap_info(LocalMallocState heap);

u32 str_hash(const char *str, u32 c);
// counts sentinel
u32 str_len(const char *str);
void* str_cpy(void* dst, const char* src);
bool str_cmp(const char *str0, const char *str1);
i64 i64_power(i64 base, i64 exp);
u32 u64_to_string(char *buffer, u32 buffer_size, u64 n);
u32 f32_to_string(char* buff, u32 buff_size, f32 n, u32 precision);
// expects sentinel
f64 str_to_f64(const char* str);

template<typename T>
i64 QPartition(T* arr, i64 low, i64 high) {

    i64 pivot = arr[high];
    i64 index = low - 1;

    for(i64 i = low; i < high; i++) {
        if(arr[i] < pivot) {
            index++;
            auto tmp = arr[index];
            arr[index] = arr[i];
            arr[i] = tmp;
        }
    }

    auto tmp = arr[high];
    arr[high] = arr[index + 1];
    arr[index + 1] = tmp;
    return index + 1;
}
template<typename T>
void Qsort(T* arr, i64 low, i64 high) {

    if(low < high) {
        i64 pivot = QPartition(arr, low, high);
        Qsort(arr, low, pivot-1);
        Qsort(arr, pivot+1, high);
    }
}

byte* print_fn_v(byte* buffer, u32 buffer_size, const char* format, va_list args);
// mutates shared global state
void init_global_print(LinearAllocator memory);
void print_out_of_memory();
byte* init_global_state(u32 heapSize, u32 miscMemoySize, u32 ioBufferSize);
// mutates shared global state
void global_io_flush();
// mutates shared global state
void global_print(const char* format ...);
byte* local_print(byte* buffer, u32 buffer_size, const char* format ...);
// uses global_malloc_debug

u64 ReadFile(const char* fileName, byte* buffer);
u64 ReadFileTerminated(const char* fileName, byte* buffer);
byte* ReadFileTerminated(const char *fileName, byte *buffer, u32* size_);
byte* ReadFile(const char* fileName, byte* buffer, u32* size_);

struct Pixel {
    union {
        struct {
            u8 r, g, b, a;
        };
        u32 mem;
    };
};
struct ImageDescriptor {
    u32 width;
    u32 height;
    Pixel* img;
};
ImageDescriptor LoadBMP(const char* path, void* memory);

u32 u32_log2(u32 n);
f32 f32_log(f32 n, f32 base);
void local_free_wrapper(LocalMallocState* state, void* mem, u32 size);
    

template <typename K, typename V>
struct HashNode {
    K key;
    V value;
};

template <typename K, typename V, u64 (*HASH_FUNCTION)(void *, K), bool (*EQ_FUNCTION)(void *, K, K), K INVALID_KEY>
struct HashTable {
    HashNode<K, V> *array;
    void *user;
    u32 cap;
    u32 occupancy;
    static constexpr f32 loadFactor = 0.5;

    void Init(void *user_) {
        user = user_;
        cap = 2;
        array = (HashNode<K, V> *)LOG(global_malloc_debug(sizeof(HashNode<K, V>) * 2));
        array[0].key = INVALID_KEY;
        array[1].key = INVALID_KEY;

#ifdef DEBUG_BUILD
        check_memory_integrity(array);
#endif
    }
    void CopyInit(HashTable<K, V, HASH_FUNCTION, EQ_FUNCTION, INVALID_KEY> *other) {

        memcpy(this, other, sizeof(*this));
        array = (HashNode<K, V> *)LOG(global_malloc_debug(sizeof(HashNode<K, V>) * other->cap));
        memcpy(array, other->array, sizeof(HashNode<K, V>) * other->cap);

#ifdef DEBUG_BUILD
        check_memory_integrity(array);
#endif
    }
    void Delete(K key) {
        occupancy--;
        array[Find(key)].key = INVALID_KEY;
    }

    u32 Find(K key) {

        u32 index = HASH_FUNCTION(user, key) & (cap - 1);
        for (;;) {

            if (EQ_FUNCTION(user, array[index].key, key)) {
                return index;
            }
            index++;
            if (index == cap) {
                return ~u32(0);
            }
        }
    }


    void Insert(K key, V val) {

        if (cap * loadFactor < (occupancy + 1)) {
            GrowAndReHash();
        }

        occupancy++;
        u32 index = HASH_FUNCTION(user, key) & (cap - 1);
        for (;;) {
            if (EQ_FUNCTION(user, array[index].key, INVALID_KEY)) {
                array[index].key = key;
                array[index].value = val;
                return;
            }

            index++;
            if (index == cap) {
                GrowAndReHash();
                index = HASH_FUNCTION(user, key) & (cap - 1);
            }
        }
    }

    void GrowAndReHash() {

        u32 newCap = cap * 2;
        Begin:

#ifdef DEBUG_BUILD
        check_memory_integrity(array);
#endif

        HashNode<K, V> *tmp = (HashNode<K, V> *)LOG(global_malloc_debug(sizeof(HashNode<K, V>) * newCap));
        for (u32 i = 0; i < newCap; i++) {
            tmp[i].key = INVALID_KEY;
        }
#ifdef DEBUG_BUILD
        check_memory_integrity(array);
        check_memory_integrity(tmp);
#endif

        for (u32 i = 0; i < cap; i++) {

            if (!EQ_FUNCTION(user, array[i].key, INVALID_KEY)) {

                u32 index = HASH_FUNCTION(user, array[i].key) & (newCap - 1);
                for (;;) {
                    if (EQ_FUNCTION(user, tmp[index].key, INVALID_KEY)) {
                        tmp[index].key = array[i].key;
                        tmp[index].value = array[i].value;
                        break;
                    }
                    index++;
                    if (index == newCap) {
                        newCap *= 2;
                        LOG(global_free_debug(tmp));
                        goto Begin;
                    }
                }
            }
        }

        LOG(global_free_debug(array));
        array = tmp;
        cap = newCap;
    }
    void Free() {
        LOG(global_free_debug(array));
        array = nullptr;
    }
};

template <typename T, u64 (*HASH_FUNCTION)(void *, T), bool (*EQ_FUNCTION)(void *, T, T), T INVALID_VALUE, u64 INVALID_HASH>
struct HashSet {

    HashNode<u64, T>* mem;
    u32 cap;
    u32 occupancy;
    static constexpr f32 loadFactor = 0.5;

    void Init() {
        cap = 2;
        mem = (HashNode<u64, T> *)LOG(global_malloc_debug(sizeof(HashNode<u64, T>) * 2));
        occupancy = 0;
        mem[0].key = INVALID_HASH;
        mem[0].value = INVALID_VALUE;
        mem[1].key = INVALID_HASH;
        mem[1].value = INVALID_VALUE;

#ifdef DEBUG_BUILD
        check_memory_integrity(mem);
#endif
    }
    void CopyInit(HashSet<T, HASH_FUNCTION,EQ_FUNCTION,INVALID_VALUE, INVALID_HASH> *other) {

        memcpy(this, other, sizeof(*this));
        mem = (HashNode<u64, T> *)LOG(global_malloc_debug(sizeof(HashNode<u64, T>) * other->cap));
        memcpy(mem, other->mem, sizeof(HashNode<u64, T>) * other->cap);

#ifdef DEBUG_BUILD
        check_memory_integrity(mem);
#endif
    }
    void Delete(void* user, T value) {
        occupancy--;
        auto index = Find(user, value);
        mem[index].value = INVALID_VALUE;
        mem[index].key = INVALID_HASH;
    }
    void Free() {
        LOG(global_free_debug(mem));
    }
    void Clear() {
        occupancy = 0;
        for(u32 i = 0; i < cap; i++) {
            mem[i].value = INVALID_VALUE;
            mem[i].key = INVALID_HASH;
        }
    }
    u32 Find(void* user, T value) {

        auto hash = HASH_FUNCTION(user, value);
        u32 index = hash & (cap - 1);
        for(;;) {
            if(mem[index].key == hash) {
                if(EQ_FUNCTION(user, mem[index].value, value)) return index;
            }

            if(++index == cap) return ~u32(0);
        }
    }

    void Insert(void* user, T value) {
        
        occupancy++;
        if(occupancy > cap * loadFactor) {
            Grow(user);
        }

        auto hash = HASH_FUNCTION(user, value);
        begin:
        u32 index = hash & (cap - 1);

        for(;;) {
            if(mem[index].key == INVALID_HASH) {
                if(EQ_FUNCTION(user, mem[index].value, INVALID_VALUE)) {
                    mem[index].key = hash;
                    mem[index].value = value;

                    return;
                }
            }

            index++;
            if(index == cap) {
                Grow(user);
                goto begin;
            }
        }
    }
    void Grow(void* user) {

        begin:
        auto tmp = (HashNode<u64, T>*)LOG(global_malloc_debug(2 * cap * sizeof(HashNode<u64, T>) ));
        for(u32 i = 0; i < cap*2; i++) {
            tmp[i].value = INVALID_VALUE;
            tmp[i].key = INVALID_HASH;
        }

        for(u32 i = 0; i < cap; i++) {

            if(mem[i].key != INVALID_HASH) {
                if(!EQ_FUNCTION(user, mem[i].value, INVALID_VALUE)) {

                    auto index = mem[i].key & (2*cap - 1);
                    for(;;) {

                        if(tmp[index].key == INVALID_HASH) {
                            if(EQ_FUNCTION(user, tmp[index].value, INVALID_VALUE)) {
                                tmp[index] = mem[i];
                                break;
                            }
                        }

                        index++;
                        if(index == 2*cap) {
                            cap *= 2;
                            LOG(global_free_debug(tmp));
                            goto begin;
                        }
                    }
                }
            }
        }

        LOG(global_free_debug(mem));
        mem = tmp;
        cap *= 2;
    }

    T& operator[](u32 index) {
        return mem[index].value;
    }
};

template<typename T, typename state_t, void* ALLOCATE(state_t* state, u32 size), void FREE(state_t* state, void* mem, u32 size)>
struct DynamicBufferLocal {
    T *mem;
    u32 cap;
    u32 size;

    void Init(state_t* allocState) {
        mem = (T*)LOG(ALLOCATE(allocState, sizeof(T)));
        cap = 1;
        size = 0;
    }
    void CopyInit(state_t* allocState, DynamicBufferLocal<T,state_t,ALLOCATE,FREE> *buff) {
        SetCapacity(allocState, buff->cap);
        size = buff->size;
        cap = buff->cap;
        memcpy(mem, buff->mem, sizeof(T) * size);
    }

    T &Back() {
        ASSERT(mem != nullptr && size != 0);
        return mem[size - 1];
    }
    T &Front() {
        ASSERT(mem != nullptr && size != 0);
        return mem[0];
    }

    void SetCapacity(state_t* allocState, u32 capacity) {
        LOG(FREE(allocState, mem, cap * sizeof(T)));
        mem = (T*)LOG(ALLOCATE(allocState, capacity * sizeof(T)));
        cap = capacity;
        size = 0;
    }
    u32 PushBack(state_t* allocState, T e) {

        if (cap < size + 1) {

            T* tmp = (T*)LOG(ALLOCATE(allocState, sizeof(T) * cap * 2 ));
            ASSERT(cap * 2 >= size + 1);
            memcpy(tmp, mem, size * sizeof(T));
            LOG(FREE(allocState, mem, cap * sizeof(T)));
            mem = tmp;

            cap *= 2;
        }

        mem[size] = e;
        return size++;
    }
    void Clear() {
        size = 0;
    }
    u32 PopBack() {
        return --size;
    }
    u32 Shrink(state_t* allocState) {
        T* tmp = (T*)LOG(ALLOCATE(allocState, sizeof(T) * (size + 1) * 2 ));
        for (u32 i = 0; i < size * sizeof(T); i++) {
            ((byte *)tmp)[i] = ((byte *)mem)[i];
        }
        LOG(FREE(allocState, mem, cap * sizeof(T)));
        mem = tmp;
        cap = size;
        return size;
    }

    T &operator[](u32 i) {
        return mem[i];
    }
    void Free(state_t* allocState) {
        LOG(FREE(allocState, mem, cap * sizeof(T)));
        mem = nullptr;
        cap = 0;
        size = 0;
    }

    void Delete(u32 i) {
        for (; i < size - 1; i++) {
            mem[i] = mem[i + 1];
        }
    }
    void Remove(u32 i) {
        mem[i] = Back();
        PopBack();
    }
};

template <typename T, void* ALLOCATE(u32 size), void FREE(void* mem)>
struct DynamicBufferGlobal {
    T *mem;
    u32 cap;
    u32 size;

    void Init() {
        mem = (T*)LOG(ALLOCATE(sizeof(T)));
        cap = 1;
        size = 0;
    }
    void CopyInit(DynamicBufferGlobal<T,ALLOCATE,FREE> *buff) {
        SetCapacity(buff->cap);
        size = buff->size;
        cap = buff->cap;
        memcpy(mem, buff->mem, sizeof(T) * size);
    }

    T &Back() {
        ASSERT(mem != nullptr && size != 0);
        return mem[size - 1];
    }
    T &Front() {
        ASSERT(mem != nullptr && size != 0);
        return mem[0];
    }

    void SetCapacity(u32 capacity) {
        mem = (T*)LOG(ALLOCATE(capacity * sizeof(T) ));
        cap = capacity;
        size = 0;
    }
    u32 PushBack(T e) {

        if (cap < size + 1) {

#ifdef DEBUG_BUILD
            check_all_memory(nullptr);
#endif
            T* tmp = (T*)LOG(ALLOCATE(sizeof(T) * cap * 2 ));
#ifdef DEBUG_BUILD
            check_all_memory(nullptr);
#endif
            ASSERT(cap * 2 >= size + 1);

            memcpy(tmp, mem, size * sizeof(T));

            LOG(FREE(mem));
            mem = tmp;

            cap *= 2;
        }

        mem[size] = e;
        return size++;
    }
    void Clear() {
        size = 0;
    }
    u32 PopBack() {
        return --size;
    }
    u32 Shrink() {
        T* tmp = (T*)LOG(ALLOCATE(sizeof(T) * (size + 1) * 2 ));
        for (u32 i = 0; i < size * sizeof(T); i++) {
            ((byte *)tmp)[i] = ((byte *)mem)[i];
        }
        LOG(FREE(mem));
        mem = tmp;
        cap = size;
        return size;
    }

    T &operator[](u32 i) {
        return mem[i];
    }
    void Free() {
        LOG(FREE(mem));
        mem = nullptr;
        cap = 0;
        size = 0;
    }

    void Delete(u32 i) {
        for (; i < size - 1; i++) {
            mem[i] = mem[i + 1];
        }
    }
    void Remove(u32 i) {
        mem[i] = Back();
        PopBack();
    }
};


template <typename T, void* ALLOCATE(u32 size), void FREE(void* mem)>
struct StaticBufferGlobal {
    T *memory;
    u32 size;
    void Init(u32 size_) {
        static_assert(std::is_trivially_destructible<T>::value, "T must be trivally destructible");
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivally copyable");

        ASSERT(!memory);
        size = size_;
        memory = (T *)LOG(ALLOCATE(size * sizeof(T)));
    }
    void Free() {
        LOG(FREE(memory));
    }
    void Fill(T *mem, u32 c) {
        ASSERT(c <= size);
        memcpy(memory, mem, sizeof(T) * c);
    }
    T &operator[](u32 i) {
        return memory[i];
    }
};
template <typename T, typename state_t, void* ALLOCATE(state_t* state, u32 size), void FREE(state_t* state, void* mem)>
struct StaticBufferLocal {
    T *memory;
    u32 size;
    void Init(state_t* allocatorState, u32 size_) {
        static_assert(std::is_trivially_destructible<T>::value, "T must be trivally destructible");
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivally copyable");

        size = size_;
        memory = (T *)LOG(ALLOCATE(allocatorState, size * sizeof(T)));
    }
    void Free(state_t* allocatorState) {
        LOG(FREE(allocatorState, memory));
    }
    void Fill(T *mem, u32 c) {
        ASSERT(c <= size);
        memcpy(memory, mem, sizeof(T) * c);
    }
    T &operator[](u32 i) {
        return memory[i];
    }
};

template<typename T>
struct SmallStaticBuffer2 {
    u32 memory;
    u32 size;
    void Init(byte* base, T* memory_, u32 size_) {
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivally copyable");
        size = size_;
        memory = (byte*)memory_ - (byte*)base;
    }
    void Fill(T* from, byte* base, u32 size_) {

        ASSERT(size_ <= size);
        T* buffer = (T*)(base + memory);
        memcpy(buffer, from, size_ * sizeof(T));
    }
    T& GetElement(byte* base, u32 index) {
        return *((T*)(base + memory + index * sizeof(T)));
    }
};
template<typename unit>
struct Timer {
    std::chrono::_V2::system_clock::time_point begin;
    Timer() {
        begin = std::chrono::high_resolution_clock::now();
    }

    auto Now() {
        return std::chrono::high_resolution_clock::now();
    }
    u64 FromBegin() {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<unit>(end - begin).count();
    }
    u64 From(std::chrono::_V2::system_clock::time_point begin_) {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<unit>(end - begin_).count();
    }
    void PrintNow() {
        auto end = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<unit>(end - begin).count();
        global_print("suc", "elapsed: ", delta, '\n');
    }

    ~Timer() {
        PrintNow();
    }
};
typedef std::chrono::milliseconds milli_second_t;
typedef std::chrono::microseconds micro_second_t;
typedef std::chrono::nanoseconds nano_second_t;

template<typename T>
using DynamicBufferDebugMalloc = DynamicBufferGlobal<T, global_malloc_debug,global_free_debug>;
template<typename T>
using DynamicBufferLocalMalloc = DynamicBufferLocal<T, LocalMallocState, local_malloc, local_free_wrapper>;
template<typename T>
using StaticBufferDebugMalloc = StaticBufferGlobal<T, global_malloc_debug,global_free_debug>;
template<typename T>
using StaticBufferLocalMalloc = StaticBufferLocal<T, LocalMallocState, local_malloc, local_free>;

/*
_FORCE_INLINE u64 xy_to_morton_ (u64 x, u64 y) {

    __m128i a = _mm_set_epi64x(0,x);
    a = _mm_clmulepi64_si128(a,a,0);

    __m128i b = _mm_set_epi64x(0,y);
    b = _mm_clmulepi64_si128(b,b,0);

    u64 l = _mm_extract_epi64(a, 0);
    u64 r = _mm_extract_epi64(b, 0);
    return l | (r << 1);
}
*/
