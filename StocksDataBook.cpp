#include "StocksDataBook.h"
#include "CSVFileReader.h"
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <chrono>

/** Parse the CSV file and convert valid lines into SDBEs
 *
 *  @param filename Name of CSV file
 *
 */
StocksDataBook::StocksDataBook(std::string filename)
{
    // Convert valid lines into SDBEs
    SDBEcollection = CSVFileReader::readCSVfile(filename);
}

/** Return all unique products in the dataset
 *
 *  @return container of unique products
 *
 */
std::vector<std::string> StocksDataBook::getUniqueProducts()
{
    // Executes given that unique products have not been cached
    if (uniqueProducts.empty())
    {
        // Store unique products
        std::unordered_set<std::string> prodUnorderedSet;

        // Insert all products
        for (StocksDataBookEntry& SDBEentry : SDBEcollection)
        {
            prodUnorderedSet.insert(SDBEentry.product);
        }

        // Flatten unordered set into vector
        std::vector<std::string> products(prodUnorderedSet.begin(), prodUnorderedSet.end());

        // Cache the set of unique products to avoid redundant calls
        uniqueProducts = products;

        return products;
    }

    // Return cached products
    return uniqueProducts;
}

/** Return SDBEs according to the filter parameters
 *
 *  @param type      SDBE type - ask/bid/unknown
 *  @param product   Product name
 *  @param timestamp Current timestamp of simulation
 *  @return          container of filtered SDBE entries from dataset
 *
 */
std::vector<StocksDataBookEntry> StocksDataBook::filterSDBEentries(StocksDataBookType type,
                                                                   std::string product,
                                                                   std::string timestamp)
{
    // Filtered subset of the SDBE entries from dataset
    std::vector<StocksDataBookEntry> filteredSDBEs;

    // Iterate through SDBE entries in dataset for comparison with filters
    for (int i = 0; i < SDBEcollection.size(); ++i)
    {
        // SDBE matches the filter parameters
        if (SDBEcollection[i].SDBEtype == type && SDBEcollection[i].product == product && SDBEcollection[i].timestamp == timestamp)
        {
            filteredSDBEs.push_back(SDBEcollection[i]);
        }
    }
    return filteredSDBEs;
}

/** Return the maximum and minimum price within SDBE collection
 *
 *  @param SDBEcollection Collection of SDBE entries
 *  @return               pair containing maximum and minimum price within container
 *
 */
struct MinMaxPair StocksDataBook::getMinMaxPrice(std::vector<StocksDataBookEntry>& SDBEcollection)
{
    // Number of SDBE entries in the SDBE collection
    int containerSize = SDBEcollection.size();

    // Pair containing minimum and maximum data members
    struct MinMaxPair minMaxPair;

    // Current position within the SDBE collection
    int containerIndex;

    // Initialize of minimum and maximum values for an even-length container of SDBE entries
    if (containerSize % 2 == 0)
    {
        // Case 1: First entry is greater than second entry
        if (SDBEcollection[0].price > SDBEcollection[1].price)
        {
            // Set maximum to first entry and minimum to second entry
            minMaxPair.max = SDBEcollection[0].price;
            minMaxPair.min = SDBEcollection[1].price;
        }

        // Case 2: First entry is smaller than second entry
        else
        {
            // Initialize maximum to second entry and minimum to first entry
            minMaxPair.min = SDBEcollection[0].price;
            minMaxPair.max = SDBEcollection[1].price;
        }

        // Set the starting position of comparisons for the SDBE container entries
        containerIndex = 2;
    }

    // Initialize of minimum and maximum values for an odd-length container of SDBE entries
    else
    {
        // Set maximum and minimum to first entry in container
        minMaxPair.min = SDBEcollection[0].price;
        minMaxPair.max = SDBEcollection[0].price;

        // Set the starting position of comparisons for the SDBE container entries
        containerIndex = 1;
    }

    // Iterate through each SDBE entry in the collection and compare pairs with current maximum and minimum
    while (containerIndex < containerSize - 1)
    {
        // Case 1: First element in pair has a higher price than the second element in pair
        if (SDBEcollection[containerIndex].price > SDBEcollection[containerIndex + 1].price)
        {
            // Compare and update maximum price against first element in pair
            if (SDBEcollection[containerIndex].price > minMaxPair.max)
            {
                minMaxPair.max = SDBEcollection[containerIndex].price;
            }

            // Compare and update minimum price against second element in pair
            if (SDBEcollection[containerIndex + 1].price < minMaxPair.min)
            {
                minMaxPair.min = SDBEcollection[containerIndex + 1].price;
            }
        }

        // Case 2: Second element in pair has a higher price than the first element in pair
        else
        {
            // Compare and update maximum price against second element in pair
            if (SDBEcollection[containerIndex + 1].price > minMaxPair.max)
            {
                minMaxPair.max = SDBEcollection[containerIndex + 1].price;
            }

            // Compare and update minimum price against first element in pair
            if (SDBEcollection[containerIndex].price < minMaxPair.min)
            {
                minMaxPair.min = SDBEcollection[containerIndex].price;
            }
        }

        // Advance to the next pair for comparison
        containerIndex += 2;
    }

    // Return structure containing maximum and minimum prices from container of SDBE entries
    return minMaxPair;
}

/** Return the initial timestamp in the StocksDataBook
 *
 *  @return earliest timestamp in dataset
 *
 */
std::string StocksDataBook::getEarliestTimeStamp()
{
    return SDBEcollection[0].timestamp;
}

/** Return the next timestamp after the timestamp passed in, in a circular manner
 *
 *  @param timestamp Timestamp to serve as a frame of reference
 *  @return          next timestamp in dataset
 *
 */
std::string StocksDataBook::getNextTimeStamp(std::string timestamp)
{
    // Position of upper bound, the next timestamp
    signed int upperBoundTimeStamp = -1;

    // Beginning and end timestamp markers that determine the search space
    unsigned int startTimeStamp = 0;
    unsigned int endTimeStamp = SDBEcollection.size();

    // The collection of SDBE entries is empty
    if (endTimeStamp == 0)
    {
        return "Invalid StocksDataBook";
    }

    /* Case in which reference timestamp is the latest timestamp
    Return initial timestamp to maintain a circular SDB */
    if (timestamp == SDBEcollection[endTimeStamp - 1].timestamp)
    {
        std::cout << SDBEcollection[0].timestamp << std::endl;
        return SDBEcollection[0].timestamp;
    }

    // Compute upper bound of reference timestamp via a modified binary search
    while (startTimeStamp <= endTimeStamp)
    {
        // Determine midpoint timestamp, avoiding integer overflow
        int midTimeStamp = startTimeStamp + (endTimeStamp - startTimeStamp) / 2;

        // Prefetch the two possible midpoints of the next loop iteration in the current iteration

        // Prefetch low path
        __builtin_prefetch(&SDBEcollection[(midTimeStamp + 1 + endTimeStamp) / 2], 0, 1);

        // Prefetch high path
        __builtin_prefetch(&SDBEcollection[(startTimeStamp + midTimeStamp - 1) / 2], 0, 1);

        // Reduce search space to the right half of timestamp collection
        if (SDBEcollection[midTimeStamp].timestamp <= timestamp)
            startTimeStamp = midTimeStamp + 1;

        // Reduce search space to the left half of timestamp collection
        else
        {
            // Record upper bound position
            upperBoundTimeStamp = midTimeStamp;
            endTimeStamp = midTimeStamp - 1;
        }
    }
    // Next timestamp occurs at position of lower bound
    std::string nextTimestamp = SDBEcollection[upperBoundTimeStamp].timestamp;
    return nextTimestamp;
}

/** Return the timestamp before the timestamp passed in, in a circular manner
*
*   @param timestamp Timestamp to serve as a frame of reference
*   @return          previous timestamp in dataset
*
*/
std::string StocksDataBook::getPreviousTimeStamp(std::string timestamp)
{
    // Position of lower bound, the previous timestamp
    signed int lowerBoundTimeStamp = -1;

    // Beginning and end timestamp markers that determine the search space
    unsigned int startTimeStamp = 0;
    unsigned int endTimeStamp = SDBEcollection.size();

    // The collection of SDBE entries is empty
    if (endTimeStamp == 0)
    {
        return "Invalid StocksDataBook";
    }

    /* Case in which reference timestamp is the earliest timestamp
    Return latest timestamp to maintain a circular SDB */
    if (timestamp == SDBEcollection[0].timestamp)
    {
        return SDBEcollection[endTimeStamp - 1].timestamp;
    }

    // Compute lower bound of reference timestamp via a modified binary search
    while (startTimeStamp <= endTimeStamp)
    {
        // Determine midpoint timestamp, avoiding integer overflow
        int midTimeStamp = startTimeStamp + (endTimeStamp - startTimeStamp) / 2;

        // Prefetch the two possible midpoints of the next loop iteration in the current iteration

        // Prefetch low path
        __builtin_prefetch(&SDBEcollection[(midTimeStamp + 1 + endTimeStamp) / 2], 0, 1);

        // Prefetch high path
        __builtin_prefetch(&SDBEcollection[(startTimeStamp + midTimeStamp - 1) / 2], 0, 1);

        // Reduce search space to the left half of timestamp collection
        if ((SDBEcollection[midTimeStamp].timestamp) >= timestamp)
        {
            endTimeStamp = midTimeStamp - 1;
        }

        // Reduce search space to the right half of timestamp collection
        else
        {
            // Record lower bound position
            lowerBoundTimeStamp = midTimeStamp;
            startTimeStamp = midTimeStamp + 1;
        }
    }
    // Previous timestamp occurs at position of lower bound
    std::string previousTimestamp = SDBEcollection[lowerBoundTimeStamp].timestamp;
    return previousTimestamp;
}