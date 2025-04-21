#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

constexpr const char* BLOCKCHAIN_BASH_FILE_PATH = "./assignment_1_a.sh";
constexpr const char* DATABASE_CSV_FILE_NAME = "database.csv";

struct Block
{
    string hash;
    long height;
    long long total;
    string time;
    string relayed_by;
    string prev_block;
};

static bool printdb(const string &DB_fileName);
static bool fileIsReadable(const string &fileName);
static bool openDatabaseFile(const string &fileName, ifstream &file);
static vector<Block> parseBlocksFromCSV(ifstream &file);
static void printBlockChain(const vector<Block> &blocks);
static void printBlock(const Block &block);

// === Main ===
int main()
{
    printdb(DATABASE_CSV_FILE_NAME);
    return 0;
}

// === Function Definitions ===

static bool printdb(const string &DB_fileName)
{
    bool success = true;
    ifstream file;

    if (success && !fileIsReadable(DB_fileName))
    {
        cerr << "File is not readable or does not exist: " << DB_fileName << endl;
        success = false;
    }

    if (success && !openDatabaseFile(DB_fileName, file))
    {
        cerr << "Error opening file!" << endl;
        success = false;
    }

    if (success)
    {
        vector<Block> blocks = parseBlocksFromCSV(file);
        printBlockChain(blocks);
    }
    
    return success;
}

static bool fileIsReadable(const string &fileName)
{
    ifstream file(fileName);
    return file.is_open();
}

static bool openDatabaseFile(const string &fileName, ifstream &file)
{
    file.open(fileName);
    return file.is_open();
}

static vector<Block> parseBlocksFromCSV(ifstream &file)
{
    vector<Block> blocks;
    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        Block b;
        string temp;

        getline(ss, b.hash, ',');
        getline(ss, temp, ',');
        b.height = stol(temp);
        getline(ss, temp, ',');
        b.total = stoll(temp);
        getline(ss, b.time, ',');
        getline(ss, b.relayed_by, ',');
        getline(ss, b.prev_block, ',');

        blocks.push_back(b);
    }

    return blocks;
}

static void printBlockChain(const vector<Block> &blocks)
{
    for (size_t i = 0; i < blocks.size(); ++i)
    {
        printBlock(blocks[i]);

        if (i != blocks.size() - 1)
        {
            cout << "                        |" << endl;
            cout << "                        |" << endl;
            cout << "                        |" << endl;
            cout << "                        V" << endl;
        }
    }
}

static void printBlock(const Block &block)
{
    cout << "hash: " << block.hash << endl;
    cout << "height: " << block.height << endl;
    cout << "total: " << block.total << endl;
    cout << "time: " << block.time << endl;
    cout << "relayed_by: " << block.relayed_by << endl;
    cout << "prev_block: " << block.prev_block << endl;
}