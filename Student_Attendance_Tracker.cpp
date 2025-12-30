// *********************************************************
// Program: Student Attendance Tracker.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2530
// Member_1: 253UC246FX | Hazim Zubair | hazim.zubair1@student.mmu.edu.my
// Member_2: 253UC2454U | Aemir Mussadiq bin Aemir Firdauz | aemir.mussadiq.aemir1@student.mmu.edu.my
// Member_3: ID | NAME | EMAIL
// Member_4: ID | NAME | EMAIL
// *********************************************************
// Task Distribution
// Member_1: Sheet & Column Setup – Ask for sheet name, define columns, store column names & types
// Member_2: Data Entry & Validation – Loop to input rows, check INT/TEXT types, store in array
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <string>
using namespace std;

bool isInteger(const string &s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return !s.empty();
}

int main()
{
    // VARIABLES
    string SheetName, ColName[10], ColType[10], TypeChecker;
    int NumOfCol, ColCount = 0;
    const int MAX_ROWS = 50;
    string sheet[MAX_ROWS][10];
    int rowCount = 0;

    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "Enter attendance sheet name: ";
    getline(cin, SheetName);

    cout << "Attendance sheet \"" << SheetName << "\" created successfully." << endl;

    cout << "Define number of columns (max 10): ";
    cin >> NumOfCol;
    while (NumOfCol < 1 || NumOfCol > 10)
    {
        cout << "Invalid number of columns. Please enter a number between 1 and 10: ";
        cin >> NumOfCol;
    }
    cin.ignore();

    cout << "Define " << NumOfCol << " columns." << endl;

    while (ColCount < NumOfCol)
    {
        cout << "Enter column " << ColCount + 1 << " name: ";
        getline(cin, ColName[ColCount]);

        while (true)
        {
            cout << "Enter column " << ColCount + 1 << " type (TEXT/INT): ";
            cin >> TypeChecker;
            if (TypeChecker == "TEXT" || TypeChecker == "INT" || TypeChecker == "text" || TypeChecker == "int")
            {
                if (TypeChecker == "text") TypeChecker = "TEXT";
                else if (TypeChecker == "int") TypeChecker = "INT";

                ColType[ColCount] = TypeChecker;
                cout << "Column " << ColCount + 1 << " \"" << ColName[ColCount] << "\" of type " << ColType[ColCount] << " created successfully." << endl;
                break;
            }
            else
            {
                cout << "Invalid column type. Please enter either TEXT or INT." << endl;
            }
        }

        ColCount++;
        cin.ignore();
    }

    // ----------- DATA ENTRY & VALIDATION -----------
    char addMore = 'Y';
    while (toupper(addMore) == 'Y' && rowCount < MAX_ROWS)
    {
        cout << "\nEntering data for row " << rowCount + 1 << ":\n";
        for (int i = 0; i < ColCount; i++)
        {
            string input;
            while (true)
            {
                cout << ColName[i] << " (" << ColType[i] << "): ";
                cin >> input;

                if (ColType[i] == "INT")
                {
                    if (!isInteger(input))
                    {
                        cout << "Invalid input. Please enter an integer." << endl;
                        continue; 
                    }
                    else if (stoi(input) < 0) 
                    {
                        cout << "Invalid input. Please enter a positive integer." << endl;
                        continue; 
                    }
                }

                else if (ColType[i] == "TEXT")
                {
                    if (input.empty())
                    {
                        cout << "Invalid input. Text cannot be empty." << endl;
                        continue;
                    }
                    else if (input.length() > 50)
                    {
                        cout << "Input too long. Please enter less than 50 characters." << endl;
                        continue;
                    }
                }

                sheet[rowCount][i] = input;
                break;
            }
        }
        rowCount++;

        while (true)
        {
            cout << "Add another row? (Y/N): ";
            cin >> addMore;
            addMore = toupper(addMore);
            if (addMore == 'Y' || addMore == 'N')
                break;
            else
                cout << "Invalid input. Please enter Y or N." << endl;
        }
    }

    return 0;
}
