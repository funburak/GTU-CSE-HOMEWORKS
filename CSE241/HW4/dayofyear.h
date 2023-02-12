#ifndef DAYOFYEAR_H
#define DAYOFYEAR_H

#include <iostream>
#include <list>

using namespace std;

namespace DOY{

    class DayOfYearSet{
        public:
            class DayOfYear{
                public:
                    DayOfYear(); 
                    explicit DayOfYear(int d); 
                    DayOfYear(int day, int month);

                    void setDay(int d);
                    void setMonth(int m);
                    int getDay() const;
                    int getMonth() const;
                    void printDate() const;
                    int calculateDay(); const // Returns the number of which day of the year (Max 366 days)
                    DayOfYear calculateDayOfYear(int number){ // I have to implement this function here because it gives incompatible error in .cpp file
                        int d,m;
                        if(number <= 31){
                            d = number % 32;
                            m = 1;
                            return DayOfYear(d,m);
                        }
                        else if(number > 31 && number <= 60){
                            d = (number % 60 + 31) % 30;
                            m = 2;
                            return DayOfYear(d,m);
                        }
                        else if(number > 60 && number <=91){
                            d = (number % 91 + 60) % 32;
                            m = 3;
                            return DayOfYear(d,m);
                        }
                        else if(number > 90 && number <=120){
                            d = (number % 120 + 90) % 31;
                            m = 4;
                            return DayOfYear(d,m);
                        }
                        else if(number > 120 && number <=151){
                            d = (number % 151 + 120) % 32;
                            m = 5;
                            return DayOfYear(d,m);
                        }
                        else if(number > 151 && number <=181){
                            d = (number % 181 + 151) + 31;
                            m = 6;
                            return DayOfYear(d,m);
                        }
                        else if(number > 181 && number <=212){
                            d = (number % 212 + 181) % 32;
                            m = 7;
                            return DayOfYear(d,m);
                        }
                        else if(number > 212 && number <=243){
                            d = (number % 243 + 212) % 32;
                            m = 8;
                            return DayOfYear(d,m);
                        }
                        else if(number > 243 && number <=273){
                            d = (number % 273 + 243) % 31;
                            m = 9;
                            return DayOfYear(d,m);
                        }
                        else if(number > 273 && number <=304){
                            d = (number % 304 + 273) & 32;
                            m = 10;
                            return DayOfYear(d,m);
                        }
                        else if(number > 304 && number <= 334){
                            d = (number % 334 + 304) % 31;
                            m = 11;
                            return DayOfYear(d,m);
                        }
                        else if(number < 334 && number <= 366){
                            d = (number % 366 + 334) % 32;
                            m = 12;
                            return DayOfYear(d,m);
                        }
                        return DayOfYear(1,1);    
                    }

                private:
                    int day;
                    int month;
            };

        DayOfYearSet();
        DayOfYearSet(int size);
        DayOfYearSet(list<DayOfYear> dates);
        DayOfYearSet(const DayOfYearSet &other);
        ~DayOfYearSet(); // Destructor
        friend ostream &operator<<(ostream &out, DayOfYearSet& obj);
        DayOfYearSet &operator=(const DayOfYearSet &other);
        bool operator==(const DayOfYearSet &other) const;
        bool operator!=(const DayOfYearSet &other) const;
        DayOfYearSet remove(int index); // Removes an element from the set
        int size() const {return elements;}; // Returns the size of DayOfYear array
        void operator+(const DayOfYear &other); // Adds an element to the set
        DayOfYearSet operator+(const DayOfYearSet &other) const; // Returns the union set
        DayOfYearSet operator-(const DayOfYearSet &other) const; // Returns the difference set
        DayOfYearSet operator-(const DayOfYear &date); // Removes an element from the set
        DayOfYearSet operator^(const DayOfYearSet &other) const; // Returns the intersection set
        DayOfYearSet& operator!(); // Returns the complement set
        DayOfYear operator[](int index); // Returns the element of the given index
        
        private:
            DayOfYear *date;
            int elements;
    };
} // end namespace

#endif // DAYOFYEAR_H