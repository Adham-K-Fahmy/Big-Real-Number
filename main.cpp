#include "BigRealClass.cpp"

int main() {
    //test 1
    BigReal a(10.55), b("-1.10001"), c(BigDecimalInt("505"));
    //test 2
    cout << a << ' ' <<  b << ' ' << c << endl;
    //test 3
    cout << a+b << endl;
    //test 4
    cout << a+c << endl;
    //test 5
    cout << a-c << endl;
    //test 6
    cout << c-b << endl;
    //test 7
    cout << b-c << endl;
    //test 8
    cin >> a;
    cout << a << endl;
    //test 9
    a = b;
    BigReal d(b);
    c = BigReal("101.9901");
    cout << a << ' ' << b << ' ' << c << endl;
    //test 10
    cout << (a<c) << endl;
    //test 11
    cout << (a>c) << endl;
    //test 12
    cout << (a==c) << endl;
    cout << (a==b) << endl;
    //test 13
    cout << a.size() << endl;
    //test 14
    cout << a.sign() << endl;
}



