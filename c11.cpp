
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Meter { static constexpr double f=1; };
struct Kilometer { static constexpr double f=1000; };
struct Centimeter { static constexpr double f=0.01; };
struct Millimeter { static constexpr double f=0.001; };
struct Mile { static constexpr double f=1609.34; };

template<class U>
class Quantity {
    double value;
public:
    Quantity(double v):value(v){}
    double getValue() const { return value; }
};

template<class T,class F>
Quantity<T> convert(Quantity<F> q) {
    return Quantity<T>(q.getValue()*F::f/T::f);
}

int main() {
    double n;
    vector<double> history;

    cout<<"===== SMART UNIT CONVERTER =====\n";
    cout<<"Enter distance in meters: ";
    cin>>n;

    if(n<0) {
        cout<<"Invalid distance!\n";
        return 0;
    }

    Quantity<Meter> d(n);

    auto km=convert<Kilometer>(d);
    auto cm=convert<Centimeter>(d);
    auto mm=convert<Millimeter>(d);
    auto mi=convert<Mile>(d);

    history.push_back(n);

    cout<<fixed<<setprecision(2);

    cout<<"\n--- CONVERSION RESULTS ---\n";
    cout<<"Meter      : "<<n<<"\n";
    cout<<"Kilometer  : "<<km.getValue()<<"\n";
    cout<<"Centimeter : "<<cm.getValue()<<"\n";
    cout<<"Millimeter : "<<mm.getValue()<<"\n";
    cout<<"Mile       : "<<mi.getValue()<<"\n";

    cout<<"\n--- SMART RECOMMENDATION ---\n";

    if(n>=1000)
        cout<<"Recommended: "<<km.getValue()<<" km\n";
    else if(n>=1)
        cout<<"Recommended: "<<n<<" meters\n";
    else
        cout<<"Recommended: "<<cm.getValue()<<" cm\n";

    cout<<"\n--- DISTANCE CATEGORY ---\n";

    if(n<100)
        cout<<"Short Distance\n";
    else if(n<10000)
        cout<<"Medium Distance\n";
    else
        cout<<"Long Distance\n";

    cout<<"\n--- HISTORY ---\n";
    for(double x:history)
        cout<<x<<" meters\n";

    cout<<"\nConversion Completed Successfully!\n";

    return 0;
}
