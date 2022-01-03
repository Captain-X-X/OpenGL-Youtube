#include "Math.h"
/* Vector 3 Maths */
float vec3::Add(vec3& vec)
{
    return vec.X + vec.Y + vec.Z;
}
float vec3::Minus(vec3& vec)
{
    return vec.X - vec.Y - vec.Z;
}

/* Vector 2 Maths */
float vec2::Add(vec2& vec)
{
    return vec.X + vec.Y;
}
float vec2::Minus(vec2& vec)
{
    return vec.X - vec.Y;
}
