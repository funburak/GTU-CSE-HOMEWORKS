#ifndef PFARRAY_H
#define PFARRAY_H

#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

namespace DynamicArray{

    template<class T>
    class PFArray{
        public:
            class Iterator{
                public:
                    // These using declarations are necessary for STL algorithms.
                    // For example iterator_category and value_type are for sort and find function.
                    using iterator_category = random_access_iterator_tag;
                    using value_type = T;
                    using difference_type = std::ptrdiff_t;
                    using pointer = T*;
                    using reference = T&;

                    
                    Iterator(shared_ptr<T> d, int s); // Constructor

                    T &operator*();
                    T *operator->();
                    int operator-(const Iterator &other);
                    Iterator operator+(difference_type n);
                    Iterator operator-(difference_type n);
                    Iterator& operator++(); // Pre increment
                    Iterator operator++(int a); // Post increment
                    Iterator& operator--(); // Pre decrement
                    Iterator& operator--(int); // Post decrement
                    bool operator==(const Iterator &other) const;
                    bool operator!=(const Iterator &other) const;
                    bool operator<(const Iterator &other) const;
                    bool operator>=(const Iterator &other) const;

                private:
                    shared_ptr<T> iter;
                    int index;
            };

            PFArray();
            PFArray(int size);
            PFArray(const PFArray &other); // Copy constructor
            PFArray(PFArray &&other); // Move constructor

            PFArray& operator=(const PFArray &other);// Assignment operator
            PFArray& operator=(PFArray &&other); // Move assignment operator

            bool empty(); // Test whether container is empty
            int size() const; // Return container size
            void erase(Iterator it); // Erase element pointed by the Iterator
            void clear(); // Clear all content
            void addElement(const T& element); // Adds element to the container
            int getCapacity() const; // Return the capacity
            Iterator begin(); // Returns iterator to begining
            const Iterator cbegin(); // Returns a constant iterator to beginnig
            Iterator end(); // Returns iterator to end
            const Iterator cend(); // Returns a constant iterator to end

        private:
            int used;
            int capacity;
            shared_ptr<T> data;
    };

} // end namespace

#endif // PFARRAY_H