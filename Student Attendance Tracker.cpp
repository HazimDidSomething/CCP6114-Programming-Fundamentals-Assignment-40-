// *********************************************************
// Program: Student Attendance Tracker.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2530
// Member_1: 253UC246FX | Hazim Zubair | hazim.zubair1@students.mmu.edu.my
// Member_2: ID | NAME | EMAIL
// Member_3: ID | NAME | EMAIL
// Member_4: ID | NAME | EMAIL
// *********************************************************
// Task Distribution
// Member_1: Sheet & Column Setup – Ask for sheet name, define columns, store column names & types
// Member_2:
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <string>
using namespace std;
int main()
{
    // VARIABLES
    string SheetName, ColName[10], ColType[10], TypeChecker;
    int NumOfCol, ColCount = 0;

    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "Enter attendance sheet name: ";
    getline(cin, SheetName);

    cout << "Attendance sheet " << SheetName << " created successfully." << endl;

    cout << "Define number of columns (max 10): ";
    cin >> NumOfCol;
    while (NumOfCol < 1 || NumOfCol > 10)
    {
        cout << "Invalid number of columns. Please enter a number between 1 and 10: ";
        cin >> NumOfCol;
    }
    cin.ignore();
    cout << "Define " << NumOfCol << " columns." << endl;

    while (NumOfCol != 0)
    {
        cout << "Enter column " << ColCount + 1 << " name: ";
        getline(cin, ColName[ColCount]);
        while (true)
        {
            cout << "Enter column " << ColCount + 1 << " type (TEXT/INT): ";
            cin >> TypeChecker;
            if (TypeChecker == "TEXT" || TypeChecker == "INT" || TypeChecker == "text" || TypeChecker == "int")
            {
                if (TypeChecker == "text")
                    TypeChecker = "TEXT";
                else if (TypeChecker == "int")
                    TypeChecker = "INT";
                ColType[ColCount] = TypeChecker;
                cout << "Column" << ColCount + 1 << " \"" << ColName[ColCount] << "\" of type " << ColType[ColCount] << " created successfully." << endl;
                break;
            }
            else
            {
                cout << "Invalid column type. Please enter either TEXT or INT." << endl;
            }
        }

        ColCount++;
        NumOfCol--;
    }

    return 0;
}
