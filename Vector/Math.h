#ifndef MATH_H
#define MATH_H
struct vec3
{
    float X, Y, Z;
    float Add(vec3& vec);
    float Minus(vec3& vec);
};
struct vec2
{
    float X, Y;
    float Add(vec2& vec);
    float Minus(vec2& vec);
};
#endif // MATH_H