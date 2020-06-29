#pragma once
#include <iostream>

//用于最后的值
class RationalValue{ 
public:
    RationalValue(int i) //默认没有小数部分
    :integer(i), has_fraction(false), fraction(0.0)
    {}

    RationalValue(int i, double fraction)
    :integer(i), fraction(fraction), has_fraction(true)
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
    // friend std::ostream& operator<<(const ostream& stream, const RationalValue& v);
private:
    int integer = 0;
    double fraction = 0.0;
    bool has_fraction;
};

RationalValue operator+(const RationalValue& lhs, const RationalValue& rhs);
RationalValue operator-(const RationalValue& lhs, const RationalValue& rhs); 
RationalValue operator*(const RationalValue& lhs, const RationalValue& rhs);
RationalValue operator/(const RationalValue& lhs, const RationalValue& rhs);
std::ostream& operator<<(std::ostream& stream, const RationalValue& v);


