#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

constexpr const char *BLOCKCHAIN_BASH_FILE_PATH = "../assignment_1_a.sh";
constexpr const char *DATABASE_CSV_FILE_NAME = "../database.csv";
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

    void print() const
    {
        cout << "hash: " << hash << endl;
        cout << "height: " << height << endl;
        cout << "total: " << total << endl;
        cout << "time: " << time << endl;
        cout << "relayed_by: " << relayed_by << endl;
        cout << "prev_block: " << prev_block << endl;
    }
};

static bool openDatabaseCSV(ifstream &file, const string &fileName);
static bool isValidHash(const string &i_HashToCheck);
static bool isValidHeight(const string &i_HeightToCheck);
static bool tryParseBlockFromLine(const string &line, Block &i_Block);
static void printBlock(const Block &i_Block);
static bool FindBlockByHash(const string &fileName, const string &i_hashQuery);
static bool FindBlockByHeight(const string &fileName, const string &i_heightQuery);
static bool handleFindByHash(const string &input);
static bool handleFindByHeight(const string &input);

// === Utilities ===

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
static bool isValidHash(const string &i_HashToCheck)
{
    return !i_HashToCheck.empty() &&
           i_HashToCheck.length() == 64 &&
           regex_match(i_HashToCheck, regex("^[0-9a-fA-F]{64}$"));
}

static bool isValidHeight(const string &i_HeightToCheck)
{
    return !i_HeightToCheck.empty() &&
           regex_match(i_HeightToCheck, regex("^[1-9][0-9]*$")); // Positive integer only
}

// === Block Parsing & Display ===
static bool tryParseBlockFromLine(const string &line, Block &i_Block)
{
    stringstream ss(line);
    string temp;

    if (!getline(ss, i_Block.hash, ','))
        return false;
    if (!getline(ss, temp, ','))
        return false;
    i_Block.height = stol(temp);
    if (!getline(ss, temp, ','))
        return false;
    i_Block.total = stoll(temp);
    if (!getline(ss, i_Block.time, ','))
        return false;
    if (!getline(ss, i_Block.relayed_by, ','))
        return false;
    if (!getline(ss, i_Block.prev_block, ','))
        return false;

    return true;
}

static void printBlock(const Block &i_Block)
{
    cout << "hash: " << i_Block.hash << endl;
    cout << "height: " << i_Block.height << endl;
    cout << "total: " << i_Block.total << endl;
    cout << "time: " << i_Block.time << endl;
    cout << "relayed_by: " << i_Block.relayed_by << endl;
    cout << "prev_block: " << i_Block.prev_block << endl;
}

// === Search by Hash ===
static bool FindBlockByHash(const string &fileName, const string &i_hashQuery)
{
    ifstream file;
    if (!openDatabaseCSV(file, fileName))
    {
        return false;
    }

    string line;
    getline(file, line); // Skip header

    Block tempCurrentBlock;
    while (getline(file, line))
    {
        if (!tryParseBlockFromLine(line, tempCurrentBlock))
        {
            continue;
        }

        if (tempCurrentBlock.hash == i_hashQuery)
        {
            cout << "Printing block with hash: " << i_hashQuery << endl;
            tempCurrentBlock.print();
            return true;
        }
    }

    cout << "Block with hash: " << i_hashQuery << " was not found in the local database." << endl;
    cout << "Please run refresh database first." << endl;
    return false;
}

// === Search by Height ===
static bool FindBlockByHeight(const string &fileName, const string &i_heightQuery)
{
    ifstream file;
    if (!openDatabaseCSV(file, fileName))
    {
        return false;
    }

    long targetHeight = stol(i_heightQuery);
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
            cout << "Printing block with height: " << i_heightQuery << endl;
            printBlock(b);
            return true;
        }
    }

    cout << "Block with height: " << i_heightQuery << " was not found in the local database." << endl;
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