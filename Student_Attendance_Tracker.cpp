// *********************************************************
// Program: Student Attendance Tracker.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT4L
// Trimester: 2530
// Member_1: 253UC246FX | Hazim Zubair | hazim.zubair1@student.mmu.edu.my
// Member_2: 253UC2454U | Aemir Mussadiq bin Aemir Firdauz | aemir.mussadiq.aemir1@student.mmu.edu.my
// Member_3: 253UC243ZS | Irfan Mukhriz bin Abd Malek | irfan.mukhriz.abd1@student.mmu.edu.my
// Member_4: 253UC245TK | Aqeef Azizi bin Nor Azizi | aqeef.azizi.nor1@student.mmu.edu.my
// *********************************************************
// Task Distribution
// Member_1: Sheet & Column Setup – Ask for sheet name, define columns, store column names & types
// Member_2: Data Entry & Validation – Loop to input rows, check INT/TEXT types, store in array
// Member_3: CSV Display & Output – Print the attendance sheet in CSV format, handles output formatting
// Member_4: Documentation & Header – Write program header, add comments, pseudocode, and sample input/output
// *********************************************************

#include <iostream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

bool isInteger(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// Function: Display sheet in CSV format
void displayCSV(string sheet[][10], int rowCount, string ColName[], int ColCount)
{
    // Print column headers
    for (int i = 0; i < ColCount; i++)
    {
        cout << ColName[i];
        if (i < ColCount - 1)
            cout << ", ";
    }
    cout << endl;

    // Print the rows of sheet
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < ColCount; j++)
        {
            cout << sheet[i][j];
            if (j < ColCount - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

int main()
{
    // VARIABLES
    string SheetName, ColName[10], ColType[10], TypeChecker;
    int NumOfCol, ColCount = 0;
    const int MAX_ROWS = 50;
    string sheet[MAX_ROWS][10];
    int rowCount = 0;

    // ----------- SHEET & COLUMN SETUP -----------
    cout << "===========================================" << endl;
    cout << "STUDENT ATTENDANCE TRACKER - MILESTONE 1" << endl;
    cout << "===========================================" << endl;

    cout << "Enter attendance sheet name: ";
    getline(cin, SheetName);
    cout << "Attendance sheet \"" << SheetName << "\" created successfully." << endl;

    while (true)
    {
        cout << "Define number of columns (max 10): ";
        string input;
        getline(cin, input);

        if (isInteger(input))
        {
            NumOfCol = stoi(input);
            if (NumOfCol >= 1 && NumOfCol <= 10)
                break;
        }
        cout << "Invalid input. Please enter a number between 1 and 10." << endl;
    }

    cout << "Define " << NumOfCol << " columns.\n";

    while (ColCount < NumOfCol)
    {
        cout << "Enter column " << ColCount + 1 << " name: ";
        getline(cin, ColName[ColCount]);

        while (true)
        {
            cout << "Enter column " << ColCount + 1 << " type (TEXT/INT): ";
            cin >> TypeChecker;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (TypeChecker == "TEXT" || TypeChecker == "INT" || TypeChecker == "text" || TypeChecker == "int")
            {
                if (TypeChecker == "text")
                    TypeChecker = "TEXT";
                else if (TypeChecker == "int")
                    TypeChecker = "INT";

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
    }

    // ----------- DATA ENTRY & VALIDATION -----------
    char addMore = 'Y';
    while (toupper(addMore) == 'Y' && rowCount < MAX_ROWS)
    {
        cout << "\n-------------------------------------------" << endl;
        cout << "Insert New Attendance (Row " << rowCount + 1 << ")" << endl;
        cout << "-------------------------------------------" << endl;

        string studentID, studentName, status;
        while (true)
        {
            cout << "Enter ID: ";
            getline(cin, studentID);
            if (!isInteger(studentID))
            {
                cout << "Invalid ID. Please enter a valid integer ID." << endl;
                continue;
            }

            cout << "Enter Name: ";
            getline(cin, studentName);
            if (studentName.empty())
            {
                cout << "Name cannot be empty. Please enter a valid name." << endl;
                continue;
            }

            cout << "Status (1 = Present, 0 = Absent): ";
            getline(cin, status);
            if (status != "1" && status != "0")
            {
                cout << "Invalid status. Please enter 1 for Present or 0 for Absent." << endl;
                continue;
            }

            // Store values in array
            sheet[rowCount][0] = studentID;
            sheet[rowCount][1] = studentName;
            sheet[rowCount][2] = status;
            break;
        }
        rowCount++;

        while (true)
        {
            cout << "Add another row? (Y/N): ";
            cin >> addMore;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            addMore = toupper(addMore);
            if (addMore == 'Y' || addMore == 'N')
                break;
            else
                cout << "Invalid input. Please enter Y or N." << endl;
        }
    }

    // ----------- DISPLAY THE ATTENDANCE SHEET IN CSV FORMAT -----------
    cout << "\n-------------------------------------------" << endl;
    cout << "View Attendance Sheet (CSV Mode)" << endl;
    cout << "-------------------------------------------" << endl;
    displayCSV(sheet, rowCount, ColName, ColCount);

    cout << "\n-------------------------------------------" << endl;
    cout << "End of Milestone 1 Output, Great Input!" << endl;
    cout << "-------------------------------------------" << endl;

    return 0;
}
