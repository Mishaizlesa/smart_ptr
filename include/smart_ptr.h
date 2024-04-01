#include <iostream>
#include <exception>
#include <type_traits>

template<typename T>
class smart_ptr {
private:
    T* data = nullptr;
    int* copy_count = nullptr;

    void clear() {
        (*copy_count)--;
        if (*copy_count == 0) {
            if (data != nullptr) {
                if (std::is_array<T>::value) {
                    delete[] data;
                } else {
                    delete data;
                }
                data = nullptr;
            }
            delete copy_count;
    }
}
public:

    smart_ptr(): data(nullptr), copy_count(nullptr){}

    smart_ptr(T* data) : data(data), copy_count(new int(1)) {}

    smart_ptr(const smart_ptr& other) : data(other.data), copy_count(other.copy_count) {
        (*copy_count)++;
    }

    smart_ptr& operator=(const smart_ptr& other) {
        if (this != &other) {
            clear();
            data = other.data;
            copy_count = other.copy_count;
            (*copy_count)++;
        }
        return *this;
    }

    T& operator*() {
        if (!data) {
            fprintf(stderr, "no memory allocated\n");
            throw std::logic_error("null_ptr");
        }
        return *data;
    }

    T* operator->() {
        if (!data) {
            fprintf(stderr, "no memory allocated\n");
            throw std::logic_error("null_ptr");
        }
        return data;
    }

     ~smart_ptr() {
        if (copy_count) clear();
    }
};
