# Overview
Classes are a user-defined data type that group members variables and functions in the same way as a struct might, however, they offer much more control over the accessibility of its members by other datatypes.

This directory will go over how classes work.

# Classes
Classes encapsulate data into three access specifications: "private", "public" and "protected". Each of these specifications offer a degree of control over what has access to the class's members.

## Private
The "private" specification is where you would store the member variables and functions that will only see use within this class (helper functions)

In essense, anything in the private specicification will act as a black box where other classes will not be able to see any of the variables or functions. (similarly to the engine bay of a car, users will not have the ability to directly interface with the components in the engine bay).

The private specification should not house any members or function that a user may need in order to work with the class (running with the car analogy, the user does not need to know how the engine works in order to operate a car).

For example, in the PointClass.cpp file, we have

```cpp
class Point
{
    // Member Variables
    private:
        double x, y;
};
```
In the above code we define the Point type as one with a specific x and y variable. Because this is unique to the class and will not be changed by anything unless we specifically call a mutator function, we leave it in the private specification. 

## Public

The "public" specification, on the other hand, holds all of the information that is available to the user and other classes. This specification will hold things like your accessors and mutators (getters and setters), constructors and deconstructors, operator overloads and public methods (or member functions) that define what the object can do.

For example, in our PointClass.cpp file...

```cpp
class Point
{
    public:
        // Accessors (getter)
        double getx() const {return x;} 
        double gety() const {return y;}

        // Mutator (setter)
        void setx(double v) {x = v;} 
        void sety(double v) {y = v;}

        // Constructor
        Point(double a, double b) { x = a; y = b;};

        // Operator overload
        Point operator+ ( const Point& otherPoint)
        {
            Point sum( this -> x + otherPoint.getx(), this -> y + otherPoint.gety());
            return sum;
        }

    private:
        double x, y;
};
```
We have accessors that grab member variables, mutators that change the member variables and contructor that defines how the object should be initialized. We also have our operator overloader here, however, you may have noticed that the syntax here is a little different.

### "this"
An important concept to introduce is the "this" operator. "this" is what is known as a "self-referential" operator, that is, when "this" is used, we are telling the compiler that we are refering to the object we are working with.

Consider the following operator overload...

```cpp
Point operator+ ( const Point& otherPoint)
{
    Point sum(this -> x + otherPoint.getx(), this -> y + otherPoint.gety());
    return sum;
}
```
Here, using "this ->" says look at the *this* object's x and y values (Since this is self-referential, we are able to access the private members, since we are telling the object to retrieve its own private members).

### Operator Overloads in Classes
If you were tasked with making an operator overload for the "+" operator to work with two points, you may have had something like this in mind...

```cpp
Point operator+ ( const Point& p1, const Point& p2)
{
    Point sum(p1.getx() + p2.getx(), p1.getx() + p2.gety());
    return sum;
}
```

Although this works as a nonmember function, when used as a method, the left side of the operator will always be the object you are using the operator with...

```cpp

// Take the current object and perform the operation with the 2nd point
Point operator+ ( const Point& otherPoint)
{
    Point sum(this -> x + otherPoint.getx(), this -> y + otherPoint.gety());
    return sum;
}

/*--- VS ---*/

// Take p1 and perform the operation with p2
Point operator+ (const Point& p1, const Point& p2)
{
    Point sum(p1.getx() + p2.getx(), p1.gety() + p2.gety())
    return sum;
}
```

Both methods are valid, it depends on the programmer to find the best way to proceed.