#include <GL/glut.h>
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(3, 3);
    Matrix<int> b(3,3);
    a.set(0,0,2);
    a.set(0,2,1);
    a.set(1,0,3);
    a.set(2,0,5);
    a.set(2,1,1);
    a.set(2,2,1);
    b.set(0,0,1);
    b.set(0,2,1);
    b.set(1,0,1);
    b.set(1,1,2);
    b.set(2,0,1);
    b.set(2,1,1);
    a.print();
    cout<<endl;
    b.print();
    cout<<endl;
    /*Matrix<int> c=a*b;
    cout<<endl;
    c.print();
    cout<<endl;
    c=c.transposed();
    cout<<endl;
    c.print();*/
    a=a+a;
    a.print();
    cout<<endl;
    Matrix<int> c=a+a;
    c.print();
    //a.print();
    /*cout<<endl;
    Matrix<int> c=b+a;
    c.print();*/
    //b.print();


    return EXIT_SUCCESS;
}
