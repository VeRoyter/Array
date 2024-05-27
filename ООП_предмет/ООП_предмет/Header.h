#include <initializer_list>
#include <iterator>
#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <algorithm>
template <class T, std::size_t N> class My_Array {
private:
    std::size_t arr_lenght = 0;
    T* arr_data = new T[N];
public:
    struct Iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        reference operator[](difference_type n) const { return *(m_ptr + n); }

        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { --m_ptr; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        Iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        Iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }

        friend Iterator operator+(Iterator it, difference_type n) { return it += n; }
        friend Iterator operator+(difference_type n, Iterator it) { return it += n; }
        friend Iterator operator-(Iterator it, difference_type n) { return it -= n; }
        friend difference_type operator-(const Iterator& a, const Iterator& b) { return a.m_ptr - b.m_ptr; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }
        friend bool operator< (const Iterator& a, const Iterator& b) { return a.m_ptr < b.m_ptr; }
        friend bool operator> (const Iterator& a, const Iterator& b) { return a.m_ptr > b.m_ptr; }
        friend bool operator<= (const Iterator& a, const Iterator& b) { return a.m_ptr <= b.m_ptr; }
        friend bool operator>= (const Iterator& a, const Iterator& b) { return a.m_ptr >= b.m_ptr; }
    private:
        pointer m_ptr;
    };
    Iterator begin() { return Iterator(arr_data); }
    Iterator end() { return Iterator(arr_data + arr_lenght); }
    Iterator cbegin() const { return Iterator(arr_data); }
    Iterator cend() const { return Iterator(arr_data + arr_lenght); }
    std::reverse_iterator<Iterator> rbegin() const { return std::reverse_iterator<Iterator>(end()); }
    std::reverse_iterator<Iterator> rend() const { return std::reverse_iterator<Iterator>(begin()); }
    My_Array() = default;

    My_Array(std::initializer_list<T> list) : My_Array() { //Исправил проверку
        std::size_t copy_size = std::min(list.size(), N);
        std::size_t i = 0;
        for (auto element : list) {
            if (i < copy_size) {
                arr_data[i] = element;
                ++i;
            }
            else {
                break;
            }
        }
    }
    My_Array(const My_Array& other) { // сделал конструктор
        std::copy(other.arr_data, other.arr_data + other.arr_lenght, arr_data);
        arr_lenght = other.arr_lenght;
    }

    My_Array(My_Array<T, N>&& rv);
    My_Array<T, N>& operator=(My_Array<T, N>&& rv);

    ~My_Array() { delete[]arr_data; }
    T& front() {
        return arr_data[0];
    }
    T& back() {
        return arr_data[this->size() - 1];
    }
    T& at(std::size_t N1) {
        if (N1 >= N) { throw std::out_of_range("Index out of range"); };
        return arr_data[N1];
    }
    T& operator[](std::size_t ind) {
        assert(ind >= 0 && ind < arr_lenght);
        return arr_data[ind];
    }
    My_Array& operator=(const My_Array& Arr1) {
        if (this != &Arr1) {
            std::copy(Arr1.arr_data, Arr1.arr_data + N, arr_data);
            arr_lenght = Arr1.arr_lenght;
        }
        return *this;
    }
    template <class T1, std::size_t N1>
    bool operator==(const My_Array<T1, N1>& Arr) const {
        if (N != N1) { return false; } // Check for size equality
        for (std::size_t i = 0; i < N; ++i) {
            if (this->arr_data[i] != Arr.at(i)) return false;
        }
        return true;
    }

    template< class T1, std::size_t N1 >
    bool operator==(My_Array<T1, N1>& Arr) {
        for (std::size_t i = 0; i < N; ++i) {
            if (this->arr_data[i] != Arr.at(i)) return false;
        }
        return true;
    }
    template<class T1, std::size_t N1>
    bool operator!=(My_Array<T1, N1>& Arr) {
        int X = std::min(N, N1);
        for (std::size_t i = 0; i < X; ++i) {
            if (this->arr_data[i] != Arr.at(i)) return true;
        }
        return false;
    }
    template< class T1, std::size_t N1 >
    bool operator<(My_Array<T1, N1>& Arr) {
        return(this->size() < Arr.size());
    }
    template< class T1, std::size_t N1 >
    bool operator>(My_Array<T1, N1>& Arr) {
        return(this->size() > Arr.size());
    }
    template< class T1, std::size_t N1 >
    bool operator<=(My_Array<T1, N1>& Arr) {
        return(this->size() <= Arr.size());
    }
    template< class T1, std::size_t N1 >
    bool operator>=(My_Array<T1, N1>& Arr) {
        return(this->size() >= Arr.size());
    }

    T* data() { return arr_data; }

    void fill(const T& value) {
        for (std::size_t i = 0; i < N; ++i) {
            arr_data[i] = value;
        }
        arr_lenght = N;
    }
    bool empty() { // empty добаввил
        return this->begin() == this->end();
    }
    std::size_t size() const {
        return arr_lenght;
    }
    template <std::size_t N1>  // а.Свап 
    void swap(My_Array<T, N1>& arr1) {
        if (this != &arr1) {
            for (std::size_t i = 0; i < N; ++i) {
                std::swap(arr_data[i], arr1.at(i));
            }
            std::swap(this->arr_lenght, arr1.arr_lenght);
        }
    }
    void push_back(T value) {
        if (arr_lenght < N) {

            arr_data[arr_lenght++] = value;

        }
        else {
            throw std::out_of_range("My_Array is full");
        }
    }
    void erase(std::size_t index) {
        if (index >= this->size()) {
            throw std::out_of_range("Index out of range");
        }

        for (std::size_t i = index; i < this->size() - 1; ++i) {
            arr_data[i] = arr_data[i + 1];
        }

        --arr_lenght;
    }
};

template <typename T, typename C> //Mas size
typename C::size_type max_size(const C& a) {
    return a.size();
}

template <class T, class U, std::size_t N1, std::size_t N>
void swap(My_Array<T, N1>& arr1, My_Array<U, N>& arr2) {
    arr1.swap(arr2);
}
