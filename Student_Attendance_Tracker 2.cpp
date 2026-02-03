// *********************************************************
// Program: Student_Attendance_Tracker 2.cpp
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
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <fstream> // For file handling
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

// Structure to hold attendance sheet data ( database )
struct Attendancesheet
{
    string sheetName;
    string colName[10];
    string colType[10];
    string data[50][10];
    int numOfCol;
    int rowCount;
};
Attendancesheet database[10];
int sheetCount = 0;
string termName;

void displayCSV(const Attendancesheet &sheet)
{
    // Print column headers
    for (int i = 0; i < sheet.numOfCol; i++)
    {
        cout << sheet.colName[i];
        if (i < sheet.numOfCol - 1)
            cout << ", ";
    }
    cout << endl;

    // Print rows
    for (int i = 0; i < sheet.rowCount; i++)
    {
        for (int j = 0; j < sheet.numOfCol; j++)
        {
            cout << sheet.data[i][j];
            if (j < sheet.numOfCol - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

// Function to count total rows across all sheets
void CountRows()
{
    if (sheetCount == 0)
    {
        cout << "Database is empty. No sheets to count." << endl;
        return;
    }

    int totalAcrossAll = 0;
    cout << "\n--- Attendance Summary ---" << endl;
    for (int i = 0; i < sheetCount; i++)
    {
        cout << "Sheet: " << database[i].sheetName
             << " | Total Students: " << database[i].rowCount << endl;
        totalAcrossAll += database[i].rowCount;
    }
    cout << "Total students in term: " << totalAcrossAll << endl;
}

// Function to view current term name
void viewTermName()
{
    if (termName.empty())
    {
        cout << "No School Term created yet." << endl;
        cin.get();
    }
    else
    {
        cout << "Current School Term: " << termName << endl;
    }
}

// Function to create a new attendance sheet
void sheetCreation()
{
    if (sheetCount >= 10)
    {
        cout << "Database is full. Cannot create more sheets.\n";
        return;
    }

    string SheetName, ColName[10], ColType[10], TypeChecker;
    int NumOfCol, ColCount = 0;

    cout << "Enter attendance sheet name: ";
    getline(cin, SheetName);

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
        cout << "Invalid input. Please enter a number between 1 and 10.\n";
    }

    cout << "\nDefine " << NumOfCol << " columns.\n";

    while (ColCount < NumOfCol)
    {
        cout << "\nEnter column " << ColCount + 1 << " name: ";
        getline(cin, ColName[ColCount]);

        if (ColName[ColCount].empty() ||
            ColName[ColCount].find_first_not_of(' ') == string::npos)
        {
            cout << "Column name cannot be empty.\n";
            continue;
        }

        // Trim spaces
        size_t first = ColName[ColCount].find_first_not_of(' ');
        size_t last = ColName[ColCount].find_last_not_of(' ');
        ColName[ColCount] = ColName[ColCount].substr(first, last - first + 1);

        if (ColName[ColCount] == "status" || ColName[ColCount] == "Status" || ColName[ColCount] == "STATUS")
        {
            ColName[ColCount] = "Status (Present: 1, Absent: 0)";
            ColType[ColCount] = "INT";
            cout << "Column set as INT automatically.\n";
        }
        else if (ColName[ColCount] == "attendance" || ColName[ColCount] == "Attendance" || ColName[ColCount] == "ATTENDANCE")
        {
            ColName[ColCount] = "Attendance (Present: 1, Absent: 0)";
            ColType[ColCount] = "INT";
            cout << "Column set as INT automatically.\n";
        }
        else
        {
            while (true)
            {
                cout << "Enter column type (TEXT / INT): ";
                getline(cin, TypeChecker);

                if (TypeChecker == "TEXT" || TypeChecker == "text")
                {
                    ColType[ColCount] = "TEXT";
                    break;
                }
                else if (TypeChecker == "INT" || TypeChecker == "int")
                {
                    ColType[ColCount] = "INT";
                    break;
                }
                else
                {
                    cout << "Invalid type. Try again.\n";
                }
            }
        }

        cout << "Column \"" << ColName[ColCount]
             << "\" of type " << ColType[ColCount]
             << " created successfully.\n";

        ColCount++;
    }

    // Save into database
    database[sheetCount].sheetName = SheetName;
    database[sheetCount].numOfCol = NumOfCol;
    database[sheetCount].rowCount = 0;

    for (int i = 0; i < NumOfCol; i++)
    {
        database[sheetCount].colName[i] = ColName[i];
        database[sheetCount].colType[i] = ColType[i];
    }

    sheetCount++;

    cout << "\nAttendance sheet \"" << SheetName << "\" saved successfully!\n";
}

// Function to save data to CSV file
void saveToFile()
{
    ofstream file("Student_Attendance_Tracker 2_data.csv");
    if (!file.is_open())
    {
        cout << "Error when opening file to save data." << endl;
        return;
    }

    // For term name
    file << "School Term: " << termName << endl;

    // For headers
    for (int i = 0; i < sheetCount; i++)
    {
        file << "Sheet: " << database[i].sheetName << endl;
        for (int j = 0; j < database[i].numOfCol; j++)
        {
            file << database[i].colName[j] << ",";
        }
        file << endl;

        // Write the data
        for (int r = 0; r < database[i].rowCount; r++)
        {
            for (int c = 0; c < database[i].numOfCol; c++)
            {
                file << database[i].data[r][c] << ",";
            }
            file << endl;
        }
    }

    file.close();
    cout << "Data saved successfully to Student_Attendance_Tracker 2_data.csv" << endl;
}

// Function to load data from CSV file
void loadFromFile()
{
    ifstream file("Student_Attendance_Tracker 2_data.csv");
    if (!file.is_open())
    {
        cout << "Data created and loaded" << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        if (line.find("Sheet:") != string::npos)
        {
            string sheetName = line.substr(7);
            string colNames[10];
            string colTypes[10];

            // Read col names and types
            getline(file, line);
            int colCount = 0;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos)
            {
                colNames[colCount] = line.substr(0, pos);
                line.erase(0, pos + 1);
                colTypes[colCount] = (line == "INT") ? "INT" : "TEXT";
                colCount++;
            }

            // Load data for the sheet
            int rowCount = 0;
            while (getline(file, line) && !line.empty())
            {
                size_t pos = 0;
                int colIndex = 0;
                while ((pos = line.find(',')) != string::npos)
                {
                    database[sheetCount].data[rowCount][colIndex] = line.substr(0, pos);
                    line.erase(0, pos + 1);
                    colIndex++;
                }
                rowCount++;
            }
        }
    }

    file.close();
    cout << "Data loaded successfully from Student_Attendance_Tracker 2_data.csv" << endl;
}

// ---------- Edit Sheet ----------
void editSheet(int index)
{
    Attendancesheet &sheet = database[index];
    char addMore = 'Y';
    int mode;
    string input;
    while (true)
    {
        cout << "do you want to view the sheet or edit (1 = view , 2 = edit  and 0 = back)" << endl;
        getline(cin, input); // read as string

        if (!isInteger(input)) // check if input is a valid integer
        {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        mode = stoi(input);
        if (mode == 1)
        {
            // ----------- DISPLAY THE ATTENDANCE SHEET IN CSV FORMAT -----------
            cout << "\n-------------------------------------------" << endl;
            cout << "View Attendance Sheet (CSV Mode)" << endl;
            cout << "-------------------------------------------" << endl;
            displayCSV(sheet);

            cout << "\nPress Enter to go back.";
            cin.get();
            return;
        }

        else if (mode == 2)
        {
            while (toupper(addMore) == 'Y' && sheet.rowCount < 50)
            {
                for (int i = 0; i < sheet.numOfCol; i++)
                {
                    string input;
                    while (true)
                    {
                        cout << sheet.colName[i] << ": ";
                        getline(cin, input);

                        if (sheet.colType[i] == "INT")
                        {
                            if (!isInteger(input))
                            {
                                cout << "Enter integer only.\n";
                                continue;
                            }
                            int v = stoi(input);
                            if (sheet.colName[i].find("Status") != string::npos &&
                                v != 0 && v != 1)
                            {
                                cout << "Only 0 or 1 allowed.\n";
                                continue;
                            }
                        }
                        else
                        {
                            if (input.empty())
                            {
                                cout << "Text cannot be empty.\n";
                                continue;
                            }
                        }

                        sheet.data[sheet.rowCount][i] = input;
                        break;
                    }
                }

                sheet.rowCount++;

                cout << "Add another row? (Y/N): ";
                cin >> addMore;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            // ----------- DISPLAY THE ATTENDANCE SHEET IN CSV FORMAT -----------
            cout << "\n-------------------------------------------" << endl;
            cout << "View Attendance Sheet (CSV Mode)" << endl;
            cout << "-------------------------------------------" << endl;
            displayCSV(sheet);

            cout << "\nPress Enter to go back.";
            cin.get();
            return;
        }
        else if (mode == 0)
        {
            return;
        }
        else
        {
            cout << "invalid in put" << endl;
        }
    }
}

// ---------- Choose Sheet ----------
int chooseSheet()
{
    if (sheetCount == 0)
    {
        cout << "No sheets available.\n";
        return -1;
    }

    for (int i = 0; i < sheetCount; i++)
        cout << i + 1 << ". " << database[i].sheetName << endl;

    string input;
    cout << "Choose sheet number: ";
    getline(cin, input);

    if (isInteger(input))
    {
        int c = stoi(input);
        if (c >= 1 && c <= sheetCount)
            return c - 1;
    }

    cout << "Invalid selection.\n";
    return -1;
}

int main()
{
    // VARIABLES
    string SheetName, ColName[10], ColType[10], TypeChecker;
    int NumOfCol, ColCount = 0;
    const int MAX_ROWS = 50;
    string sheet[MAX_ROWS][10];
    int rowCount = 0;

    cout << "Enter School Term Name (e.g., Trimester 2530): " << endl;
    getline(cin, termName);
    while (termName.empty())
    {
        cout << "School Term Name cannot be empty. Please enter a valid name: ";
        getline(cin, termName);
    }
    viewTermName();
    int choice;

    // Load existing data from file
    loadFromFile();

    while (true)
    {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Create Sheet\n";
        cout << "2. View Term\n";
        cout << "3. Count Rows\n";
        cout << "4. Save Data\n";
        cout << "5. View/add data to Sheet\n";
        cout << "6. Update/Delete Record\n";
        cout << "7. delete sheet\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0)
            break;
        else if (choice == 1)
            sheetCreation();
        else if (choice == 2)
            viewTermName();
        else if (choice == 3)
            CountRows();
        else if (choice == 4)
            saveToFile();
        else if (choice == 5)
        {
            int sheetID = chooseSheet();
            if (sheetID != -1)
                editSheet(sheetID);
        }
    }

    return 0;
}
