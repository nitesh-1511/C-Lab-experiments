
#include <iostream>
#include <stack>
#include <queue>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

template <class T>
class MyStack {
    T data[10000];
    int top;

public:
    MyStack() { top = -1; }

    void push(T x) {
        if (top < 9999)
            data[++top] = x;
    }

    T pop() {
        if (top >= 0)
            return data[top--];
        return T();
    }
};

template <class T>
class MyQueue {
    T data[10000];
    int front, rear;

public:
    MyQueue() {
        front = 0;
        rear = -1;
    }

    void enqueue(T x) {
        if (rear < 9999)
            data[++rear] = x;
    }

    T dequeue() {
        if (front <= rear)
            return data[front++];
        return T();
    }
};

int main() {
    const int N = 10000;
    const int R = 100;

    volatile long long result = 0;

    cout << "===== DATA STRUCTURE PERFORMANCE =====\n";
    cout << "Operations: " << N * R << endl;

    // Custom Stack
    auto start = steady_clock::now();

    for (int j = 0; j < R; j++) {
        MyStack<int> s;
        for (int i = 0; i < N; i++)
            s.push(i);
        for (int i = 0; i < N; i++)
            result += s.pop();
    }

    auto end = steady_clock::now();
    double cs = duration<double, milli>(end - start).count();

    // STL Stack
    start = steady_clock::now();

    for (int j = 0; j < R; j++) {
        stack<int> s;
        for (int i = 0; i < N; i++)
            s.push(i);
        for (int i = 0; i < N; i++) {
            result += s.top();
            s.pop();
        }
    }

    end = steady_clock::now();
    double ss = duration<double, milli>(end - start).count();

    // Custom Queue
    start = steady_clock::now();

    for (int j = 0; j < R; j++) {
        MyQueue<int> q;
        for (int i = 0; i < N; i++)
            q.enqueue(i);
        for (int i = 0; i < N; i++)
            result += q.dequeue();
    }

    end = steady_clock::now();
    double cq = duration<double, milli>(end - start).count();

    // STL Queue
    start = steady_clock::now();

    for (int j = 0; j < R; j++) {
        queue<int> q;
        for (int i = 0; i < N; i++)
            q.push(i);
        for (int i = 0; i < N; i++) {
            result += q.front();
            q.pop();
        }
    }

    end = steady_clock::now();
    double sq = duration<double, milli>(end - start).count();

    cout << fixed << setprecision(3);

    cout << "\nCustom Stack : " << cs << " ms";
    cout << "\nSTL Stack    : " << ss << " ms";
    cout << "\nCustom Queue : " << cq << " ms";
    cout << "\nSTL Queue    : " << sq << " ms";

    cout << "\n\n===== BENCHMARK COMPLETED =====\n";

    return 0;
}
