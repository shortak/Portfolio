#include <iostream>

class Point
{
    public:
        double getx() {return x;}
        void setx(double v) {x = v;}
    
    private:
        double x, y;
};

Point operator+ (point& p1, point& p2)
{
    point sum = {p1.x + p2.x, p1.y + p2.y};
    return sum;
}

ostream& operator << (ostream& out, const point& p)
{
    out << "(" << p.x << ", " << p.y << " )";
    return out;
}

int main()
{
    return 0;
}