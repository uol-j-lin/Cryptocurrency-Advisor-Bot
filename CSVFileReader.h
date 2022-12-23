#pragma once

#include "StocksDataBookEntry.h"
#include <vector>
#include <unordered_map>
#include <string>

class CSVFileReader
{
public:
    /** Initialize an instance of the CSV File Reader class */
    CSVFileReader();

    /** Parse the CSV file and convert valid lines into SDBEs */
    static std::vector<StocksDataBookEntry> readCSVfile(std::string csvFile);

    /** Split a CSV line into tokens based on a delimiter */
    static std::vector<std::string> tokenize(std::string csvLine, char separator);

    /** Convert a string into an SDBE based on the input parameters */
    static StocksDataBookEntry stringsToSDBE(std::string price,
                                            std::string amount,
                                            std::string timestamp,
                                            std::string product,
                                            StocksDataBookType StocksDataBookType);

private:
    /** @overload static StocksDataBookEntry stringsToSDBE(std::vector<std::string> tokens)
     * 
     *  Convert a string into an SDBE based on its number of tokens and data types
     */
    static StocksDataBookEntry stringsToSDBE(std::vector<std::string> tokens);
};