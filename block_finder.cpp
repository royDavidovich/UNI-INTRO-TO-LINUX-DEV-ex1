#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

constexpr const char *BLOCKCHAIN_BASH_FILE_PATH = "./assignment_1_a.sh";
constexpr const char *DATABASE_CSV_FILE_NAME = "database.csv";
constexpr const char *MODE_SEARCH_BY_HASH = "--hash";
constexpr const char *MODE_SEARCH_BY_HEIGHT = "--height";

struct Block
{
    string hash;
    long height;
    long long total;
    string time;
    string relayed_by;
    string prev_block;
};

// === Utilities ===
static bool fileIsReadable(const string &fileName)
{
    ifstream file(fileName);
    return file.is_open();
}

static bool openDatabaseCSV(ifstream &file, const string &fileName)
{
    file.open(fileName);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        return false;
    }
    return true;
}

// === Validation ===
static bool isValidHash(const string &hash)
{
    return !hash.empty() &&
           hash.length() == 64 &&
           regex_match(hash, regex("^[0-9a-fA-F]{64}$"));
}

static bool isValidHeight(const string &height)
{
    return !height.empty() &&
           regex_match(height, regex("^[1-9][0-9]*$")); // Positive integer only
}

// === Block Parsing & Display ===
static bool tryParseBlockFromLine(const string &line, Block &b)
{
    stringstream ss(line);
    string temp;

    if (!getline(ss, b.hash, ','))
        return false;
    if (!getline(ss, temp, ','))
        return false;
    b.height = stol(temp);
    if (!getline(ss, temp, ','))
        return false;
    b.total = stoll(temp);
    if (!getline(ss, b.time, ','))
        return false;
    if (!getline(ss, b.relayed_by, ','))
        return false;
    if (!getline(ss, b.prev_block, ','))
        return false;

    return true;
}

static void printBlock(const Block &b)
{
    cout << "hash: " << b.hash << endl;
    cout << "height: " << b.height << endl;
    cout << "total: " << b.total << endl;
    cout << "time: " << b.time << endl;
    cout << "relayed_by: " << b.relayed_by << endl;
    cout << "prev_block: " << b.prev_block << endl;
}

// === Search by Hash ===
static bool FindBlockByHash(const string &fileName, const string &hashQuery)
{
    ifstream file;
    if (!openDatabaseCSV(file, fileName))
    {
        return false;
    }

    string line;
    getline(file, line); // Skip header

    Block b;
    while (getline(file, line))
    {
        if (!tryParseBlockFromLine(line, b))
        {
            continue;
        }

        if (b.hash == hashQuery)
        {
            cout << "Printing block with hash: " << hashQuery << endl;
            printBlock(b);
            return true;
        }
    }

    cout << "Block with hash: " << hashQuery << " was not found in the local database." << endl;
    cout << "Please run refresh database first." << endl;
    return false;
}

// === Search by Height ===
static bool FindBlockByHeight(const string &fileName, const string &heightQuery)
{
    ifstream file;
    if (!openDatabaseCSV(file, fileName))
    {
        return false;
    }

    long targetHeight = stol(heightQuery);
    string line;
    getline(file, line); // Skip header

    Block b;
    while (getline(file, line))
    {
        if (!tryParseBlockFromLine(line, b))
        {
            continue;
        }

        if (b.height == targetHeight)
        {
            cout << "Printing block with height: " << heightQuery << endl;
            printBlock(b);
            return true;
        }
    }

    cout << "Block with height: " << heightQuery << " was not found in the local database." << endl;
    cout << "Please run refresh database first." << endl;
    return false;
}

// === Command Handlers ===
static bool handleFindByHash(const string &input)
{
    if (!isValidHash(input))
    {
        cerr << "Invalid hash format." << endl;
        return false;
    }
    return FindBlockByHash(DATABASE_CSV_FILE_NAME, input);
}

static bool handleFindByHeight(const string &input)
{
    if (!isValidHeight(input))
    {
        cerr << "Invalid height format." << endl;
        return false;
    }
    return FindBlockByHeight(DATABASE_CSV_FILE_NAME, input);
}

// === Main ===
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " [--hash HASH] | [--height HEIGHT]" << endl;
        return 1;
    }

    const string mode = argv[1];
    const string input = argv[2];

    if (mode == MODE_SEARCH_BY_HASH)
    {
        return handleFindByHash(input) ? 0 : 1;
    }
    else if (mode == MODE_SEARCH_BY_HEIGHT)
    {
        return handleFindByHeight(input) ? 0 : 1;
    }
    else
    {
        cerr << "Invalid mode. Use --hash or --height." << endl;
        return 1;
    }
}