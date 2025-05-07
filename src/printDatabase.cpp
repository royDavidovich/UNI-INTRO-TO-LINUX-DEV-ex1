#include "blockchain_utils.h"

#include <fstream>

constexpr const char *DATABASE_FILE = "../database.csv";

int main()
{
    std::ifstream file;
    if (!openDatabaseCSV(file, DATABASE_FILE))
    {
        return 1;
    }

    std::vector<Block> db = parseBlocksFromCSV(file);
    printChain(db);
    return 0;
}