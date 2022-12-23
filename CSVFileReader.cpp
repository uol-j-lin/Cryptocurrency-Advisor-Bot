#include "CSVFileReader.h"
#include <iostream>
#include <fstream>
#include <algorithm>

/** Initialize an instance of the CSV File Reader class */
CSVFileReader::CSVFileReader() = default;

/** Parse the CSV file and convert valid lines into SDBEs
 *
 *  @param csvFilename The name of the CSV file to be parsed
 *  @return            container of SDBE objects constructed from each valid line of the CSV file
 * 
 */
std::vector<StocksDataBookEntry> CSVFileReader::readCSVfile(std::string csvFilename)
{
    // Storage for valid SDBE entries 
    std::vector<StocksDataBookEntry> entries;

    // Request the vector capacity in advanced to prevent excessive memory allocations
    entries.reserve(1022000);

    // Create object associated with the CSV file to perform input/output operations on
    std::ifstream csvFile{ csvFilename };

    // Ensure CSV file is open, and associated with the stream object
    std::string line;

    if (csvFile.is_open())
    {
        // Continue processing line by line as end of file has not been reached 
        while (std::getline(csvFile, line))
        {
            // Attempt to process the CSV line 
            try
            {
                // Split line into tokens based on comma delimiter 
                std::vector<std::string> tokenizedCSVLine = tokenize(line, ',');

                // Insert the SDBE into the storage collection
                if (tokenizedCSVLine.size() == 5)
                {
                    // Implicitly call the StocksDataBookEntry's parameterized constructor
                    entries.emplace_back(std::stod(tokenizedCSVLine[3]), 
                                         std::stod(tokenizedCSVLine[4]), 
                                         tokenizedCSVLine[0], 
                                         tokenizedCSVLine[1], 
                                         StocksDataBookEntry::stringToStocksDataBookType(tokenizedCSVLine[2]));
                }
            }
            // Unsuccessful string to SDBE conversion 
            catch (const std::exception& e)
            {
                std::cout << "CSV File Reader parsed an invalid CSV line.\n";
            }
        }
    }
    // Indicate the number of valid string to SDBE conversions across the entire file 
    std::cout << "CSV File Reader has successfully processed " << entries.size() << " entries\n";
    return entries;
}

/** Split a CSV line into tokens based on a delimiter
 *
 *  @param csvLine    The CSV line to be parsed
 *  @param separator  The delimiter that separates tokens
 *  @return container containing parsed tokens of a CSV line
 *
 */
std::vector<std::string> CSVFileReader::tokenize(std::string csvLine, char separator)
{
    // Storage for parsed tokens
    std::vector<std::string> tokens;

    // Index of start of string
    signed int start = 0;

    // Index of first occurrence of delimiter
    signed int end = csvLine.find_first_of(separator);

    while (end <= std::string::npos)
    {
        // Insert substring between delimiter occurrences
        tokens.emplace_back(csvLine.substr(start, end - start));

        // End of string reached
        if (end == std::string::npos)
        {
            break;
        }
        // Adjust start of next substring to be just beyond last delimiter occurrence
        start = end + 1;

        // Find next occurrence of delimiter
        end = csvLine.find_first_of(separator, start);
    }
    return tokens;
}

/** Convert a string into an SDBE based on the input parameters
 *                                                              
 *  @param tokens String of tokens
 *  @return       StocksDataBookEntry generated using tokens as arguments
 *                  
 */
StocksDataBookEntry CSVFileReader::stringsToSDBE(std::vector<std::string> tokens)
{
    // Tokens that must undergo type conversions before SDBE instantiation
    double price;
    double amount;
    
    // Validate that the number of tokens matches the SDBE parameters
    if (tokens.size() != 5) 
    {
        std::cout << "Bad line \n";
        throw std::exception{};
    }
    try
    {   
        // Convert tokens into price and amount doubles to represent SDBE parameters
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception& e)
    {
        // Unsuccessful string to double conversion
        std::cout << "Unsuccessful conversion from string to double for CSV line - " << tokens[3] << ", " << tokens[4] << "\n";
        throw;
    }

    // Instantiate SDBE with input parameters
    StocksDataBookEntry obe{price,
                            amount,
                            tokens[0],
                            tokens[1],
                            StocksDataBookEntry::stringToStocksDataBookType(tokens[2])};

    return obe;
}

/** Convert a string into an SDBE based on its number of tokens and data types
 *
 *  @param priceString  Price of SDBE 
 *  @param amountString Amount of SDBE
 *  @param timestamp    Timestamp of SDBE
 *  @param product      Product of SDBE
 *  @param SDBEtype     Ask/Bid/Unknown
 *  @return             StocksDataBookEntry generated using parameters as arguments
 *
 */
StocksDataBookEntry CSVFileReader::stringsToSDBE(std::string priceString,
    std::string amountString,
    std::string timestamp,
    std::string product,
    StocksDataBookType SDBEtype)
{
    // Tokens that must undergo type conversions before SDBE instantiation
    double price;
    double amount;
    try
    {
        // Convert tokens into price and amount doubles to represent SDBE parameters
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception& e)
    {
        // Unsuccessful string to double conversion
        std::cout << "CSVFileReader::stringsToSDBE Bad float! " << priceString << "\n";
        std::cout << "CSVFileReader::stringsToSDBE Bad float! " << amountString << "\n";
        throw;
    }

    // Instantiate SDBE with input parameters
    StocksDataBookEntry obe{ price,
                       amount,
                       timestamp,
                       product,
                       SDBEtype };

    return obe;
}