#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define GET_BLOCKCHAIN_BASH_FILE_PATH "/home/roy/myRepos/UNI-INTRO-TO-LINUX-DEV-ex1/assignment_1_a.sh"
#define DB_CSV_FILE_NAME "res.csv"

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

    static bool refreshData(string BashScriptFilePath)
    {
        string input;
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

                if (pos != input.length()) {
                    throw invalid_argument("Extra characters found");
                }

                if (numOfBlocksToGet == -1) {
                    return false;
                }

                if (numOfBlocksToGet < 1 || numOfBlocksToGet > 50) {
                    cout << "Please enter a number between 1 and 50." << endl;
                    continue;
                }

                // Valid number - run script
                string command = "bash " + BashScriptFilePath + " " + to_string(numOfBlocksToGet);
                system(command.c_str());
                return true;
            }
            catch (const invalid_argument&) {
                cout << "Invalid input! Not a number." << endl;
            }
            catch (const out_of_range&) {
                cout << "Input number is too large!" << endl;
            }
        }

        return false; // not reached normally
    }

    static bool printDB(string DB_fileName)
    {
        bool success = false;

        ifstream file("res.csv");
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

};

int main()
{
    // string DB_fileNmae = "res.csv";
    // string bashFilePath = "/home/roy/myRepos/UNI-INTRO-TO-LINUX-DEV-ex1/assignment_1_a.sh";
    
    BlockChain::printDB(DB_CSV_FILE_NAME);
    BlockChain::refreshData(GET_BLOCKCHAIN_BASH_FILE_PATH);
    BlockChain::printDB(DB_CSV_FILE_NAME);

    return 0;
}