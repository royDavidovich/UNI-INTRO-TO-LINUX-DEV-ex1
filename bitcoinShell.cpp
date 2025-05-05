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
    cout << "    --MENU--     " << endl;
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
    system("./printDatabase");
}

void printBlockByHash()
{
    string hash;
    cout << "Enter block hash: ";
    getline(cin, hash);
    system(("./blockFinder --hash " + hash).c_str());
}

void printBlockByHeight()
{
    string height;
    cout << "Enter block height: ";
    getline(cin, height);
    system(("./blockFinder --height " + height).c_str());
}

void exportToCSV()
{
    // this isn't really needed, but kept for later use
}

void refreshDatabase()
{
    string count;
    cout << "Enter Number Of Blocks To Refresh To The Database .csv File: ";
    getline(cin, count);
    system(("./refreshDatabase " + count).c_str());
}