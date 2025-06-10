// DynamicMemory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <new>
using namespace std;

int main()
{
    int i, n; //undeclared variables
    int* p; //pointer
    cout << "How many numbers would you like to type?\n";
    cin >> i;
    p = new (nothrow) int[i]; //prevents compiler from throwing an exception

    //returns a 0 to the pointer if the memory fails to be allocated

    if (p == 0)
        cout << "Error: memory could not be allocated";
    else
    {
        for (n = 0; n < i;n++)
        {

            cout << "Enter number: ";
            cin >> p[n];
        }


        cout << "You have entered: ";

        for (n = 0;n < i;n++)
        {
            cout << p[n] << ", ";
        }
        delete[]p;


    }return 0;
}
