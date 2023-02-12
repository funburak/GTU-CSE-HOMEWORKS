#include <iostream>
#include <list>
#include <fstream>

#include "dayofyear.h"

using namespace std;
using namespace DOY; // Day of Year namespace

typedef DayOfYearSet::DayOfYear DayOfYear;

int main(){
    list<DayOfYear> date = {DayOfYear(2,12), DayOfYear(5,5)};
    list<DayOfYear> date2 = {DayOfYear(5,5), DayOfYear(2,12)};
    list<DayOfYear> date3 = {DayOfYear(1,12),DayOfYear(6,6),DayOfYear(2,12)};
    for(auto iter: date){
        iter.printDate();
    }


    DayOfYear singledate(20,11);
    DayOfYear remove1(6,6);
    DayOfYear remove2(5,5);
    ofstream file; 
    file.open("results.txt",std::ios::app); // Open file as append mode
    file << "FILE OPENED-----------------------------" << endl;

    DayOfYearSet set1(date);
    cout << "Set1=";
    cout << set1 << endl;
    file << "Set1=";
    file << set1 << endl;
    DayOfYearSet set2(date2);
    cout << "Set2=";
    cout << set2 << endl;
    file << "Set2=";
    file << set2 << endl;

    if(set1 == set2){
        cout << "Set1 and Set2 are equal!" << endl;
        file << "Set1 and Set2 are equal!" << endl;
    }

    DayOfYearSet set3(date3);
    cout << "Set3=";
    cout << set3 << endl;
    file << "Set3=";
    file << set3 << endl;
    DayOfYearSet set4(set3);
    cout << "Set4=Set3=";
    file << "Set4=Set3=";
    cout << set4 << endl;
    file << set4 << endl;


    cout << "Add (20,11) to the set1 and set3" << endl;
    file << "Add (20,11) to the set1 and set3" << endl;
    set1 + singledate;
    set3 + singledate;
    cout << "Set1=";
    cout << set1 << endl;
    file << "Set1=";
    file << set1 << endl;
    cout << "Set3=";
    file << "Set3=";
    cout << set3 << endl;
    file << set3 << endl;

    cout << "Remove index 2 from set2 and set3" << endl;
    file << "Remove index 2 from set2 and set3" << endl;
    set2.remove(2);
    set3.remove(2);
    cout << "Set2= ";
    file << "Set2=";
    cout << set2 << endl;
    file << set2 << endl;
    cout << "Set3=";
    file << "Set3=";
    cout << set3 << endl;
    file << set3 << endl;
    
    cout << "Set3 -(6,6)=";
    file << "Set3 - (6,6)=";
    set3 = set3- remove1;
    cout << set3 << endl;
    file << set3 << endl;
    cout << "Set2 -(5,5)=";
    file << "Set2 -(5,5)=";
    set2 = set2 - remove2;
    cout << set2 << endl;
    file << set2 << endl;

    cout << "Set1=";
    file << "Set1=";
    cout << set1 << endl;
    file << set1 << endl;
    cout << "Set3=";
    file << "Set3=";
    cout << set3 << endl;
    file << set3 << endl;
    cout << "Union set = Set1 + Set3=";
    file << "Unionn set = Set1 + Set3=";
    DayOfYearSet union_set = set1 + set3;
    cout << union_set << endl;
    file << union_set << endl;
    
    cout << "Difference = Set1 - Set2=";
    file << "Difference set = Set1 - Set2";
    DayOfYearSet difference = set1- set2;
    cout << difference << endl;
    file << difference << endl;

    cout << "Set1=";
    file << "Set1=";
    cout << set1 << endl;
    file << set1 << endl;
    cout << "Set2=";
    file << "Set2=";
    cout << set2 << endl;
    file << set2 << endl;
    DayOfYearSet intersection = set1^set2;
    cout << "Set1 ^ Set2=";
    file << "Intersection = Set1 ^ Set2=";
    cout << intersection << endl;
    file << intersection << endl;

    cout << "Set1=";
    cout << set1 << endl;
    cout << "Complement set of set1= ";
    DayOfYearSet complement1 = !set1;
    cout << complement1 << endl;

    cout << "Set3=";
    file << "Set3=";
    cout << set3 << endl;
    file << set3 << endl;
    cout << "Complement set of set3=";
    file << "Complement set of set3=";
    DayOfYearSet complement3 = !set3;
    cout << complement3 << endl;
    file << complement3 << endl;



    DayOfYear date4(set1[1]);
    cout << "Second element of set1=" << endl;
    file << "Second element of set1=" << endl;
    cout << date4.getDay() << "/" << date4.getMonth() << endl;
    file << date4.getDay() << '/' << date4.getMonth() << endl;

    cout << "Set == Set2" << endl;
    file << "Set == Set2" << endl;
    cout << "Set1=";
    file << "Set1=";
    cout << set1 << endl;
    file << set1 << endl;
    cout << "Set2= ";
    file << "Set2=";
    cout << set2 << endl;
    file << set2 << endl;
    if(set1 == set2){
        cout << "Set1 and Set2 are equal!" << endl;
        file << "Set1 and Set2 are equal!" << endl;
    }
    else{
        cout << "Set1 and Set2 are not equal!" << endl;
        file << "Set1 and Set2 are not equal!" << endl;
    }

    DayOfYearSet set5(set4);
    cout << "Set4=";
    file << "Set4=";
    cout << set4 << endl;
    file << set4 << endl;
    cout << "Set5=";
    file << "Set5=";
    cout << set5 << endl;
    file << set5 << endl;
    cout << "Set4 == Set5" << endl;
    file << "Set4 == Set5" << endl;
    if(set4 != set5){
        cout << "Set4 and Set5 are not equal!" << endl;
        file << "Set4 and Set5 are not equal!" << endl;
    }
    else{
        cout << "Set4 and Set5 are equal!" << endl;
        file << "Set4 and Set5 are equal!" << endl;
    }

    file << "FILE CLOSED----------------------------------" << endl;
    file.close();
    
    return 0;
}