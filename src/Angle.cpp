#include "Angle.h"

#include "Util.h"


Angle::Angle() {}

Angle::Angle(float radians) : radians(radians)
{
    while (radians < Pi * -1)
        radians += 2 * Pi;
    while (radians >= Pi)
        radians -= 2 * Pi;
}


Angle degrees(float deg) { return Angle((deg * Pi) / 180); }

Angle radians(float rad) { return Angle(rad); }


float Angle::asDegrees() const { return (radians * 180) / Pi; }

float Angle::asRadians() const { return radians; }


Angle Angle::operator + (Angle other) const
{
    return Angle(radians + other.radians);
}

Angle Angle::operator - (Angle other) const
{
    return Angle(radians - other.radians);
}

Angle & Angle::operator += (Angle other)
{
    radians += other.radians;
    return *this;
}

Angle & Angle::operator -= (Angle other)
{
    radians -= other.radians;
    return *this;
}
