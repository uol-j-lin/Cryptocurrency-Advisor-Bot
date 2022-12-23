#include "StocksDataBookEntry.h"

/** Initialize the fields of a baseline SDBE in the dataset
 *
 *  @param _price Entry price
 *  @param _amount Entry amount
 *  @param _timestamp Current timestamp in simulation
 *  @param _product Product name
 *  @param _SDBEtype SDBE type - ask/bid/unknown
 * 
 */
StocksDataBookEntry::StocksDataBookEntry(double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    StocksDataBookType _SDBEtype)
    : price(_price),
    amount(_amount),
    timestamp(_timestamp),
    product(_product),
    SDBEtype(_SDBEtype)
{ 
}

/** Convert a string to a StocksDataBookType (SDBT)
 *
 *  @param inputString String to be matched against an enumeration constant
 *  @return enumerator representing the StocksDataBookType
 *
 */
StocksDataBookType StocksDataBookEntry::stringToStocksDataBookType(std::string inputString)
{
    // Match input string to ask 
    if (inputString == "ask")
    {
        // Return ask enumerator
        return StocksDataBookType::ask;
    }

    // Match input string to bid
    if (inputString == "bid")
    {
        // Return bid enumerator
        return StocksDataBookType::bid;
    }

    // Unrecognized SDBE type, return unknown enumerator
    return StocksDataBookType::unknown;
}