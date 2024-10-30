#pragma once

#include <cmath>

// Normalize a Vector
Vector2 normalize(const Vector2& vec)
{
     // Length between x-y components
     float magnitude = std::hypotf(vec.x, vec.y);

     // Avoid dividing by 0
     if (magnitude == 0.0f)
          return vec;

     return { vec.x / magnitude, vec.y / magnitude };
}

// Vector2 addition
Vector2 operator+(const Vector2& v, const Vector2& u)
{
     return { v.x + u.x, v.y + u.y };
}

// Vector2 addition assignment
Vector2& operator+=(Vector2& v, const Vector2& u) {
     v.x += u.x;
     v.y += u.y;
     return v; // Return the modified object itself
}

// Vector2 subtraction
Vector2 operator-(const Vector2& v, const Vector2& u)
{
     return { v.x - u.x, v.y - u.y };
}

// Vector2 subtraction assignment
Vector2& operator-=(Vector2& v, const Vector2& u) {
     v.x -= u.x;
     v.y -= u.y;
     return v;
}

// Vector2 scalar multiplication
Vector2 operator*(const Vector2& v, float s)
{
     return { v.x * s, v.y * s };
}

Vector2 operator*=(Vector2& v, float s)
{
     v.x *= s;
     v.y *= s;
     return v;
}

// Vector2 scalar division
Vector2 operator/(const Vector2& v, float s)
{
     // Avoid division by 0
     if (s == 0.0f)
          return v;
     return { v.x / s, v.y / s };
}
Vector2 operator/=(Vector2& v, const float s)
{
     if (s == 0.0f)return v;

     v.x /= s;
     v.y /= s;

     return v;
      
}

// Vector2 dot product
float dot(const Vector2& v, const Vector2& u)
{
     return v.x * u.x + v.y * u.y;
}

// Vector2 cross product (returns a scalar)
float cross(const Vector2& v, const Vector2& u)
{
     return v.x * u.y - v.y * u.x;
}

// Vector2 length
float magnitude(const Vector2& v)
{
     return std::hypotf(v.x, v.y);
}

// Vector2 distance between two points
float distance(const Vector2& v, const Vector2& u)
{
     return std::hypotf(u.x - v.x, u.y - v.y);
}



#include <cmath>

Vector2 limit(const Vector2& v, const float max)
{
     //  the magnitude (length) of the vector
     float mag = std::hypot(v.x, v.y);

     // If the magnitude exceeds the limit, scale the vector down
     if (mag > max)
     {
          float scale = max / mag;
          return { v.x * scale, v.y * scale };
     }
     // If within the limit, return the original vector
     return v;
}


