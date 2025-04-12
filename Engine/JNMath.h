#pragma once
#include <cmath>

template <typename Type>
struct Vec2
{
    Type x;
    Type y;
};

template <typename Type>
struct Vec3
{
    Type x;
    Type y;
    Type z;
};

template <typename Type>
Type Fact(Type num)
{
    if (num <= 0)
    {
        return 1;
    }
    else
    {
        return num * Fact(num - 1);
    }
}

template <typename Type>
Type Power(Type a, Type b)
{
    if (b < 0)
    {
        if (a == 0)
            return 0;
        else
            return 1 / (a * Power(a, (-b) - 1));
    }

    if (b == 0)
        return 1;

    if (b == 1)
        return a;

    return a * Power(a, b - 1);
}

template <typename Type>
Type Square(Type a)
{
    return a * a;
}

template <typename Type>
float SquareRoot(Type a)
{
    /*
    if (a <= 0)
        return 0;

    float error = 0.00001;
    float square = a;
    while (square - a / square > error)
    {
        square = (square + a / square) / 2;
    }
    */
    return sqrt(a);
}

template <typename Type>
float GetMagnatuede2D(Vec2<Type> vect)
{
    float mag = (SquareRoot(Square(vect.x) + Square(vect.y)));
    return mag;
}

template <typename Type>
Type GetMagnatuede3D(Vec3<Type> vect)
{
    Type mag = (SquareRoot(Square(vect.x) + Square(vect.y) + Square(vect.z)));
    return mag;
}

template <typename Type>
Vec2<Type> Normalize2D(Vec2<Type> a)
{
    Type mag = GetMagnatuede2D(a);
    Vec2<Type> vect(a.x / mag, a.y / mag);

    return vect;
}

template <typename Type>
Vec3<float> Normalize3D(Vec3<Type> a)
{
    float mag = GetMagnatuede3D(a);
    Vec3<Type> newVect;
    newVect.x = a.x / mag;
    newVect.y = a.y / mag;
    newVect.z = a.z / mag;
    return newVect;
}

template <typename Type>
Vec2<Type> AddVect2D(Vec2<Type> a, Vec2<Type> b)
{
    Vec2<Type> newVect(a.x + b.x, a.y + b.y);
    return newVect;
}

template <typename Type>
Vec2<Type> SubtractVect2D(Vec2<Type> a, Vec2<Type> b)
{
    Vec2<Type> newVect(a.x - b.x, a.y - b.y);
    return newVect;
}

template <typename Type>
Vec2<Type> MultiplyVect2DScalar(Vec2<Type> a, Type b)
{
    Vec2<Type> newVect(a.x * b, a.y * b);
    return newVect;
}

template <typename Type>
Vec2<float> DivideVect2DScalar(Vec2<Type> a, Type b)
{
    Vec2<float> newVect(a.x / b, a.y / b);
    return newVect;
}

template <typename Type>
Vec3<Type> AddVect3D(Vec3<Type> a, Vec3<Type> b)
{
    Vec3<Type> newVect;
    newVect.x = a.x + b.x;
    newVect.y = a.y + b.y;
    newVect.z = a.z + b.z;
    return newVect;
}

template <typename Type>
Vec3<Type> SubtractVect3D(Vec3<Type> a, Vec3<Type> b)
{
    Vec3<Type> newVect;
    newVect.x = a.x - b.x;
    newVect.y = a.y - b.y;
    newVect.z = a.z - b.z;
    return newVect;
}

template <typename Type>
Vec3<Type> MultiplyVect3DScalar(Vec3<Type> a, Type b)
{
    Vec3<Type> newVect;
    newVect.x = a.x * b;
    newVect.y = a.y * b;
    newVect.z = a.z * b;
    return newVect;
}

template <typename Type>
Vec3<float> DivideVect3DScalar(Vec3<Type> a, Type b)
{
    Vec3<float> newVect(a.x / b, a.y / b, a.z / b);
    return newVect;
}
/*
float DegtoRad(int deg)
{
    return deg * 3.14159f / 180;
}

float RadtoDeg(float rad)
{
    return rad * 180 / 3.14159f;
}

float Sin(int deg)
{
    deg %= 360;
    float rad = DegtoRad(deg);
    float sin = 0;

    for (int i = 0; i < 7; i++)
    {
        sin += Power(-1, i) * Power(rad, 2.0f * i + 1.0f) / Fact(2 * i + 1.0f);
    }
    return sin;
}

float Cos(int deg)
{
    deg %= 360;
    float rad = DegtoRad(deg);
    float cos = 0;

    for (int i = 0; i < 7; i++)
    {
        cos += Power(-1, i) * Power(rad, 2.0f * i) / Fact(2 * i);
    }
    return cos;
}
*/

template <typename Type>
float DotProduct2D(Vec2<Type>a, Vec2<Type> b)
{
    return (float)((a.x * b.x) + (a.y * b.y));
}

template <typename Type>
float CrossProduct2D(Vec2<Type>a, Vec2<Type> b)
{
    return (float)(a.x * b.y - b.x * a.y);
}

template <typename Type>
float DotProduct3D(Vec3<Type>a, Vec3<Type> b)
{
    return (float)((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

template <typename Type>
Vec3<Type> CrossProduct3D(Vec3<Type>a, Vec3<Type> b)
{
    Vec3<Type> crossProd;
    crossProd.x = a.y * b.z - a.z * b.y;
    crossProd.y = -1 * (a.x * b.z - a.z * b.x);
    crossProd.z = a.x * b.y - a.y * b.x;

    return crossProd;
}

template <typename Type>
Vec2<Type> Project2D(Vec2<Type> v, Vec2<Type> a)
{
    return MultiplyVect2DScalar<Type>(Normalize2D<Type>(a), DotProduct2D<Type>(v, a) / GetMagnatuede2D<Type>(a));
}

template <typename Type>
Vec2<Type> Bounce2D(Vec2<Type> v, Vec2<Type> n)
{
    return AddVect2D<Type>(v, MultiplyVect2DScalar<Type>(Project2D<Type>(v, n), -2));
}