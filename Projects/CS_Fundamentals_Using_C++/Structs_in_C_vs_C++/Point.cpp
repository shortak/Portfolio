#include <iostream>

using namespace std;

struct Point 
{
    int x;
    int y;

    void move() {
        x += 1;
        y += 1;
    }
};

int main() 
{
    Point p = {1, 2};   

    p.move();

    cout << "Point coordinates: (" << p.x << ", " << p.y << ")" << endl;

    return 0;
}