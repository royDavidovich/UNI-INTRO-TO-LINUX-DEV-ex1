#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define BLOCKCHAIN_BASH_FILE_PATH "./assignment_1_a.sh"
#define DATABASE_CSV_FILE_NAME "database.csv"

struct Block
{
    string hash;
    long height;
    long long total;
    string time;
    string relayed_by;
    string prev_block;
};

static void printBlock(const Block &block)
{
    cout << "hash: " << block.hash << endl;
    cout << "height: " << block.height << endl;
    cout << "total: " << block.total << endl;
    cout << "time: " << block.time << endl;
    cout << "relayed_by: " << block.relayed_by << endl;
    cout << "prev_block: " << block.prev_block << endl;
}

static bool printdb(string DB_fileName) // function number 1
{
    bool success = false;

    ifstream file(DATABASE_CSV_FILE_NAME);
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
    }
    else
    {
        string line;
        getline(file, line); // Skip header

        vector<Block> blocks;

        while (getline(file, line))
        {
            stringstream ss(line);
            Block b;
            string temp;

            getline(ss, b.hash, ',');
            getline(ss, temp, ',');
            b.height = stoi(temp);
            getline(ss, temp, ',');
            b.total = stoll(temp);
            getline(ss, b.time, ',');
            getline(ss, b.relayed_by, ',');
            getline(ss, b.prev_block, ',');

            blocks.push_back(b);
        }

        for (int i = 0; i < blocks.size(); ++i)
        {
            printBlock(blocks[i]);

            if (i != blocks.size() - 1)
            {
                // Only print the arrow if it's NOT the last block
                cout << "                        |" << endl;
                cout << "                        |" << endl;
                cout << "                        |" << endl;
                cout << "                        V" << endl;
            }
        }

        success = true;
    }

    return success;
}

int main()
{
    printdb(DATABASE_CSV_FILE_NAME);
    
    return 0;
}