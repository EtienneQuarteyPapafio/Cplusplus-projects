// Classes2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Classes are like structs however they can store both data and functions
//Data members are daata variables
//Member functions are functions used to manipulate these variables

#include <iostream>
using namespace std;

//constructor example

class CRectangle //class keyword, name of class
{
	int *width, *height; //sets as pointers for dynamic memory allocation
public:
	CRectangle (int, int);//functions, constructor
	~CRectangle(); //Deconstructor
	int area()
	{
		return (*width * *height);
	}

}; //object related to class


//class defined

CRectangle::CRectangle(int a, int b) //scope operator used to define member of class
{
	width = new int;
	height = new int;
	*width = a;
	*height = b;
};

//declaration of function and constructor

CRectangle::~CRectangle()
{
	delete width;
	delete height;
}

//desconstructor to free dynamic memory

int main()
{
	CRectangle rect(3, 4), rectb(5, 6); //creates an object with the name rect and passes values 
	//can use multiple objects with different values without having to re-declare

	
	cout << "area: " << rect.area() << endl;
	cout << "area 2: " << rectb.area() << endl;
	return 0;

}