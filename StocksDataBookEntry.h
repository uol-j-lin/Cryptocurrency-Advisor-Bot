#pragma once

#include <string>

/** Establish valid SDBE types */
enum class StocksDataBookType
{
    bid,
    ask,
    unknown
};

class StocksDataBookEntry
{
public:
    /** Initialize the fields of a baseline SDBE in the dataset */
    StocksDataBookEntry(double _price,
                        double _amount,
                        std::string _timestamp,
                        std::string _product,
                        StocksDataBookType _SDBEtype);

    /** Convert a string to an SDBT */
    static StocksDataBookType stringToStocksDataBookType(std::string inputString);

    // Parameters for each SDBE
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    StocksDataBookType SDBEtype;
};