#include "blockchain_utils.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>

bool openDatabaseCSV(std::ifstream &file, const std::string &filename)
{
    file.open(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    return true;
}

std::vector<Block> parseBlocksFromCSV(std::ifstream &file)
{
    std::vector<Block> db;
    std::string line;
    // Skip header line
    if (!std::getline(file, line))
        return db;

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        Block b;
        std::string tmp;
        std::getline(ss, b.hash, ',');
        std::getline(ss, tmp, ',');
        b.height = std::stol(tmp);
        std::getline(ss, tmp, ',');
        b.total = std::stoll(tmp);
        std::getline(ss, b.time, ',');
        std::getline(ss, b.relayed_by, ',');
        std::getline(ss, b.prev_block, ',');
        db.push_back(b);
    }
    return db;
}

void printBlock(const Block &b)
{
    std::cout << "hash: " << b.hash << std::endl;
    std::cout << "height: " << b.height << std::endl;
    std::cout << "total: " << b.total << std::endl;
    std::cout << "time: " << b.time << std::endl;
    std::cout << "relayed_by: " << b.relayed_by << std::endl;
    std::cout << "prev_block: " << b.prev_block << std::endl;
}

void printChain(const std::vector<Block> &db)
{
    for (size_t i = 0; i < db.size(); ++i)
    {
        printBlock(db[i]);
        if (i + 1 < db.size())
        {
            std::cout << "                        |" << std::endl;
            std::cout << "                        |" << std::endl;
            std::cout << "                        |" << std::endl;
            std::cout << "                        V" << std::endl;
        }
    }
}