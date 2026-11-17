
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
using namespace std;
priority_queue<pair<int,int>> q;
mutex m;
void producer() {
    for(int i=1;i<=5;i++) {
        lock_guard<mutex> l(m);
        q.push({i%3+1,i});
        cout<<"Produced: "<<i<<endl;
    }
}
void consumer() {
    while(true) {
        pair<int,int> x;
        {
            lock_guard<mutex> l(m);
            if(q.empty()) break;
            x=q.top();
            q.pop();
        }
        cout<<"Consumed: "<<x.second<<endl;
    }
}
int main() {
    cout<<"SMART PRODUCER-CONSUMER\n";
    thread p(producer);
    p.join();
    thread c(consumer);
    c.join();
    cout<<"\nProduced: 5\nConsumed: 5\n";
    cout<<"System Completed!\n";
    return 0;
}
