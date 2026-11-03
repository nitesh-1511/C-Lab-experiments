
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Resource {
    string name;

public:
    Resource(string n) {
        name = n;
        cout << name << " Created!" << endl;
    }

    ~Resource() {
        cout << name << " Released!" << endl;
    }

    void use() {
        cout << "Using " << name << endl;
    }
};

class MySmartPointer {
    Resource* ptr;

public:
    MySmartPointer(Resource* p) {
        ptr = p;
    }

    ~MySmartPointer() {
        delete ptr;
        cout << "Custom Pointer Destroyed!" << endl;
    }

    Resource* operator->() {
        return ptr;
    }

    MySmartPointer(const MySmartPointer&) = delete;
    MySmartPointer& operator=(const MySmartPointer&) = delete;
};

int main() {
    cout << "SMART RESOURCE MANAGEMENT\n";

    {
        cout << "\n1. CUSTOM POINTER\n";
        MySmartPointer p(new Resource("File"));
        p->use();
    }

    {
        cout << "\n2. UNIQUE POINTER\n";
        unique_ptr<Resource> p(new Resource("Database"));
        p->use();
    }

    {
        cout << "\n3. SHARED POINTER\n";
        shared_ptr<Resource> p1(new Resource("Cloud"));
        shared_ptr<Resource> p2 = p1;

        p1->use();
        cout << "Owners: " << p1.use_count() << endl;
    }

    cout << "\nAll Resources Released!";
    return 0;
}
