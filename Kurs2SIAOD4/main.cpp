#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ExternalFunctionality.cpp"
using namespace std;
int main() {
    cout<<"Practical work 4.Group IKBO-10-19.Gluchov Vladimir.\n"<<endl;
    cout << "Enter code command\n";
    cout << "1 - Convert txt file to binary\n2 - Print binary file\n3 - Update data by key\n4 - Search data by key\n";
    cout << "5 - Delete binary file\n6 - End of work.\n";
    ExtFunc func;
    func.startProgram();
    return 0;
}

