# Overview
Classes are a user-defined data type that group members variables and functions in the same way as a struct might, however, they offer much more control over the accessibility of its members by other datatypes.

This directory will go over how classes work.

# Classes
Classes encapsulate data into three access specifications: "private", "public" and "protected". Each of these specifications offer a degree of control over what has access to the class's members.

## "private"
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

## "public"

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
We have accessors that grab member variables, mutators that change the member variables, pretty easy to understand. Our first bit of new knowledge is the contructor.

## Constructors

When you initialize a variable like...
```cpp
int x = 8;
```
The compiler will already know how to contruct that variable, same goes for any native datatype.

However, the compiler will need instructions on how to initialize any sort of user-defined data type. This is the job of the constructor.

```cpp
Point() {x = y = 0;}
Point() {this -> x = 0; this -> y = 0;}
Point():x(0), y(0){}
```

What we have above are two examples of how to use constructor methods. All three will allow initialization with 0, 1 or 2 arguments. The first and second versions use a "constructor body assignment" and are relatively easy to understand (the "this" operator will be explored in a future section but in essense it works the same as the first version). But, the third version introduces some new concepts and is indeed the best practice for creating constructor methods. Let's explore this method.

### Initializer Lists vs. Constructor Body Assignments

When using a constructor body assignment, the compiler default initializes the variables, then reassigns the variable to the value you provide. On the other hand, using an initializer list will make it so that the variable will be initialized immediatly into the value you specify. This saves some steps which may be miniscule for smaller programs but for larger, more complex programs these extra steps can easily add up.

More importantly, initializer lists are REQUIRED for base classes and reference members...
```cpp
class Example
{
    int& ref;

    public:
        Example(int& r) : ref(f) {}
};
```
If your class contrains a reference member ("ref" in the above code), then there is no "default" initialization... you must create your own initialization. Trying to use a constructor body assignment will make the compiler look for a default initialization when there is nothing in the address for "ref"... its a case of putting the cart before the horse.

```cpp
class Animal {
public:
    Animal(std::string name) {
        std::cout << "Animal: " << name << std::endl;
    }
};

class Dog : public Animal 
{
    public:
        Dog() : Animal("Dog") 
        {
            std::cout << "Dog created\n";
        }
};

```
Here is an example of an initializer list being used in a "base class" this involves inheritance which we will not dive into just yet, but keep this in mind.

Additionally, if we want to exercise "const correctness" (which should be wherever we can), we might assign "const" to a private data member. In this case, we would also be required to use an initializer list.

```cpp
class Example
{
    public:
        Example() {a = b = 1;}
    private:
        const int a, b;    
}
```
In the above code, we would get an error. Remember that a constructor body assignment involves initializing the member, then *reassigning* that value. What we really want is to initialize that value right off the bat so that we don't have to deal with reassignment.

```cpp
class Example 
{
    public:
        Example():a(1), b(1){}
    private:
        const int a, b;
}
```

The above code is the correct way to use a constructor that involves const data members.

### "this"
An important concept to introduce is the "this" operator. "this" is what is known as a "self-referential" operator, that is, when "this" is used, we are telling the compiler that we are refering to the object we are working with.

Consider the following accessor method...

```cpp
class Point 
{
    public:
        double getX() const 
        {
            return this->x;  // explicitly using this
        }
        double getY() const
        {
            return this->y;
        }


    private:
        double x, y;
};
```
Here, using "this->" says look at the *this* object's x and y values (Since this is self-referential, we are able to access the private members, since we are telling the object to retrieve its own private members).

### Constructor Overloading and Disambiguation

When creating a class, there may be a need to declare multiple ways to construct the object and resolve ambiguous elements...

```cpp
class Example 
{
    public:
        Example(double a) {this->a = a;}
        Example(double a, double b) {this->b = b;}
    private:
        const int a, b;
}
```

The above code defines two ways to construct the object, the compiler will choose either method depending on how many arguments are passed. Additionally, we use "this ->" to specify which a or b is the data member and which is the argument. 

Since arguemnts take precedence over data members...

```cpp
Example(double a) {a = a;}
```

Doesn't actually work.

Using initializer lists, we can avoid this problem...

```cpp
Example(double a, double b):x(x), y(y){}
```

It is clear to the compiler that x(x) is read as member(arg).

Back to the PointClass.cpp code, after the constructor, We have our operator overloader. However, you may have noticed that the syntax here is a little different.

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
    Point sum(this->x + otherPoint.getx(), this->y + otherPoint.gety());
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