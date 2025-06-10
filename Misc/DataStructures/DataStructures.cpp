// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Data structs are groups of data elements grouped together under one name

//those elements known as members can have different types and different lengths
#include <iostream>

using namespace std;

int main()
{

    //example struct

    struct product { //name of data struct
        int weight; //variables (members of data struct)
        double price;
    } apple, banana, melon; //names of objects using struct

    //objects can be declared directly when the struct is created
    //or afterwards

    product strawberry;

    //these can be used and modified by inserting a '.' between the
    //object name and member name
    apple.weight = 1;

    cout << apple.weight;

}