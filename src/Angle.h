#pragma once


/// Kiss radian/degree headaches goodbye.
class Angle
{
public:
    /// Construct an Angle object. No guaranteed size, for performance.
    explicit Angle();
    /// Create an Angle object from a degree value.
    friend Angle degrees(float deg);
    /// Create an Angle object from a radian value.
    friend Angle radians(float rad);

    /// Get the size of this angle in degrees.
    float asDegrees() const;
    /// Get the size of this angle in radians.
    float asRadians() const;

    /// Add two Angle objects.
    Angle operator + (Angle other) const;
    /// Subtract two Angle objects.
    Angle operator - (Angle other) const;
    /// Add an Angle to this Angle.
    Angle & operator += (Angle other);
    /// Subtract an Angle from this Angle.
    Angle & operator -= (Angle other);

private:
    /// Create an Angle object from a radian value.
    explicit Angle(float radians);

    /// The size of this Angle, stored in radians.
    float radians;
};

Angle degrees(float deg);
Angle radians(float rad);
