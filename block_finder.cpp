#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

#define BLOCKCHAIN_BASH_FILE_PATH "./assignment_1_a.sh"
#define DATABASE_CSV_FILE_NAME "database.csv"
#define MODE_MODE_SEARCH_BY_HASH "--hash"
#define MODE_MODE_SEARCH_BY_HEIGHT "--height"

struct Block
{
    string hash;
    long height;
    long long total;
    string time;
    string relayed_by;
    string prev_block;
};

static bool isValidHash(const string& i_HashToCheck)
{
    if (i_HashToCheck.empty())
    {
        return false;
    }
    return ((i_HashToCheck.length() == 64) && (regex_match(i_HashToCheck, regex("^[0-9a-fA-F]{64}$"))));
}

static bool isValidHeight(const string& i_HeightToCheck)
{
    if (i_HeightToCheck.empty())
    {
        return false;
    }
    return regex_match(i_HeightToCheck, regex("^[1-9][0-9]*$"));  //positive integer only
}

static void printBlock(const Block& i_Block)
{
    cout << "hash: " << i_Block.hash << endl;
    cout << "height: " << i_Block.height << endl;
    cout << "total: " << i_Block.total << endl;
    cout << "time: " << i_Block.time << endl;
    cout << "relayed_by: " << i_Block.relayed_by << endl;
    cout << "prev_block: " << i_Block.prev_block << endl;
}

static bool FindBlockInDataBaseByHash(string i_DataBaseFileName, string i_HashToFetch = "")
{
    bool success = false;

    // Valid hash - run script
    ifstream file(i_DataBaseFileName);
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
    }
    else
    {
        string line;
        getline(file, line); // Skip header

        Block b;
        string temp;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, b.hash, ',');
            if (b.hash == i_HashToFetch)
            {
                getline(ss, temp, ',');
                b.height = stoi(temp);
                getline(ss, temp, ',');
                b.total = stoll(temp);
                getline(ss, b.time, ',');
                getline(ss, b.relayed_by, ',');
                getline(ss, b.prev_block, ',');

                cout << "Printing block with hash: " << i_HashToFetch << endl;
                printBlock(b);
                success = true;
                break;
            }
        }

        if (success != true)
        {
            cout << "Block with hash: " << i_HashToFetch << " was not found in the local database." << endl;
            cout << "Please run refresh database first." << endl;
        }
    }

    return success;
}

static bool FindBlockInDataBaseByHeight(string i_DataBaseFileName, string i_UserInput = "")
{
    long heightToFetch = stol(i_UserInput);
    bool success = false;

    // Valid height - run script
    ifstream file(i_DataBaseFileName);
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
    }
    else
    {
        string line;
        getline(file, line); // Skip header

        Block b;
        string temp;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, b.hash, ',');
            getline(ss, temp, ',');
            b.height = stoi(temp);
            if (b.height == heightToFetch)
            {
                getline(ss, temp, ',');
                b.total = stoll(temp);
                getline(ss, b.time, ',');
                getline(ss, b.relayed_by, ',');
                getline(ss, b.prev_block, ',');

                cout << "Printing block with height: " << to_string(heightToFetch) << endl;
                printBlock(b);
                success = true;
                break;
            }
        }

        if (success != true)
        {
            cout << "Block with height: " << to_string(heightToFetch) << " was not found in the local database." << endl;
            cout << "Please run refresh database first." << endl;
        }
    }

    return success;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Error: No argument provided." << endl;
        return 1;
    }

    string mode_mode = argv[1];
    string userInput = argv[2];

    if (mode_mode == MODE_MODE_SEARCH_BY_HASH)
    {
        isValidHash(userInput);
        FindBlockInDataBaseByHash(DATABASE_CSV_FILE_NAME, userInput);
    }
    else if (mode_mode == MODE_MODE_SEARCH_BY_HEIGHT)
    {
        isValidHeight(userInput);
        FindBlockInDataBaseByHeight(DATABASE_CSV_FILE_NAME, userInput);
    }
    else
    {
        cerr << "Error: No argument provided." << endl;
        return 1;
    }

    return 0;
}