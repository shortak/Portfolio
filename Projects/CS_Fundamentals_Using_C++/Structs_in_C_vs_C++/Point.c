#include <stdio.h>

struct Point 
{

    int x;
    int y;

};

void move(struct Point* p)
{
    p -> x += 1;
    p -> y += 1;
}

int main()
{
    struct Point p = {1, 2};
    move(&p);

    printf("Point coordinates: (%d, %d)\n", p.x, p.y);

    return 0;
}