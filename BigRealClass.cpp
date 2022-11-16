#include "BigRealClass.h"

// regex function that checks the validation of the input.
bool BigDecimalInt::checkValidInput(string input) {
    regex validInput("[-+]?[0-9]+");
    return regex_match(input, validInput);
}

// constructor that takes a string as an input.
void BigDecimalInt::setNumber(string num) {
    bool validNumber = checkValidInput(num);
    if (validNumber) {
        number = num;
        if (number[0] == '+') {
            number.erase(0, 1);
            signNumber = '+';
        } else if (number[0] == '-') {
            number.erase(0, 1);
            signNumber = '-';
        } else {
            signNumber = '+';
        }
    } else {
        cout << "Invalid" << "\n";
        exit(1);
    }
}

// operator < overloading function.
bool BigDecimalInt::operator<(const BigDecimalInt &anotherDec) {
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2) {
        comp1 += '0';
        len1++;
    }
    while (len2 < len1) {
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if (signNumber == '-' && anotherDec.signNumber == '+') {
        return true;
    } else if (signNumber == '+' && anotherDec.signNumber == '-') {
        return false;
    } else if (signNumber == '+' && anotherDec.signNumber == '+') {
        return comp1 < comp2;
    } else {
        return comp1 > comp2;
    }
}

// operator > overloading function.
bool BigDecimalInt::operator>(const BigDecimalInt &anotherDec) {
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2) {
        comp1 += '0';
        len1++;
    }
    while (len2 < len1) {
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if (signNumber == '-' && anotherDec.signNumber == '+') {
        return false;
    } else if (signNumber == '+' && anotherDec.signNumber == '-') {
        return true;
    } else if (signNumber == '+' && anotherDec.signNumber == '+') {
        return comp1 > comp2;
    } else {
        return comp1 < comp2;
    }
}

// operator == overloading function.
bool BigDecimalInt::operator==(const BigDecimalInt anotherDec) {
    if (signNumber == anotherDec.signNumber && number == anotherDec.number) {
        return true;

    } else {
        return false;
    }
}

// operator = overloading function.
BigDecimalInt &BigDecimalInt::operator=(BigDecimalInt anotherDec) {
    signNumber = anotherDec.signNumber;
    number = anotherDec.number;
    return *this;
}

//addition implementation.
string addition(string num1, string num2) {
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
    int carry = 0;
    while (it1 != num1.rend()) {
        int twoDigitsSum;
        carry = 0;
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
        if (twoDigitsSum >= 10) {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
        it1++;
        it2++;
    }
    if (carry) {
        res = char((carry) + '0') + res;
    }
    return res;
}

//subtraction implementation
string subtraction(string num1, string num2) {
    deque<long long> d;
    string res;

    for (long long i = num1.length() - 1; i >= 0; i--) {
        if (num1[i] < num2[i]) {
            num1[i] = char(((num1[i] - '0') + 10) + '0');
            num1[i - 1] = char(((num1[i - 1] - '0') - 1) + '0');
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        } else {
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
    }

    for (auto i: d) {
        res += to_string(i);
    }
    return res;
}

// // operator + overloading function.
BigDecimalInt BigDecimalInt::operator+(BigDecimalInt number2) {
    BigDecimalInt result;
    char signNumber1 = signNumber, signNumber2 = number2.signNumber;
    string num1 = number, num2 = number2.number;
    BigDecimalInt number1 = *this;

    while (num1.length() < num2.length()) {
        num1 = '0' + num1;
    }
    while (num2.length() < num1.length()) {
        num2 = '0' + num2;
    }

    if (signNumber1 == signNumber2) {
        result.signNumber = signNumber1;
        result.number = addition(num1, num2);

    } else {

        if (number1.signNumber == '-') {
            number1.signNumber = '+';
            result = (number2 - number1);
        } else {
            number2.signNumber = '+';
            result = (number1 - number2);
        }
    }
    return result;
}

// operator - overloading function.
BigDecimalInt BigDecimalInt::operator-(BigDecimalInt anotherDec) {
    BigDecimalInt obj;
    deque<long long> d;
    string strmin = "", res = "";
    string num1 = number, num2 = anotherDec.number;
    char sign1 = signNumber, sign2 = anotherDec.signNumber;

    if (number.length() > anotherDec.number.length()) {
        for (long long i = 0; i < number.length() - anotherDec.number.length(); i++) {
            strmin += '0';
        }
        strmin += anotherDec.number;
        num2 = strmin;
    } else if (number.length() < anotherDec.number.length()) {
        for (long long i = 0; i < anotherDec.number.length() - number.length(); i++) {
            strmin += '0';
        }
        strmin += number;
        num1 = strmin;
    }

    bool ok = false, is_determined = false;
    if (num1 < num2) {
        swap(num1, num2);
        swap(sign1, sign2);
        ok = true;
    }

    if (sign1 == sign2) {
        res = subtraction(num1, num2);

        if (sign1 == '-')ok = !ok;
    } else {
        res = addition(num1, num2);
        if (signNumber == '-') {
            obj.signNumber = '-';
            is_determined = true;
        } else {
            obj.signNumber = '+';
            is_determined = true;
        }

    }
    if (res.empty()) res = "0";
    if (!is_determined && (ok)) {
        obj.signNumber = '-';
    } else if (!is_determined) {
        obj.signNumber = '+';
    }

    obj.number = res;
    return obj;
}

// function to return the size of number.
int BigDecimalInt::size() {
    return number.size();
}

// function returns the sign.
int BigDecimalInt::sign() {
    if (signNumber == '+') {
        return 1;
    } else {
        return 0;
    }
}

// operator << overloading function.
ostream &operator<<(ostream &out, BigDecimalInt num) {
    if (num.signNumber == '+') {
        out << num.number;
    } else {
        out << num.signNumber << num.number;
    }
    return out;
}

BigReal::BigReal(double doubleNumber) {
    stringstream tempNum;
    tempNum << setprecision(numeric_limits<double>::digits10 + 1) << doubleNumber;
    string realNumber = tempNum.str();
    int pointIndex;
    for (int i = 0; i < realNumber.length(); ++i) {
        pointIndex = i;
        if (realNumber[i] == '.') {
            break;
        }
    }
    string num, fractionalNum;
    num = realNumber.substr(0, pointIndex);
    fractionalNum = realNumber.substr(pointIndex + 1, realNumber.length());
    if (fractionalNum.empty()) {
        fractionalNum = '0';
    }
    if (num.empty()) {
        num = '0';
    }
    if (num == "-") {
        num = "0";
        fractionalNum = "-" + fractionalNum;
    } else if (num[0] == '-') {
        num = num;
        fractionalNum = "-" + fractionalNum;
    }
    number = BigDecimalInt(num);
    floatNumber = BigDecimalInt(fractionalNum);
    this->removeZeros();
}

BigReal::BigReal(string realNumber) {
    int pointIndex;
    for (int i = 0; i < realNumber.length(); ++i) {
        pointIndex = i;
        if (realNumber[i] == '.') {
            break;
        }
    }
    string num, fractionalNum;
    num = realNumber.substr(0, pointIndex);
    fractionalNum = realNumber.substr(pointIndex + 1, realNumber.length());
    if (fractionalNum.empty()) {
        fractionalNum = '0';
    }
    if (num.empty()) {
        num = '0';
    }
    if (num == "-") {
        num = "0";
        fractionalNum = "-" + fractionalNum;
    } else if (num[0] == '-') {
        num = num;
        fractionalNum = "-" + fractionalNum;
    }
    number = BigDecimalInt(num);
    floatNumber = BigDecimalInt(fractionalNum);
    this->removeZeros();
}

BigReal::BigReal(BigDecimalInt bigInteger) {
    number = bigInteger;
    floatNumber = BigDecimalInt("0");
    this->removeZeros();
}

BigReal::BigReal(const BigReal &other) {
    number = other.number;
    floatNumber = other.floatNumber;
    this->removeZeros();
}

BigReal::BigReal(BigReal &&other) {
    this->number = move(other.number);
    this->floatNumber = move(other.floatNumber);
    this->removeZeros();
}

void BigReal::operator=(BigReal &other) {
    number = other.number;
    floatNumber = other.floatNumber;
    this->removeZeros();
}

void BigReal::operator=(BigReal &&other) {
    this->number = move(other.number);
    this->floatNumber = move(other.floatNumber);
    this->removeZeros();
}

BigReal BigReal::operator+(BigReal other) {
    BigReal result, num2 = other;
    if (this->sign() != num2.sign()) {
        if (num2.sign()) {
            num2.number = BigDecimalInt("-" + num2.number.getNumber());
            num2.floatNumber = BigDecimalInt("-" + num2.floatNumber.getNumber());
        } else {
            num2.number = BigDecimalInt(num2.number.getNumber());
            num2.floatNumber = BigDecimalInt(num2.floatNumber.getNumber());
        }
        return *this - num2;
    }
    if (this->floatNumber.size() < num2.floatNumber.size()) {
        swap(this->floatNumber, num2.floatNumber);
    }
    while (num2.floatNumber.size() < this->floatNumber.size()) {
        if (num2.sign()) {
            num2.floatNumber = BigDecimalInt(num2.floatNumber.getNumber() + "0");
        } else {
            num2.floatNumber = BigDecimalInt("-" + num2.floatNumber.getNumber() + "0");
        }
    }
    result.number = this->number + num2.number;
    int size = max(this->floatNumber.size(), num2.floatNumber.size());
    result.floatNumber = this->floatNumber + num2.floatNumber;
    if (result.floatNumber.size() > size) {
        if (result.sign()) {
            result.floatNumber = result.floatNumber.getNumber().substr(1, result.floatNumber.size());
            result.number = result.number + BigDecimalInt(1);
        } else {
            BigDecimalInt temp("-" + result.floatNumber.getNumber().substr(1, result.floatNumber.size()));
            result.floatNumber = temp;
            result.number = result.number - BigDecimalInt(1);
        }
    }
    result.removeZeros();
    return result;
}

BigReal BigReal::operator-(BigReal other) {
    BigReal result, num1, num2;
    num1 = *this;
    if (other.sign()) {
        BigReal temp;
        temp.number = BigDecimalInt("-" + other.number.getNumber());
        temp.floatNumber = BigDecimalInt("-" + other.floatNumber.getNumber());
        num2 = temp;
    } else {
        BigReal temp;
        temp.number = BigDecimalInt(other.number.getNumber());
        temp.floatNumber = BigDecimalInt(other.floatNumber.getNumber());
        num2 = temp;
    }
    if (num1.sign() == num2.sign()) {
        return num1 + num2;
    }
    while (num1.floatNumber.size() > num2.floatNumber.size()) {
        if(num2.sign()){
            num2.floatNumber = BigDecimalInt(num2.floatNumber.getNumber()+"0");
        }
        else{
            num2.floatNumber = BigDecimalInt("-"+num2.floatNumber.getNumber()+"0");
        }
    }
    while (num1.floatNumber.size() < num2.floatNumber.size()) {
        if(num1.sign()){
            num1.floatNumber = BigDecimalInt(num1.floatNumber.getNumber()+"0");
        }
        else{
            num1.floatNumber = BigDecimalInt("-"+num1.floatNumber.getNumber()+"0");
        }
    }
    if (num1.number.getNumber() == "0" && num1.floatNumber.getNumber() == "0") {
        return num2;
    } else if (num2.number.getNumber() == "0" && num2.floatNumber.getNumber() == "0") {
        return num1;
    }
    result.number = num1.number + num2.number;
    result.floatNumber = num1.floatNumber + num2.floatNumber;
    if(result.number.getNumber() == "0"){
        if(result.floatNumber.sign()){
           result.number = BigDecimalInt("0");
        }
        else{
            result.number = BigDecimalInt("-0");
        }
    }
    if (result.floatNumber.sign() != result.number.sign()) {
        if (result.number.sign()) {
            result.number = result.number - BigDecimalInt(1);
            string temp = "1";
            for (int i = 0; i < result.floatNumber.size(); ++i) {
                temp += "0";
            }
            result.floatNumber = BigDecimalInt("-" + result.floatNumber.getNumber()) + BigDecimalInt(temp);
        } else {
            result.number = result.number + BigDecimalInt(1);
            string temp = "1";
            for (int i = 0; i < result.floatNumber.size(); ++i) {
                temp += "0";
            }
            result.floatNumber = BigDecimalInt(result.floatNumber.getNumber()) - BigDecimalInt(temp);
        }
        if(result.floatNumber.sign()){
            result.floatNumber = BigDecimalInt(result.floatNumber.getNumber().substr(1, result.floatNumber.size()));
        }
        else{
            result.floatNumber = BigDecimalInt("-"+result.floatNumber.getNumber().substr(1, result.floatNumber.size()));
        }
    }
    result.removeZeros();
    return result;
}

bool BigReal::operator>(BigReal anotherReal) {
    if (number == anotherReal.number) {
        return (floatNumber > anotherReal.floatNumber);
    } else {
        return (number > anotherReal.number);
    }
}

bool BigReal::operator<(BigReal anotherReal) {
    return !(*this == anotherReal || *this > anotherReal);
}

bool BigReal::operator==(BigReal anotherReal) {
    return (number == anotherReal.number && floatNumber == anotherReal.floatNumber);
}

int BigReal::size() {
    return number.size() + floatNumber.size();
}

int BigReal::sign() {
    return number.sign();
}

ostream &operator<<(ostream &out, BigReal num) {
    BigDecimalInt temp(num.floatNumber);
    if (!num.floatNumber.sign()) {
        temp = BigDecimalInt(num.floatNumber.getNumber().substr(0, num.floatNumber.getNumber().size()));
    }
    cout << num.number << '.' << temp;
    return out;
}

istream &operator>>(istream &in, BigReal &num) {
    string w;
    cin >> w;
    BigReal temp(w);
    num = temp;
    return in;
}

void BigReal::removeZeros() {
    int lastZero = 0, frontZero = floatNumber.size() - 1;
    while (lastZero + 1 < number.getNumber().size() && number.getNumber()[lastZero] == '0') {
        lastZero++;
    }
    while (frontZero > 0 && floatNumber.getNumber()[frontZero] == '0') {
        frontZero--;
    }
    if (number.sign()) {
        number = BigDecimalInt(number.getNumber().substr(lastZero, number.getNumber().size()));
        floatNumber = BigDecimalInt(floatNumber.getNumber().substr(0, frontZero + 1));
    } else {
        number = BigDecimalInt("-" + number.getNumber().substr(lastZero, number.getNumber().size()));
        floatNumber = BigDecimalInt("-" + floatNumber.getNumber().substr(0, frontZero + 1));
    }
}