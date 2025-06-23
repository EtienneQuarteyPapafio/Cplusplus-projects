// Classes2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Classes are like structs however they can store both data and functions
//Data members are daata variables
//Member functions are functions used to manipulate these variables

#include <iostream>
using namespace std;

class CRectangle //class keyword, name of class
{
	int x, y; //member 1 and 2 variables private by default
public:
	void set_values(int, int);//functions
	int area()
	{
		return (x * y);
	}

}; //object related to class


//class defined

void CRectangle::set_values(int a, int b) //scope operator used to define member of class
{
	x = a;
	y = b;
}

//external declaration of function

int main()
{
	CRectangle rect, rectb; //creates an object with the name rect
	//can use multiple objects with different values without having to re-declare

	rect.set_values(3, 4);
	rectb.set_values(5, 7);
	cout << "area: " << rect.area() << endl;
	cout << "area 2: " << rectb.area() << endl;
	return 0;

}