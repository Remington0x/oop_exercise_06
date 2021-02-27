#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <iostream>
#include <vector>

template <class T, size_t BLOCK_SIZE>
class allocator {
private:
    std::vector<T*> vec;
    T* buffer = nullptr;
public:
    using allocator_type = allocator;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;

    T* allocate(const std::size_t & n) {
        //std::cout << "WARNING: n = " << n << std::endl;
        if (buffer == nullptr) {
            buffer = new T[BLOCK_SIZE];
            for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
                vec.push_back(&buffer[i]);
            }
        }

        //std::cout << "WARNING: vec.size() = " << vec.size() << std::endl;
        if (vec.size() < n) {
            throw(std::bad_alloc());
        } else {
            T* p = vec.front();
            for (std::size_t i = 0; i < n; ++i) {
				vec.erase(vec.begin());
			}
            return p;
        }
    }

    template<class OTHER_T, class... ARGS>
	void construct(OTHER_T* p, ARGS... arguments) {
		*p =  OTHER_T(std::forward<ARGS>(arguments)...);
	}

    void deallocate(pointer, std::size_t) {
        ;
    }

    explicit allocator(const allocator<T, BLOCK_SIZE> & another_allocator) : allocator() {
        buffer = new T[BLOCK_SIZE];
        for (size_t i = 0; i < BLOCK_SIZE; ++i) {
            buffer[i] = another_allocator.buffer[i];
            vec.push_back(&buffer[i]);
        }
    }

    allocator() : vec(), buffer(nullptr) {
        static_assert(BLOCK_SIZE > 0);
    }

    template <class OTHER_T>
    class rebind {
    public:
        using other = allocator<OTHER_T, BLOCK_SIZE>;
    };

    ~allocator() {
        delete[] buffer;
    }

};


#endif
