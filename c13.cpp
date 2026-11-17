#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <type_traits>
using namespace std;
template <typename T>
vector<T> processData(const vector<T>& data) {
    static_assert(is_arithmetic_v<T>,
                  "Only numeric types allowed");
    vector<T> result;
    for (T x : data)
        if (x > 0)
            result.push_back(x * 2);
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()),
                 result.end());
    return result;
}
int main() {
    vector<int> data = {-5, 10, 20, -3, 15, 30, 10};
    auto result = processData(data);
    cout << "SMART DATA PIPELINE\n";
    cout << "\nOriginal: ";
    for (int x : data)
        cout << x << " ";
    cout << "\nProcessed: ";
    for (int x : result)
        cout << x << " ";
    int sum = accumulate(result.begin(), result.end(), 0);
    cout << "\n\nSum: " << sum;
    cout << "\nAverage: "
         << (result.empty() ? 0.0 :
             (double)sum / result.size());
    if (!result.empty()) {
        cout << "\nMinimum: " << result.front();
        cout << "\nMaximum: " << result.back();
    }
    int even = 0, odd = 0;
    for (int x : result)
        (x % 2 == 0) ? even++ : odd++;
    cout << "\nEven: " << even;
    cout << "\nOdd: " << odd;
    cout << "\n\nPipeline Completed!\n";
    return 0;
}