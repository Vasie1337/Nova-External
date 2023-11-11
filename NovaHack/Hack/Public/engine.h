#pragma once
#include <iostream>
#include <math.h>
#include <d3d9.h>

class engine
{
public:
    typedef __int8 int8;
    typedef __int16 int16;
    typedef __int32 int32;
    typedef __int64 int64;

    typedef unsigned __int8 uint8;
    typedef unsigned __int16 uint16;
    typedef unsigned __int32 uint32;
    typedef unsigned __int64 uint64;

    inline static const float M_PI = 3.1415926535898f;
    inline static const float M_RAD = float(M_PI) / 180.f;

    struct vec2
    {
        vec2() : x(0.f), y(0.f)
        {

        }

        vec2(float _x, float _y) : x(_x), y(_y)
        {

        }

        float x;
        float y;

        vec2 operator+(vec2 v) {
            return vec2(x + v.x, y + v.y);
        }

        float Distance(const vec2& other) const {
            float dx = x - other.x;
            float dy = y - other.y;
            return sqrtf(dx * dx + dy * dy);
        }
    };
    struct vec3 {
        float x;
        float y;
        float z;

        vec3() : x(0.0f), y(0.0f), z(0.0f) {}

        vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

        inline float Dot(vec3 v) {
            return x * v.x + y * v.y + z * v.z;
        }

        inline float Distance(vec3 v) {
            return std::sqrtf(pow(v.x - x, 2.0f) + pow(v.y - y, 2.0f) + pow(v.z - z, 2.0f));
        }

        inline int DistanceInt(vec3 v) {
            return (int)(std::sqrtf(pow(v.x - x, 2.0f) + pow(v.y - y, 2.0f) + pow(v.z - z, 2.0f)));
        }

        inline float Magnitude() {
            return std::sqrtf(x * x + y * y + z * z);
        }

        inline bool operator!=(const vec3& Other) const
        {
            return x != Other.x || y != Other.y || z != Other.z;
        }

        vec3 operator+(vec3 v) {
            return vec3(x + v.x, y + v.y, z + v.z);
        }

        vec3 operator-(vec3 v) {
            return vec3(x - v.x, y - v.y, z - v.z);
        }

        vec3 operator*(float flNum) {
            return vec3(x * flNum, y * flNum, z * flNum);
        }
        vec3& operator*=(float flNum) {
            x *= flNum;
            y *= flNum;
            z *= flNum;
            return *this;
        }

    };
    struct vec4
    {
    public:
        float X;
        float Y;
        float Z;
        float W;

        inline vec4()
            : X(0.0), Y(0.0), Z(0.0), W(0.0)
        {
        }

        inline vec4(decltype(X) Value)
            : X(Value), Y(Value), Z(Value), W(Value)
        {
        }

        inline vec4(decltype(X) x, decltype(Y) y, decltype(Z) z, decltype(W) w)
            : X(x), Y(y), Z(z), W(w)
        {
        }

        inline bool operator==(const vec4& Other) const
        {
            return X == Other.X && Y == Other.Y && Z == Other.Z && W == Other.W;
        }

        inline bool operator!=(const vec4& Other) const
        {
            return X != Other.X || Y != Other.Y || Z != Other.Z || W != Other.W;
        }
    };
    struct camera
    {
        vec3 Location{};
        vec3 Rotation{};
        float FOV{};
    };
    struct drawdata {
        engine::vec2 RootPos2D{};
        engine::vec2 HeadPos2D{};
        engine::vec2 FootPos2D{};

        int WorldDistance{};
        float FovDistance{};

        uintptr_t Mesh{};
    };
    struct aimdata {
        engine::vec2 ClosestAimPos2D{};
        float ClosestFovDistance{};
    };

    inline static vec2 Screen = {
        static_cast<float>(GetSystemMetrics(SM_CXSCREEN)),
        static_cast<float>(GetSystemMetrics(SM_CYSCREEN))
    };
    inline static vec2 ScreenCenter = {
        Screen.x / 2.f,
        Screen.y / 2.f
    };

    static D3DMATRIX Matrix(vec3 rot, vec3 origin = vec3(0, 0, 0));
    static bool WorldToScreen(vec3 WorldLocation, camera LocalCamera, vec2* OutPos);
};