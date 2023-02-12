#include <iostream>
#include <list>

#include "dayofyear.h"

using namespace std;


namespace DOY{

    DayOfYearSet::DayOfYear::DayOfYear(){ // Set date to January 1
        day = 1;
        month = 1;
    }

    DayOfYearSet::DayOfYear::DayOfYear(int d){
        if(d > 31){
            d = d % 31;
        }
        day = d;
        month = 1;
    }

    DayOfYearSet::DayOfYear::DayOfYear(int d, int m){
        if(m > 12){ // If month is larger than 12 take the mod 12 of it
            m = m % 12;
        }
        else if(m < 0){ // If m is negative make it positive
            m = -m;
        }
        else if (m == 0){ // If m is zero consider it as 1 which means January
            m = 1;
        }
        if(d < 0){ // If given d is negative make it positive
            d = -d;
        }
        switch(m){ // Take mod of the each month most day possible
            case 1:
                d = d % 31;
                break;
            case 2:
                d = d % 29;
                break;
            case 3:
                d = d % 31;
                break;
            case 4:
                d = d % 30;
                break;
            case 5:
                d = d % 31;
                break;
            case 6:
                d = d % 30;
                break;
            case 7:
                d = d % 31;
                break;
            case 8:
                d = d % 31;
                break;
            case 9:
                d = d % 30;
                break;
            case 10:
                d = d % 31;
                break;
            case 11:
                d = d % 30;
                break;
            case 12:
                d = d % 31;
                break;
        }
        day = d;
        month = m;
    }

    void DayOfYearSet::DayOfYear::setDay(int d){
        day = d;
    }

    void DayOfYearSet::DayOfYear::setMonth(int m){
        month = m;
    }

    int DayOfYearSet::DayOfYear::getDay() const{
        return day;
    }

    int DayOfYearSet::DayOfYear::getMonth() const{
        return month;
    }

    ostream &operator<<(ostream &out, DayOfYearSet::DayOfYear &obj){
        obj.printDate();
        return out;
    }

    void DayOfYearSet::DayOfYear::printDate() const{
        switch(month){
            case 1:
                cout << day << ' ' << "January" << endl;
                break;
            case 2:
                cout << day << ' ' << "February" << endl;
                break;
            case 3:
                cout << day << ' ' << "March" << endl;
                break;
            case 4:
                cout << day << ' ' << "April" << endl;
                break;
            case 5:
                cout << day << ' ' << "May" << endl;
                break;
            case 6:
                cout << day << ' ' << "June" << endl;
                break;
            case 7:
                cout << day << ' ' << "July" << endl;
                break;
            case 8:
                cout << day << ' ' << "August" << endl;
                break;
            case 9:
                cout << day << ' ' << "September" << endl;
                break;
            case 10:
                cout << day << ' ' << "October" << endl;
                break;
            case 11:
                cout << day << ' ' << "November" << endl;
                break;
            case 12:
                cout << day << ' ' << "December" << endl;
                break;
            default:
                cerr << "Illegal month value!!!" << endl;
                break;    
        }
    }

    int DayOfYearSet::DayOfYear::calculateDay(){
        switch(month){
            case 1:
                return day;
                break;
            case 2:
                return 31 + day;
                break;
            case 3:
                return 31 + 29 + day;
                break;
            case 4:
                return 31 + 29 + 31 + day;
                break;
            case 5:
                return 31 + 29 + 31 + 30 + day;
                break;
            case 6:
                return 31 + 29 + 31 + 30 + 31 + day;
                break;
            case 7:
                return 31 + 29 + 31 + 30 + 31 + 30 + day;
                break;
            case 8:
                return 31 + 29 + 31 + 30 + 31 + 30 + 31 + day;
                break;
            case 9:
                return 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + day;
                break;
            case 10:
                return 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
                break;
            case 11:
                return 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
                break;
            case 12:
                return 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + day;
                break;
        }
        return 0;
    }

    DayOfYearSet::DayOfYearSet(){
        elements = 1;
        date = new DayOfYear[elements];
    }

    DayOfYearSet::DayOfYearSet(int size){
        elements = size;
        date = new DayOfYear[elements];
    }

    DayOfYearSet::DayOfYearSet(list<DayOfYear> dates){
        elements = dates.size();
        date = new DayOfYear[elements];
        
        int i = 0;
        for(auto iter:dates){
            date[i] = DayOfYear(iter);
            date[i].setDay(iter.getDay());
            date[i].setMonth(iter.getMonth());
            i++;
        }
    }

    DayOfYearSet::DayOfYearSet(const DayOfYearSet &other){
        elements = other.elements;
        date = new DayOfYear[other.elements];
        for(int i=0; i<elements; ++i){
            date[i].setDay(other.date[i].getDay());
            date[i].setMonth(other.date[i].getMonth());
        }
    }

    DayOfYearSet::~DayOfYearSet(){
        delete [] date;
        date = nullptr;
    }

    ostream &operator<<(ostream &out, DayOfYearSet &obj){
        out << '{';
        for(int i=0; i<obj.size(); ++i){
            out << obj.date[i].getDay() << "/" << obj.date[i].getMonth() <<  ' ';
        }
        out << '}' << endl;
        return out;
    }

    DayOfYearSet& DayOfYearSet::operator=(const DayOfYearSet &other){
        delete [] this->date;
        
        elements = other.elements;
        date = new DayOfYear[elements];

        for(int i=0; i<elements; ++i){
            date[i].setDay(other.date[i].getDay());
            date[i].setMonth(other.date[i].getMonth());
        }

        return *this;
    }

    // First checks the number of elements of each set. If they are not equal returns false.
    // If their number of elements are equal, it compares the date array 
    bool DayOfYearSet::operator==(const DayOfYearSet &other) const{
        int same = 0;
        
        if(this->size() != other.size()){
            return false;
        }
        
        for(int i=0; i<this->size(); ++i){
            for(int j=0; j<this->size(); ++j){
                if(this->date[i].getDay() == other.date[j].getDay() && this->date[i].getMonth() == other.date[j].getMonth()){
                    same++;
                }
            }
        }

        if(same == this->size()){
            return true;
        }

        return false;
    }

    bool DayOfYearSet::operator!=(const DayOfYearSet &other) const{
            return !(this->operator==(other));
    }

    // Removes the element at the given index.
    // If index is out of the array border returns *this.
    DayOfYearSet DayOfYearSet::remove(int index){
        if(index >= this->elements){
            cerr << "Out of size!!" << endl;
            return *this;
        }

        for(int i=index;i<this->elements-1; ++i){
            this->date[i] = this->date[i+1];
        }

        this->elements--;

        return *this;
    }

    // Checks whether the element which is going to be added is already exists in the array. If exists, return.
    // If the added element is unique the element will be added to the last index.
    void DayOfYearSet::operator+(const DayOfYear &other){
        for(int i=0; i<this->size(); ++i){
            if(this->date[i].getDay() == other.getDay() && this->date[i].getMonth() == other.getMonth()){
                cout << "That element is already in the set!" << endl;
                return;
            }   
        }

        DayOfYearSet temp;
        temp.elements = elements + 1;
        temp.date = new DayOfYear[temp.elements];
        for(int i=0; i<this->elements; ++i){
            temp.date[i].setDay(this->date[i].getDay());
            temp.date[i].setMonth(this->date[i].getMonth());
        }

        temp.date[elements].setDay(other.getDay());
        temp.date[elements].setMonth(other.getMonth());

        *this = temp;

    }

    // Returns the uninon set of two sets. (A U B)
    DayOfYearSet DayOfYearSet::operator+(const DayOfYearSet &other) const{
        int common_element = 0;
        for(int i=0; i<this->elements; ++i){
            for(int j=0; j<other.elements; ++j){
                if(this->date[i].getDay() == other.date[j].getDay() && this->date[i].getMonth() == other.date[j].getMonth()){
                    common_element++;
                }
            }
        }
        DayOfYearSet temp(this->elements + other.elements - common_element);

        int k = 0;
        for(int i=0; i<this->elements; ++i){
            bool same = false;
            for(int j=0; j<other.elements; ++j){
                if(this->date[i].getDay() == other.date[j].getDay() && this->date[i].getMonth() == other.date[j].getMonth()){
                    same = true;
                    break;
                }
            }
            temp.date[k] = this->date[i];
            k++;    
        }

        for (int i = 0; i < other.elements; ++i) {
            bool same = false;
            for (int j = 0; j < this->elements; ++j) {
                if (other.date[i].getDay() == this->date[j].getDay() && other.date[i].getMonth() == this->date[j].getMonth()) {
                    same = true;
                    break;
                }
            }
            if (!same) {
                temp.date[k] = other.date[i];
                k++;
            }
        }
        return temp;
    }
    
    // Returns the difference set of two sets (A/B). If there are equal elements it replaces that element with (1,1).
    DayOfYearSet DayOfYearSet::operator-(const DayOfYearSet &other) const{
        int count = 0;
        for (int i = 0; i < this->elements; ++i) {
            bool same = false;
            for (int j = 0; j < other.elements; ++j) {
                if (this->date[i].getDay() == other.date[j].getDay() && this->date[i].getMonth() == other.date[j].getMonth()) {
                    same = true;
                    break;
                }
            }
            if (!same) {
                count++;
            }
        }

        DayOfYearSet temp(count);
        int k = 0;
        for (int i = 0; i < this->elements; ++i) {
            bool same = false;
            for (int j = 0; j < other.elements; ++j) {
                if (this->date[i].getDay() == other.date[j].getDay() && this->date[i].getMonth() == other.date[j].getMonth()) {
                    same = true;
                    break;
                }
            }
            if (!same) {
                temp.date[k] = this->date[i];
                k++;
            }
        }

        return temp;
    }
    
    // Removes the DayOfYear object from the set. First looks for the DayOfYear object in the DayOfYearSet
    // if it exist finds the index of the DayOfYear object and shift all the elements except that object. If
    // the DayOfYear object couldn't found it return *this.
    DayOfYearSet DayOfYearSet::operator-(const DayOfYear &date){
        int index = 0;
        for(int i=0; i<this->elements; ++i){
            if(this->date[i].getDay() != date.getDay() && this->date[i].getMonth() != date.getMonth()){
                index++;
            }
        }
        if(index == 0){
            return *this;
        }

        for(int j=index-1; j<this->elements-1; ++j){
            this->date[j] = this->date[j+1];
        }

        this->elements--;

        return *this;
    }

    // Returns the intersection set of two sets. (A ∩ B). If they do not share same element it returns empty set.
    DayOfYearSet DayOfYearSet::operator^(const DayOfYearSet &other) const {
        int same = 0;
        for (int i = 0; i < this->elements; ++i) {
            for (int j = 0; j < other.elements; ++j) {
                if (this->date[i].getDay() == other.date[j].getDay() && this->date[i].getMonth() == other.date[j].getMonth()) {
                    same++;
                }
            }
        }

        if (same == 0) {
            cout << "These two set do not share same element!" << endl;
            return DayOfYearSet(0);
        }

        DayOfYearSet temp(same);
        int k = 0;
        for (int i = 0; i < this->elements; ++i) {
            for (int j = 0; j < other.elements; ++j) {
                if (this->date[i].getDay() == other.date[j].getDay() && this->date[i].getMonth() == other.date[j].getMonth() && (i != j || this != &other)) {
                    temp.date[k] = this->date[i];
                    k++;
                    if (k >= same) {
                        return temp;
                    }
                }
            }
        }

        return temp;
    }


    // Returns the complement set. (A'). First calculates the day of the year. Then subtract 366 from it and find the corresponding
    // date of the year
    DayOfYearSet& DayOfYearSet::operator!(){
        DayOfYearSet *temp = this;

        int dayofyear;

        for(int i=0; i<elements; ++i){
            dayofyear = date[i].calculateDay();
            temp->date[i] = temp->date[i].calculateDayOfYear(366 - dayofyear);
        }
        
        return *temp;
    }

    // First checks whether the given index is less than number of elements and greater than 0, if so returns an DayOfYear object with 
    // no parameter constructor. If not it returns the element at the given index.
    DayOfYearSet::DayOfYear DayOfYearSet::operator[](int index){
        if(index >= this->elements || index < 0){
            cerr << "Illegal index value. Returning 1 January" << endl;
            return DayOfYear(1,1);
        }

        int res_day = this->date[index].getDay();
        int res_month = this->date[index].getMonth();

        
        return DayOfYear(res_day,res_month);
    }

} // end namespace