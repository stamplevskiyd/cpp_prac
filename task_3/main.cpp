#include <iostream>
class A {
public:
// ...
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

template <class T, class T1 = T>
struct custom_allocator {
    using value_type = T;
    custom_allocator() noexcept {};
    template <class U> custom_allocator (const custom_allocator<U>&) noexcept {};
    T* allocate (std::size_t n) {
        return static_cast<T*>(T1::operator new(n * sizeof(T)));
    };
    void deallocate (T* p, std::size_t n) {};
};

template <class T, class U>
constexpr bool operator== (const custom_allocator<T>&, const custom_allocator<U>&) noexcept;

template <class T, class U>
constexpr bool operator!= (const custom_allocator<T>&, const custom_allocator<U>&) noexcept;

int main() {
    //auto sp = std::make_shared<A>();
    //custom_allocator<A> alloc;
    auto sp1 = std::allocate_shared<A>(custom_allocator<A>());
}