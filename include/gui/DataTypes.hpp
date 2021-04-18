#pragma once
struct Vector3f
{
	float x; 
	float y; 
	float z; 
    Vector3f operator+(const Vector3f& a) const
    {
        return {a.x+x, a.y+y, a.z+z};
    }
    bool operator>=(const Vector3f& a) const {
        return x>=a.x && y>=a.y && z>=a.z;
    }
    bool operator<=(const Vector3f& a) const {
        return x<=a.x && y<=a.y && z<=a.z;
    }
};
struct Vector2f
{
    float x;
    float y;
    
    Vector2f operator+(const Vector2f& a) const
    {
        return {a.x+x, a.y+y};
    }
    Vector2f operator-(const Vector2f& a) const
    {
        return {x-a.x, y-a.y};
    }
    bool operator>=(const Vector2f& a) const {
        return x>=a.x && y>=a.y;
    }
    bool operator<=(const Vector2f& a) const {
        return x<=a.x && y<=a.y;
    }
};
#define _asV2F(v) (Vector2f{v.x,v.y})
#define _asV3F(v,z) (Vector3f{v.x,v.y,z})