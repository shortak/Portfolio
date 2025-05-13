#include <iostream>

//Enum classes are scoped, so the enumerators are not visible osside the class
//Enum classes are strongly typed, so the enumerators are not implicitly convertible to any type other than their underlying type
enum class days {SUN, MON, TUE, WED, THU, FRI, SAT}; //Declare a enum class for the days of the week

inline days operator++(days d)
{
    return static_cast<days>((static_cast<int>(d) + 1) % 7); //Increment the enum class by one, wrapping around to zero
}

// NEED TO DECLARE USING NAMESPACE HERE FOR THE OPERATOR OVERLOAD FOR "ostream data type"
using namespace std;

ostream& operator<<(ostream& out, days d)
{
    switch(d)
    {
        case days::SUN: out << "Sunday"; break;
        case days::MON: out << "Monday"; break;
        case days::TUE: out << "Tuesday"; break;
        case days::WED: out << "Wednesday"; break;
        case days::THU: out << "Thursday"; break;
        case days::FRI: out << "Friday"; break;
        case days::SAT: out << "Saturday"; break;
    }
    return out;
}

int main()
{
    

    days d = days::MON, e;

    /* OR */

    /* 
    using days::MON;        //Use this to avoid the scope resolution operator
    days d = MON, e;
    */

    e = ++d; //Increment the enum day
    cout << d << '\t' << e << endl; //Print the day
}
