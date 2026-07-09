//1. Declaring Variables
#include <iostream>
using namespace std;

int main(){
    int myNum = 20;
    double myFloatNum = 20.95;
    char myLetter = 'D';
    string myText = "Valentinus";
    bool myBoolean = true;
    std::cout << myNum << endl;
    std::cout << myFloatNum << endl;
    std::cout << myLetter << endl;
    std::cout << myText << endl;
    std::cout << myBoolean << endl;
    return 0; 
}

//2. Multiple Variables

int main(){
    int x, y, z;
    x = y = z = 20;
    cout << x + y + z;
    return 0;
}

//3. Constants
int main(){
    const int minutesPerHour = 55;
    cout << minutesPerHour;
    return 0;
}

//Real-Life Examples
int main(){
    // Student data
    int studentID = 15;
    int studentAge = 23;
    double studentFee = 75.25;
    char studentGrade = 'B';

    // Print variables
    cout << "Student ID: " << studentID << "\n";
    cout << "Student Age: " << studentAge << "\n";
    cout << "Student Fee: " << studentFee << "\n";
    cout << "Student Grade: " << studentGrade << "\n";
    return 0;
}