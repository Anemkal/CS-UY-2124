/*
 Anemka Lydia Legbara
  rec07_start.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational {
    int numerator;
    int denominator;
    void normalize() {
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if (0 > denominator) {
            numerator = -numerator;
            denominator = -denominator;
        }
    };
public:
    Rational(int numerator = 0, int denominator = 1) : numerator(numerator), denominator(denominator) {
        normalize();
    }
    Rational& operator+=(const Rational& rhs) {
        numerator = numerator * rhs.denominator + rhs.numerator * denominator;
        denominator = denominator * rhs.denominator;
        normalize();
        return *this;
    }
    Rational& operator++() {
        numerator += denominator;
        return *this;
    }
    Rational operator++(int dummy) {
        Rational original(*this);
        numerator += denominator;
        return original;
    }
    explicit operator bool() const {
        return numerator != 0;
    }
    friend ostream& operator<<(ostream& os, const Rational& rhs) {
        os << rhs.numerator << "/" << rhs.denominator;
        return os;
    }
    friend istream& operator>>(istream& is, Rational& rhs) {
        char slash;
        is >> rhs.numerator >> slash >> rhs.denominator;
        rhs.normalize();
        return is;
    }
    friend bool operator==(const Rational& lhs, const Rational& rhs) {
        return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
    }
    friend bool operator<(const Rational& lhs, const Rational& rhs);

};

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result += rhs;
    return result;
}
bool operator!=(const Rational& rhs, const Rational& lhs) {
    return !(lhs == rhs);
}
bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
};
bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs ;
};
bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs > rhs || lhs == rhs ;
}

Rational& operator--(Rational& lhs) {
    lhs += -1;
    return lhs;
}

Rational operator--(Rational& lhs, int dummy) {
    Rational temp(lhs);
    lhs += -1;
    return temp;
}
// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement += as a member
    cout << "a = " << a << endl;

    // Implement + as non-member, but NOT as a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    //
    // PLEASE CHECK OUT NOW
    //

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why SHOULDN'T it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
} // main

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
} // greatestCommonDivisor
