#include <iostream>
#include <regex>

using namespace std;

constexpr const char *BLOCKCHAIN_BASH_FILE_PATH = "./assignment_1_a.sh";
constexpr const char *DATABASE_CSV_FILE_NAME = "database.csv";

bool isValidRefreshRequest(const string &i_NumberOfBlocksToFetch);
static bool refreshData(string BashScriptFilePath, int i_NumOfBlocksToGet);

bool isValidRefreshRequest(const string &i_NumberOfBlocksToFetch)
{
    if (i_NumberOfBlocksToFetch.empty())
    {
        return false;
    }

    // Check if it's all digits
    if (!regex_match(i_NumberOfBlocksToFetch, regex("^[0-9]+$")))
    {
        return false;
    }

    // Convert to int and check the range
    try
    {
        int numberOfBlocksToFetch = stoi(i_NumberOfBlocksToFetch);
        return ((numberOfBlocksToFetch >= 1) && (numberOfBlocksToFetch <= 50));
    }
    catch (...)
    {
        return false; // stoi failed
    }
}

static bool refreshData(string BashScriptFilePath, int i_NumOfBlocksToGet) // function numbers 3 and 4
{
    // Valid number - run script
    string command = "bash " + BashScriptFilePath + " " + to_string(i_NumOfBlocksToGet);
    system(command.c_str());
    return true;

    return false; // not reached normally
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error: No argument provided." << endl;
        return 1;
    }

    if (isValidRefreshRequest(argv[1]))
    {
        int numberOfBlocksToRefresh = stoi(argv[1]);
        refreshData(BLOCKCHAIN_BASH_FILE_PATH, numberOfBlocksToRefresh);
    }

    return 0;
}