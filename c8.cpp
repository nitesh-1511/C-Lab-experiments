#include <iostream>
#include <cstring>
#include <chrono>
#include <utility>
using namespace std;
using namespace chrono;
class String {
private:
    char* data;
    size_t length;
public:
    static int copies,moves;
    String(const char* str = "") {
        if (!str) str = "";
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        copies++;
    }
    String(String&& other) noexcept {
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
        moves++;
    }
    void swap(String& other) noexcept {
        std::swap(data, other.data);
        std::swap(length, other.length);
    }
    String& operator=(const String& other) {
        if (this != &other) {
            String temp(other);
            swap(temp);
        }
        return *this;
    }
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
            moves++;
        }
        return *this;
    }
    String operator+(const String& other) const {
        String result;
        delete[] result.data;
        result.length = length + other.length;
        result.data = new char[result.length + 1];
        strcpy(result.data, data ? data : "");
        strcat(result.data, other.data ? other.data : "");
        return result;
    }
    void display() const {
        cout << (data ? data : "") << endl;
    }
    size_t size() const {
        return length;
    }
    size_t memory() const {
        return length + 1;
    }
    ~String() {
        delete[] data;
    }
};
int String::copies = 0;
int String::moves = 0;
template<typename T>
String createString(T&& value) {
    return String(forward<T>(value));
}
int main() {
    const int SIZE = 50000;
    cout << "SMART STRING MANAGEMENT SYSTEM\n";
    cout << "--------------------------------\n";
    String original("Advanced C++ String Optimization");
    cout << "\n--- STRING INFORMATION ---\n";
    cout << "Original: ";
    original.display();
    cout << "Length: " << original.size() << endl;
    cout << "Memory: " << original.memory() << " bytes\n";
    String extra(" Using Move Semantics");
    String combined = original + extra;
    cout << "\n--- CONCATENATION ---\n";
    combined.display();
    String forwarded = createString("Perfect Forwarding");
    cout << "\n--- FORWARDING ---\n";
    forwarded.display();
    String::copies = 0;
    String::moves = 0;
    auto startCopy = steady_clock::now();
    for (int i = 0; i < SIZE; i++) {
        String temp(original);
    }
    auto endCopy = steady_clock::now();
    auto copyTime =
        duration_cast<microseconds>(endCopy - startCopy);
    int copyCount = String::copies;
    String::moves = 0;
    String* sources = new String[SIZE];
    for (int i = 0; i < SIZE; i++)
        sources[i] = String("Move Optimization Example");
    auto startMove = steady_clock::now();
    for (int i = 0; i < SIZE; i++) {
        String temp(move(sources[i]));
    }
    auto endMove = steady_clock::now();
    auto moveTime =
        duration_cast<microseconds>(endMove - startMove);
    int moveCount = String::moves;
    delete[] sources;
    cout << "\n--- PERFORMANCE REPORT ---\n";
    cout << "Copy Operations : " << copyCount << endl;
    cout << "Move Operations : " << moveCount << endl;
    cout << "Copy Time : "
         << copyTime.count() << " us\n";
    cout << "Move Time : "
         << moveTime.count() << " us\n";
    cout << "\nMemory Optimization Completed!\n";
    return 0;
}