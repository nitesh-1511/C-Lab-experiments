
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Student {
public:
    string name;
    int marks;
    char grade;
};

int main() {

    vector<Student> s = {
        {"Ajay", 88, ' '},
        {"Bharath", 76, ' '},
        {"Charan", 95, ' '},
        {"Deepak", 60, ' '},
        {"Kavin", 45, ' '}
    };

    // Assign grades
    for (auto &x : s) {
        if (x.marks >= 90)
            x.grade = 'A';
        else if (x.marks >= 75)
            x.grade = 'B';
        else if (x.marks >= 50)
            x.grade = 'C';
        else
            x.grade = 'F';
    }

    // Sort marks in ascending order
    sort(s.begin(), s.end(),
        [](Student a, Student b) {
            return a.marks < b.marks;
        });

    // Find highest scoring student
    auto highest = max_element(s.begin(), s.end(),
        [](Student a, Student b) {
            return a.marks < b.marks;
        });

    // Calculate total marks
    int total = accumulate(s.begin(), s.end(), 0,
        [](int sum, Student a) {
            return sum + a.marks;
        });

    double average = (double)total / s.size();

    // Display student details
    cout << "\n===== STUDENT RESULT REPORT =====\n";
    cout << "Name\t\tMarks\tGrade\n";
    cout << "--------------------------------\n";

    for (auto x : s) {
        cout << x.name << "\t\t"
             << x.marks << "\t"
             << x.grade << endl;
    }

    if (highest != s.end())
        cout << "\nTopper: " << highest->name
             << " (" << highest->marks << " marks)";

    cout << "\nTotal Marks: " << total;
    cout << "\nAverage Marks: " << average;

    cout << "\n\n===== REPORT COMPLETED =====\n";

    return 0;
}
