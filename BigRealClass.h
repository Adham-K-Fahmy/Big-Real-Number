#ifndef BIGREAL_BIGREALCLASS_H
#define BIGREAL_BIGREALCLASS_H

#include <iostream>
#include <deque>
#include <regex>
#include <bits/stdc++.h>

using namespace std;

class BigDecimalInt {
private:
    string number;
    char signNumber;

    bool checkValidInput(string input);

public:
    bool operator<(const BigDecimalInt &anotherDec);

    bool operator>(const BigDecimalInt &anotherDec);

    bool operator==(const BigDecimalInt anotherDec);

    BigDecimalInt &operator=(BigDecimalInt anotherDec);

    BigDecimalInt operator+(BigDecimalInt number2);

    BigDecimalInt operator-(BigDecimalInt anotherDec);

    friend ostream &operator<<(ostream &out, BigDecimalInt num);

    int size();

    int sign();

    void setNumber(string num);

    string getNumber()  {
        return number;
    }

    BigDecimalInt() {
    }

    BigDecimalInt(int num) {
        string bigNum = "";
        while (num) {
            bigNum += (num % 10) + '0';
            num /= 10;
        }
        reverse(bigNum.begin(), bigNum.end());
        setNumber(bigNum);
    }

    BigDecimalInt(string num) {
        setNumber(num);
    }

};

class BigReal {
private:
    BigDecimalInt number = BigDecimalInt("0"), floatNumber = BigDecimalInt("0");

public:
    BigReal(double realNumber1 = 0.0);

    BigReal(string realNumber);

    BigReal(const BigDecimalInt &bigInteger);

    BigReal(const BigReal &other); // Copy constructor
    BigReal(BigReal &&other); // Move constructor
    void operator=(BigReal &other); // Assignment operator
    void operator=(BigReal &&other); // Move assignment
    BigReal operator+(const BigReal &other);

    BigReal operator-(BigReal other);

    bool operator<(const BigReal &anotherReal);

    bool operator>(BigReal anotherReal);

    bool operator==(BigReal anotherReal);

    int size();

    int sign();

    friend ostream &operator<<(ostream &out, BigReal num);

    friend istream &operator>>(istream &out, BigReal &num);

    void removeZeros();
};


#endif
