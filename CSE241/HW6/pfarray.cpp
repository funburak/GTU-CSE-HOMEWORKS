#include <iostream>
#include <memory>

#include "pfarray.h"

using namespace std;

namespace DynamicArray{

    template<class T>
    PFArray<T>::Iterator::Iterator(shared_ptr<T> d, int s): iter(d), index(s){}

    template<class T>
    T& PFArray<T>::Iterator::operator*(){
        return *(iter.get() + index);
    }

    template<class T>
    T* PFArray<T>::Iterator::operator->(){
        return &(iter.get() + index);
    }

    // Subtracts two iterator indexes and return the difference int.
    template<class T>
    int PFArray<T>::Iterator::operator-(const Iterator &other){
        if(index < other.index){
            throw out_of_range("Index is out of range.");
        }
        return index - other.index;
    }

    // Adds difference_type such a pointer diff to Iterator. Used for algorithm functions.
    template<class T>
    typename PFArray<T>::Iterator PFArray<T>::Iterator::operator+(difference_type n){
        return Iterator(iter,index + n);
    }

    // Subtract difference_type such as a pointer diff from Iterator. Used for algorithm functions.
    template<class T>
    typename PFArray<T>::Iterator PFArray<T>::Iterator::operator-(difference_type n){
        return Iterator(iter,index - n);
    }

    // Pre increment operator. Increments the objects index and returns it.
    template<class T>
    typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator++(){
        ++index;
        return *this;
    }

    // Post-increment operator. Increments the objects index but returns the previous object.
    template<class T>
    typename PFArray<T>::Iterator PFArray<T>::Iterator::operator++(int a){
        Iterator temp(*this);
        ++index;
        return temp;
    }

    // Pre-decrement operator. Decrements the objects index and returns it.
    template<class T>
    typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator--(){
        --index;
        return *this;
    }

    // Post-decrement operator. Decrements the objects index but returns the previous object.
    template<class T>
    typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator--(int a){
        Iterator temp(*this);
        --index;
        return temp;
    }

    // Checks whether the shared_ptr's and indexes are same.
    template<class T>
    bool PFArray<T>::Iterator::operator==(const Iterator &other)const{
        return (iter == other.iter && index == other.index);
    }

    // Checks whether the shared_ptr's and indexes are not same by calling the operator==.
    template<class T>
    bool PFArray<T>::Iterator::operator!=(const Iterator &other)const{
        return !(*this == other);
    }

    // Compares the indexes of two Iterators.
    template<class T>
    bool PFArray<T>::Iterator::operator<(const Iterator &other) const{
        return index < other.index;
    }

    // Compares the indexes of two Iterators.
    template<class T>
    bool PFArray<T>::Iterator::operator>=(const Iterator &other) const{
        return index >= other.index;
    }

    // Default constructor. Opens up 1 space.
    template<class T>
    PFArray<T>::PFArray(){
        used = 0;
        capacity = 1;
        data = shared_ptr<T>(new T[capacity],default_delete<T[]>()); // point shared_ptr to an array
    }

    // Constructor. Opens up size space.
    template<class T>
    PFArray<T>::PFArray(int size){
        used = 0;
        capacity = size;
        data = shared_ptr<T>(new T[capacity],default_delete<T[]>()); // point shared_ptr to an array
    }

    // Copy constructor.
    template<class T>
    PFArray<T>::PFArray(const PFArray &other){
        cout << "Copy constructor for PFArray!" << endl;
        used = other.used;
        capacity = other.capacity;
        data = shared_ptr<T>(new T[capacity],default_delete<T[]>()); // point shared_ptr to an array
        copy(other.data.get(),other.data.get()+other.used,data.get());
    }

    // Move constructor. Steals the objects members.
    template<class T>
    PFArray<T>::PFArray(PFArray &&other){
        used = other.used;
        capacity = other.capacity;
        data.reset(other.get());
    }

    // Assignment operator. Works same as copy constructor.
    template<class T>
    PFArray<T>& PFArray<T>::operator=(const PFArray &other){
        used = other.used;
        capacity = other.capacity;
        data = shared_ptr<T>(new T[capacity],default_delete<T[]>()); // point shared_ptr to an array
        copy(other.data.get(),other.data.get()+other.used,data.get());
        return *this;
    }

    // Move assignment operator. Works same as move constructor.
    template<class T>
    PFArray<T>& PFArray<T>::operator=(PFArray &&other){
        used = other.used;
        capacity = other.capacity;
        data.reset(other.get());
    }

    // Checks whether the container is empty. Which means there are no used elements.
    template<class T>
    bool PFArray<T>::empty() {
        return used == 0;
    }

    // Returns the used elements.
    template<class T>
    int PFArray<T>::size() const{
        return used;
    }

    // Erases the element pointed by the Iterator. Subtracts Iterator it from begin iterator.
    template<class T>
    void PFArray<T>::erase(Iterator it){
        if(it < begin() || it >= end()){
            throw out_of_range("Iterator out of range!");
        }
        int index = it - begin();
        for(int i=index; i< used-1; ++i){
            *(data.get()+i) = *(data.get()+i+1);
        }
        --used;
    }

    // Clears all content.
    template<class T>
    void PFArray<T>::clear(){
        data.reset();
        used = 0;
        capacity = 0;
    }

    // Adds element to the container. First checks if used is greater or equal to capacity. If so multiply
    // capacity by 2. Creates a temp object with new_capacity, stores elements to temp object and then 
    // assign this object to temp. Finally add element pointed by the Iterator end.
    template<class T>
    void PFArray<T>::addElement(const T& element){
        if(used >= capacity){
            capacity *= 2;
            PFArray<T> temp(capacity);
            copy(data.get(),data.get()+used,temp.data.get());
            temp.used = this->used;
            *(this) = temp;
        }
        Iterator iter = this->end();
        *iter = element;
        ++used;
    }

    // Returns the capacity of container.
    template<class T>
    int PFArray<T>::getCapacity() const {
        return capacity;
    }

    // Returns begin Iterator.
    template<class T>
    typename PFArray<T>::Iterator PFArray<T>::begin(){
        return Iterator(data,0);
    }

    // Returns constant begin Iterator.
    template<class T>
    const typename PFArray<T>::Iterator PFArray<T>::cbegin(){
        return Iterator(data,0);
    }

    // Returns end Iterator.
    template<class T>
    typename PFArray<T>::Iterator PFArray<T>::end(){
        return Iterator(data,used);
    }

    // Returns constant end Iterator.
    template<class T>
    const typename PFArray<T>::Iterator PFArray<T>::cend(){
        return Iterator(data,used);
    }
    
} // end namespace