#include <iostream>

using namespace std;

//Enum, unlike enum class, is not scoped, so the enumerators are visible outside the class
enum days {MON, TUE, WED, THU, FRI, SAT, SUN}; //Declare a enum for the days of the week

inline days operator++(days d)
{
    return static_cast<days>((static_cast<int>(d) + 1) % 7); //Increment the enum by one, wrapping around to zero
}

ostream& operator<<(ostream& out, days d)
{
    switch(d)
    {
        case MON: out << "Monday"; break;
        case TUE: out << "Tuesday"; break;
        case WED: out << "Wednesday"; break;
        case THU: out << "Thursday"; break;
        case FRI: out << "Friday"; break;
        case SAT: out << "Saturday"; break;
        case SUN: out << "Sunday"; break;
    }
    return out;
}
int main()
{
    
    days d = MON, e; //Unlike "enum class" we don't need the scope resolution operator

    e = ++d; //Increment the enum day
    cout << d << '\t' << e << endl; //Print the day
}