#include <iostream>
#include <string>
#include <cstdlib> // for system()

using namespace std;

void printMenu();
void printDatabase();
void printBlockByHash();
void printBlockByHeight();
void exportToCSV();
void refreshDatabase();

int main()
{
    int choice;
    string input;

    while (true)
    {
        printMenu();
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        switch (choice)
        {
        case 1:
            printDatabase();
            break;
        case 2:
            printBlockByHash();
            break;
        case 3:
            printBlockByHeight();
            break;
        case 4:
            exportToCSV();
            break;
        case 5:
            refreshDatabase();
            break;
        case 6:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Please choose 1 through 5, or 6 to exit." << endl;
        }

        cout << endl;
    }

    return 0;
}

// === Function Definitions ===

void printMenu()
{
    cout << "1) Print Database" << endl;
    cout << "2) Print Block By Hash" << endl;
    cout << "3) Print Block By Height" << endl;
    cout << "4) Export Data To .csv" << endl;
    cout << "5) Refresh Database (last N blocks)" << endl;
    cout << "6) Exit" << endl;
    cout << "Enter Your Choice (1 <--> 6): ";
}

void printDatabase()
{
    cout << "Printing Database:" << endl;
    system("./findByHash"); // Replace with actual executable if needed
}

void printBlockByHash()
{
    string hash;
    cout << "Enter Block Hash: ";
    getline(cin, hash);
    cout << "Printing Block Hash: " << hash << endl;
    system(("./refreshDb " + hash).c_str()); // Replace with proper hash tool
}

void printBlockByHeight()
{
    string height;
    cout << "Enter Block Height: ";
    getline(cin, height);
    cout << "Printing Block Height: " << height << endl;
    system(("./refreshDb " + height).c_str()); // Replace with proper height tool
}

void exportToCSV()
{
    string count;
    cout << "Enter Number Of Blocks To Import To The Database .csv File: ";
    getline(cin, count);
    system(("./refreshDb " + count).c_str()); // Replace with actual CSV exporter
}

void refreshDatabase()
{
    string count;
    cout << "Enter Number Of Blocks To Refresh To The Database .csv File: ";
    getline(cin, count);
    system(("./refreshDb " + count).c_str()); // Replace with proper refresh logic
}