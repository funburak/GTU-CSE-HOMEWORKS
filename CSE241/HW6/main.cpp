#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <random>

#include "pfarray.h"
#include "pfarray.cpp"

using namespace std;
using namespace DynamicArray;

typedef PFArray<int>::Iterator Iterator;
typedef PFArray<double>::Iterator IteratorD;

int main(){
    PFArray<int> a;
    a.addElement(5);
    a.addElement(10);
    a.addElement(20);
    a.addElement(15);
    a.addElement(25);
    a.addElement(30);
    a.addElement(50);
    a.addElement(48);
    a.addElement(28);
    cout << "Size of PFArray A after adding elements=" << a.size() << endl;
    
    // Printing PFArray int A.
    cout << "PFArray A before= ";
    for(Iterator it=a.cbegin(); it!=a.cend(); it++){
        cout << *it << ' ';
    }
    cout << endl;

    // Erasing element pointed by a.begin() + 1.
    Iterator era = a.begin() + 1;
    a.erase(era);
    cout << "PFArray A after erasing the a.begin()+ 1 iterator=";
    for(Iterator iter = a.begin(); iter!=a.end(); ++iter){
        cout << *iter << ' ';
    }
    cout << endl;

    PFArray<int> even;
    even.addElement(4);
    even.addElement(6);
    even.addElement(10);
    even.addElement(20);

    // Printing PFArray int even.
    cout << "PFArray<int> even= ";
    for(Iterator even_it = even.begin(); even_it != even.end(); even_it++){
        cout << *even_it << " ";
    }
    cout << endl;

    cout << "Calling all_of function on PFArray<int> even" << endl;
    if(all_of(even.begin(),even.end(),[](int x){return x % 2 == 0;})){
        cout << "All numbers are even" << endl;
    }


    // Copy constructor call.
    PFArray<int> b(a);
    cout << "Size B =" << b.size() << endl;
    cout << "PFArray B= ";
    for(Iterator it2= b.cbegin(); it2!=b.cend(); it2++){
        cout << *it2 << ' ';
    }
    cout << endl;



    // Printing PFArray<int> a.
    cout << "PFArray A before sorting." << endl;
    for(Iterator it3=a.cbegin(); it3!=a.cend(); it3++){
        cout << *it3 << ' ';
    }
    cout << endl;

    // Sorting PFarray<int> a.
    cout << "Sorting PFArray A in ascending order using sort function" << endl;
    sort(a.begin(), a.end());

    cout << "Printing sorted PFArray A using for_each function!" << endl;
    for_each(a.begin(), a.end(), [](int x){
        cout << x << " ";
    });
    cout << endl;

    // Checking if sorted is done in correctly.
    cout << "Is PFArray A sorted in a true way. Using is_sorted function to check." << endl;
    if(is_sorted(a.begin(),a.end())){
        cout << "PFArray A is sorted." << endl;
    }
    else{
        cout << "PFArray A is not sorted" << endl;
    }

    // Finding int 20 in PFArray<int> a.
    Iterator it = find(a.begin(), a.end(), 20);
    if (it != a.end()) {
        cout << "Found element 20 at index " << it - a.begin() << endl;
    } else {
        cout << "Element 20 not found" << endl;
    }

    // Reverse the elements of PFArray<int> a.
    cout << "Reversing the PFArray A using reverse function" << endl;
    reverse(a.begin(),a.end());
    for(auto&x : a){
        cout << x << ' ';
    }
    cout << endl;

    // Clearing PFArray<int> a.
    cout << "Clearing PFArray A" << endl;
    a.clear();
    if(a.empty()){
        cout << "PFArray A is Empty!" << endl;
    }
    else{
        cout << "PFArray A is not Empty!" << endl;
    }

    for(auto&x : a){
        cout << x << ' ';
    }
    cout << endl;

    // Fill all elements on PFArray with 1.
    cout << "Assign every element in PFArray B with 1 using fill function." << endl;
    fill(b.begin(),b.end(),1);
    for(Iterator it4 = b.begin(); it4!=b.end(); ++it4){
        cout << *it4 << ' ';
    }
    cout << endl;

    // Creating PFarray<double> d.
    PFArray<double> d;
    d.addElement(2.1);
    d.addElement(3.2);
    d.addElement(1.2);
    d.addElement(5.1);
    d.addElement(4.3);
    d.addElement(2.1);
    d.addElement(5.1);
    cout << "PFArray double D" << endl;
    for(IteratorD iter = d.begin(); iter!= d.end(); iter++){
        cout << *iter << ' ';
    }
    cout << endl;

    // Count how many elements exists in PFArray<double> d.
    cout << "Using count function" << endl;
     for (const double target : {5.1, 2.1, 3.2, 5.3}){
        const int element_count = count(d.cbegin(), d.cend(), target);
        cout << "number: " << target << ", count: " << element_count << '\n';
    }

    // Sorting PFArray<double> d.
    cout << "Sorting PFArray double D" << endl;
    sort(d.begin(),d.end());
    for(IteratorD iter = d.begin(); iter!= d.end(); iter++){
        cout << *iter << ' ';
    }
    cout << endl;

    PFArray<double> d2;
    d2.addElement(5.1);
    d2.addElement(1.3);
    d2.addElement(2.3);
    d2.addElement(5.3);

    cout << "PFArray double d2" << endl;
    for(IteratorD iter2 = d2.begin(); iter2!=d2.end(); iter2++){
        cout << *iter2 << ' ';
    }
    cout << endl;


    // Merging PFArray<double> d and PFArray<double> d2 into vector m.
    vector<double> m;
    merge(d.begin(),d.end(),d2.begin(),d2.end(),back_inserter(m));
    cout << "Merging PFArray double d and PFArray double d2" << endl;
    for(int i=0; i<m.size(); ++i){
        cout << m[i] << " ";
    }
    cout << endl;


    // Shuffle elements of PFArray<double> d.
    cout << "Shuffling PFArray double d using shuffle function" << endl;
    random_device rd;
    mt19937 g(rd());
    shuffle(d.begin(),d.end(),g);
    for(IteratorD iter3 = d.begin(); iter3!=d.end(); iter3++){
        cout << *iter3 << ' ';
    }
    cout << endl;

    return 0;
}