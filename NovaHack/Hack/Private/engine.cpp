#include "../Public/engine.h"

D3DMATRIX engine::Matrix(vec3 rot, vec3 origin)
{
    float Pitch = rot.x * M_RAD;
    float Yaw = rot.y * M_RAD;
    float Roll = rot.z * M_RAD;

    float SP = sinf(Pitch);
    float CP = cosf(Pitch);
    float SY = sinf(Yaw);
    float CY = cosf(Yaw);
    float SR = sinf(Roll);
    float CR = cosf(Roll);

    D3DMATRIX matrix;
    matrix.m[0][0] = CP * CY;
    matrix.m[0][1] = CP * SY;
    matrix.m[0][2] = SP;
    matrix.m[0][3] = 0.f;

    matrix.m[1][0] = SR * SP * CY - CR * SY;
    matrix.m[1][1] = SR * SP * SY + CR * CY;
    matrix.m[1][2] = -SR * CP;
    matrix.m[1][3] = 0.f;

    matrix.m[2][0] = -(CR * SP * CY + SR * SY);
    matrix.m[2][1] = CY * SR - CR * SP * SY;
    matrix.m[2][2] = CR * CP;
    matrix.m[2][3] = 0.f;

    matrix.m[3][0] = origin.x;
    matrix.m[3][1] = origin.y;
    matrix.m[3][2] = origin.z;
    matrix.m[3][3] = 1.f;

    return matrix;
}

bool engine::WorldToScreen(vec3 WorldLocation, camera LocalCamera, vec2* OutPos)
{
    D3DMATRIX tempMatrix = Matrix(LocalCamera.Rotation);

    vec3 vAxisX, vAxisY, vAxisZ;

    vAxisX = vec3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
    vAxisY = vec3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
    vAxisZ = vec3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

    vec3 vDelta = WorldLocation - LocalCamera.Location;
    vec3 vTransformed = vec3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

    if (vTransformed.z < 1.f)
        vTransformed.z = 1.f;

    float FovAngle = 80.f;

    OutPos->x = engine::ScreenCenter.x + vTransformed.x * (engine::ScreenCenter.x / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
    OutPos->y = engine::ScreenCenter.y - vTransformed.y * (engine::ScreenCenter.x / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

    return true;
}
