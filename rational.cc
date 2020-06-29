#include "rational.h"
#include <cassert>
using namespace std;
// RationalValue::RationalValue(const Rational<int>& r)
// {
//     int n = r.getNumerator();
//     int d = r.getDenominator();

//     if(n % d == 0)
//     {
//         this->integer = n / d;
//         this->has_fraction = false;
//         this->fraction = 0.0;
//     }
//     else
//     {
//         this->integer = n / d;
//         this->fraction = ((n + 0.0) / d) - integer;
//         assert(this->fraction < 1.0);
//         this->has_fraction = true;
//     }
    
// }

// RationalValue::RationalValue(const Rational<double>& r)
// {
//     double n = r.getNumerator();
//     double d = r.getDenominator();
//     this->has_fraction = true;
//     this->integer = static_cast<int>(n / d);
//     this->fraction = (n / d) - integer;
//     assert(this->fraction < 1.0);
// }


RationalValue operator+(const RationalValue& lhs, const RationalValue& rhs)
{
    int sum_i = lhs.integer + rhs.integer;
    double sum_fraction = lhs.fraction + rhs.fraction;
    if(lhs.has_fraction || rhs.has_fraction)
    {
        return RationalValue(sum_i, sum_fraction);
    }
    else
    {
        if(sum_fraction >= 1)
        {
            sum_i += 1;
            sum_fraction -= 1;
        }
        return RationalValue(sum_i);
    }  
}

RationalValue operator-(const RationalValue& lhs, const RationalValue& rhs)
{
    if(lhs.has_fraction || rhs.has_fraction)
    {
        double result = lhs.getValue() - rhs.getValue();
        return RationalValue(static_cast<int>(result), result - static_cast<int>(result));
    }
    else
    {
        return RationalValue(lhs.integer - rhs.integer);
    }
}
RationalValue operator*(const RationalValue& lhs, const RationalValue& rhs)
{
    if(lhs.has_fraction || rhs.has_fraction)
    {
        double result = lhs.getValue() * rhs.getValue();
        return RationalValue(static_cast<int>(result), result - static_cast<int>(result));
    }
    else
    {
        return RationalValue(lhs.integer * rhs.integer);
    }
}
RationalValue operator/(const RationalValue& lhs, const RationalValue& rhs)
{
    if(lhs.has_fraction || rhs.has_fraction)
    {
        double result = lhs.getValue() / rhs.getValue();
        return RationalValue(static_cast<int>(result), result - static_cast<int>(result));
    }
    else
    {
        if(lhs.integer % rhs.integer == 0)
        {
            return RationalValue(lhs.integer / rhs.integer);
        }
        else
        {
            double result = lhs.integer / rhs.integer;
            return RationalValue(static_cast<int>(result), result - static_cast<int>(result));
        }
    }
}

std::ostream& operator<<(std::ostream& stream, const RationalValue& v)
{
    if(v.hasFraction())
    {
        stream << (v.getValue());
    }
    else
    {
        stream << v.getInteger();
    }
    return stream;
}
