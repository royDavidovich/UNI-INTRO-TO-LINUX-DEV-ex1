#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define BLOCKCHAIN_BASH_FILE_PATH "./assignment_1_a.sh"
// #define DB_CSV_FILE_NAME "res.csv"
#define DATABASE_CSV_FILE_NAME "database.csv"

class BlockChain
{
    struct Block
    {
        string hash;
        long height;
        long long total;
        string time;
        string relayed_by;
        string prev_block;
    };

    static void printBlock(const Block& block)
    {
        cout << "hash: " << block.hash << endl;
        cout << "height: " << block.height << endl;
        cout << "total: " << block.total << endl;
        cout << "time: " << block.time << endl;
        cout << "relayed_by: " << block.relayed_by << endl;
        cout << "prev_block: " << block.prev_block << endl;
    }

public:
    static void mainManu()
    {
        // here we run the main manu commands from
    }

    static bool refreshData(string BashScriptFilePath)      //function numbers 3 and 4
    {
        string input = "";
        int numOfBlocksToGet;

        while (true)
        {
            cout << "Please enter how many blocks you want to get from the Block-Chain" << endl;
            cout << "Enter a number (or -1 to exit): ";
            getline(cin, input);

            try
            {
                size_t pos = 0;
                numOfBlocksToGet = stoi(input, &pos);

                if (pos != input.length())
                {
                    throw invalid_argument("Extra characters found");
                }
                else if (numOfBlocksToGet == -1)
                {
                    return false;
                }
                else if (numOfBlocksToGet < 1 || numOfBlocksToGet > 50)
                {
                    cout << "Please enter a number between 1 and 50." << endl;
                    continue;
                }

                // Valid number - run script
                string command = "bash " + BashScriptFilePath + " " + to_string(numOfBlocksToGet);
                system(command.c_str());
                return true;
            }
            catch (const invalid_argument&)
            {
                cout << "Invalid input! Not a number." << endl;
            }
        }

        return false; // not reached normally
    }

    static bool printdb(string DB_fileName)     //function number 1
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
            getline(file, line);    // Skip header

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
            
                if (i != blocks.size() - 1) {
                    // Only print the arrow if it's NOT the last block
                    cout << "    |" << endl;
                    cout << "    |" << endl;
                    cout << "    V" << endl;
                }
            }
            
            success = true;
        }

        return success;
    }

    static bool FindBlockInDataBaseByHash(string DB_fileName)
    {
        bool success = false;
        string hashToFetch = "";

        cout << "Please enter hash adress you want to get from our Block-Chain database: " << endl;
        cout << "Or enter -1 to exit: ";
        getline(cin, hashToFetch);

        while (true)
        {
            if (hashToFetch.length() != 64)
            {
                cout << "Please enter a valid hash address: ";
                getline(cin, hashToFetch);
                continue;
            }
            else
            {
                break;
            }
        }
        
        // Valid hash - run script
        ifstream file(DB_fileName);
        if (!file.is_open())
        {
            cerr << "Error opening file!" << endl;
        }
        else
        {
            string line;
            getline(file, line);    // Skip header

            Block b;
            string temp;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, b.hash, ',');
                if (b.hash == hashToFetch)
                {
                    getline(ss, temp, ','); 
                    b.height = stoi(temp);
                    getline(ss, temp, ','); 
                    b.total = stoll(temp);
                    getline(ss, b.time, ',');
                    getline(ss, b.relayed_by, ',');
                    getline(ss, b.prev_block, ',');
                    
                    cout << "Printing block with hash: " << hashToFetch << endl;
                    printBlock(b);
                    success = true;
                    break;
                }
            }

            if (success != true)
            {
                cout << "Block with hash: " << hashToFetch << " was not found in the local database." << endl;
                cout << "Please run refresh database first." << endl;
            }
        }

        return success;
    }

    static bool FindBlockInDataBaseByHeight(string DB_fileName)
    {
        string input = "";
        long heightToFetch = 0;
        bool success = false;

        while (!success)
        {
            cout << "Please enter the block's height you want to get from our Block-Chain database: " << endl;
            cout << "Or enter -1 to exit: ";
            getline(cin, input);

            try
            {
                size_t pos = 0;
                heightToFetch = stol(input, &pos);

                if (pos != input.length())
                {
                    throw invalid_argument("Extra characters found");
                }
                else if (heightToFetch == -1)
                {
                    success = false;
                    break;
                }
                else if (heightToFetch < 1)
                {
                    cout << "Please enter a valid number." << endl;
                    continue;
                }

                // Valid number - run script
                success = true;
            }
            catch (const invalid_argument&)
            {
                cout << "Invalid input! Not a number." << endl;
            }
        }
        
        // Valid height - run script
        success = false;
        ifstream file(DB_fileName);
        if (!file.is_open())
        {
            cerr << "Error opening file!" << endl;
        }
        else
        {
            string line;
            getline(file, line);    // Skip header

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


};

int main()
{
    //BlockChain::printdb(DB_CSV_FILE_NAME);
    // BlockChain::refreshData(GET_BLOCKCHAIN_BASH_FILE_PATH);
    BlockChain::FindBlockInDataBaseByHash(BLOCKCHAIN_BASH_FILE_PATH);
    BlockChain::FindBlockInDataBaseByHeight(BLOCKCHAIN_BASH_FILE_PATH);
    //BlockChain::printdb(DB_CSV_FILE_NAME);

    return 0;
}