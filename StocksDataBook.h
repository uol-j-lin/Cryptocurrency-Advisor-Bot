#pragma once

#include "StocksDataBookEntry.h"
#include "CSVFileReader.h"
#include <string>
#include <vector>

/** Structure is used to return two values from getMinMaxPrice() */
struct MinMaxPair
{
    // Minimum and maximum price
    double min;
    double max;
};

class StocksDataBook
{
public:
    /** Parse the CSV file and convert valid lines into SDBEs */
    StocksDataBook(std::string filename);

    /** Return all unique products in the dataset */
    std::vector<std::string> getUniqueProducts();

    /** Return SDBEs according to the filter parameters */
    std::vector<StocksDataBookEntry> filterSDBEentries(StocksDataBookType type,
                                                  std::string product,
                                                  std::string timestamp);

    /** Return the maximum and minimum price within SDBE collection */
    MinMaxPair getMinMaxPrice(std::vector<StocksDataBookEntry>& SDBEcollection);

    /** Return the initial timestamp in the StocksDataBook */
    std::string getEarliestTimeStamp();

    /** Return the next timestamp after the timestamp passed in, in a circular manner */
    std::string getNextTimeStamp(std::string timestamp);

    /** Return the timestamp before the timestamp passed in, in a circular manner */
    std::string getPreviousTimeStamp(std::string timestamp);

private:
    /** Collection of SDBE entries */
    std::vector<StocksDataBookEntry> SDBEcollection;

    /** All unique products in the dataset */
    std::vector<std::string> uniqueProducts;
};