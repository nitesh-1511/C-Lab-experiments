#include <iostream>
#include <cassert>
using namespace std;

class Matrix {
    int a[2][2];

public:
    Matrix(int x=0, int y=0, int z=0, int w=0) {
        a[0][0]=x;
        a[0][1]=y;
        a[1][0]=z;
        a[1][1]=w;
    }

    // Addition
    Matrix operator+(Matrix m) {
        Matrix r;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                r.a[i][j]=a[i][j]+m.a[i][j];
        return r;
    }

    // Multiplication
    Matrix operator*(Matrix m) {
        Matrix r;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++) {
                r.a[i][j]=0;
                for(int k=0;k<2;k++)
                    r.a[i][j]+=a[i][k]*m.a[k][j];
            }
        return r;
    }

    // Array indexing
    int* operator[](int i) {
        return a[i];
    }

    // Display operator
    friend ostream& operator<<(ostream &out, Matrix &m) {
        for(int i=0;i<2;i++) {
            for(int j=0;j<2;j++)
                out<<m.a[i][j]<<" ";
            out<<endl;
        }
        return out;
    }
};

int main() {
    Matrix M1(9,8,4,5);
    Matrix M2(3,6,2,1);

    Matrix add=M1+M2;
    Matrix mul=M1*M2;

    cout<<"First Matrix:"<<endl<<M1;
    cout<<"Second Matrix:"<<endl<<M2;

    cout<<"Addition Result:"<<endl<<add;
    cout<<"Multiplication Result:"<<endl<<mul;

    assert(add[0][0]==3);
    assert(add[1][1]==9);
    assert(mul[0][0]==11);
    assert(mul[1][1]==28);

    cout<<"All Tests Passed!"<<endl;

    return 0;
}