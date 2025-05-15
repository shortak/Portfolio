#include <iostream>

using namespace std;

class Point
{
    public:
        // Accessors
        double getx() const {return x;} 
        double gety() const {return y;}

        // Mutator
        void setx(double v) {x = v;} 
        void sety(double v) {y = v;}

        // Constructor
        Point(double a, double b) { x = a; y = b;};
        Point() {x = y = 0;}

        // Operator overload
        Point operator+ ( const Point& otherPoint)
        {
            Point sum(x + otherPoint.getx(), y + otherPoint.gety());
            return sum;
        }

    private:
        double x, y;
};



ostream& operator << (ostream& out, const Point& p)
{
    out << "(" << p.getx() << ", " << p.gety() << " )";
    return out;
}

int main()
{
    return 0;
}