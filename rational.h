#pragma once

// template<typename T>
// class Rational{ //用于计算
// public:
//     Rational(const T& numerator = 0, 
//         const T& denominator = 1);

//     friend Rational operator*(const Rational& lhs, const Rational& rhs)
//     {
//         return Rational<T>(lhs.numerator*rhs.numerator, lhs.denominator * rhs.denominator);
//     }

//     friend Rational operator/(const Rational& lhs, const Rational& rhs)
//     {
//         return Rational<T>(lhs.numerator*rhs.denominator, lhs.denominator * rhs.numerator);
//     }

//     friend Rational operator+(const Rational& lhs, const Rational& rhs)
//     {
//         T t_numerator = lhs.numerator*rhs.denominator +  lhs.denominator * rhs.numerator;
//         T t_denominator = lhs.denominator * rhs.denominator;
//         return Rational<T>(t_numerator, t_denominator);
//     }

//     friend Rational operator-(const Rational& lhs, const Rational& rhs)
//     {
//         rhs.numerator = -rhs.numerator;
//         rhs.denominator = -rhs.denominator;
//         return lhs + rhs;
//     }

//     T getNumerator() { return numerator; }
//     T getDenominator() { return denominator; }

// public:
//     T numerator;
//     T denominator;
// };

// template<typename T>
// Rational<T>::Rational(const T& numerator, const T& denominator)
// {
//     this->numerator = numerator;
//     this->denominator = denominator;
// }


//用于最后的值
class RationalValue{ 
public:
    RationalValue(int i) //默认没有小数部分
    :integer(i), has_fraction(false), fraction(0.0)
    {}

    RationalValue(int i, double fraction)
    :integer(i), fraction(false), has_fraction(true)
    {}

    bool hasFraction() const
    {
        return has_fraction;
    }

    int getInteger() const
    {
        return this->integer;
    }

    double getValue() const 
    {
        return this->integer + this->fraction;
    }

    friend RationalValue operator+(const RationalValue& lhs, const RationalValue& rhs);
    friend RationalValue operator-(const RationalValue& lhs, const RationalValue& rhs);
    friend RationalValue operator*(const RationalValue& lhs, const RationalValue& rhs);
    friend RationalValue operator/(const RationalValue& lhs, const RationalValue& rhs);

private:
    int integer = 0;
    double fraction = 0.0;
    bool has_fraction;
};

RationalValue operator+(const RationalValue& lhs, const RationalValue& rhs);
RationalValue operator-(const RationalValue& lhs, const RationalValue& rhs); 
RationalValue operator*(const RationalValue& lhs, const RationalValue& rhs);
RationalValue operator/(const RationalValue& lhs, const RationalValue& rhs);

