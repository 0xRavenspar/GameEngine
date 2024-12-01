class Vec2
{
    public:
    float x=0, y=0;
    Vec2() {}
    Vec2(float xin, float yin)
    : x(xin), y(yin) {}


    Vec2& add(const Vec2& v){
        x+= v.x;
        y+= v.y;
        return *this;
    }

    Vec2& scale(float s){
        x*= s;
        y*= s;
        return *this;
    }

    Vec2 operator + (const Vec2& rhs ){
        return Vec2(x + rhs.x, y+rhs.y);
    }

    Vec2 operator * (const float scale)
    {
        return Vec2(x*scale, y*scale);
    }
    float length(){
        return 0;
    }
};

#include <iostream>
int main(){
    Vec2 v1(100,200);
    Vec2 v2(300,400);
    

    Vec2 v3 = v1 * 3;
    v1.add(v2).scale(5);

    std::cout << v1.x << " " << v1.y << std::endl;
    std::cout << v2.x << " " << v2.y<< std::endl;
    std::cout << v3.x << " " << v3.y<< std::endl;

    return 0;
}