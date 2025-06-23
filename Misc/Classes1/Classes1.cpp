// Classes1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

}; //object realted to class


void CRectangle::set_values(int a, int b)
{
	x = a;
	y = b;
}

int main()
{
	CRectangle rect; //creates an object with the name rect
	rect.set_values(3, 4);
	cout << "area: " << rect.area();
	return 0;

}

