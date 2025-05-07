#ifndef BLOCKCHAIN_UTILS_H
#define BLOCKCHAIN_UTILS_H

#include <string>
#include <vector>
#include <fstream>

struct Block
{
    std::string hash;
    long height;
    long long total;
    std::string time;
    std::string relayed_by;
    std::string prev_block;
};

// Open the CSV database; returns true if file opened
bool openDatabaseCSV(std::ifstream &file, const std::string &filename);

// Parse all blocks from CSV into a vector
std::vector<Block> parseBlocksFromCSV(std::ifstream &file);

// Print a single block
void printBlock(const Block &b);

// Print the entire blockchain (chain of blocks)
void printChain(const std::vector<Block> &db);

#endif // BLOCKCHAIN_UTILS_H
