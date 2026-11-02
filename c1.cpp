#include <iostream>
using namespace std;

class Student {
private:
    int rollNo;
    string name;

public:
    // Parameterized Constructor
    Student(int r, string n) {
        rollNo = r;
        name = n;
        cout << "Constructor called" << endl;
    }

    // Member Function
    void display() {
        cout << "\nStudent Details" << endl;
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
    }

    // Destructor
    ~Student() {
        cout << "Destructor called" << endl;
    }
};

int main() {
    Student s1(101, "Nitesh");
    Student s2(102, "Kumaar");

    s1.display();
    s2.display();

    return 0;
}
