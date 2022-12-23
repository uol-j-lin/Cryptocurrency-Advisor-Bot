#pragma once

#include "StocksDataBookEntry.h"
#include "StocksDataBook.h"
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>
#include "CSVFileReader.h"


class AdvisorBot
{
public:
    /** Initialize an instance of the Advisor Bot class */
    AdvisorBot();

    /** Prompt the user for input - validate and process the input and execute corresponding command */
    void init();

    /** Current simulation timestamp */
    std::string currentTime;

    /** Instantiate an SDBE with the CSV file name to be parsed */
    StocksDataBook stocksDataBook{ "20200601.csv" };

private:
    /** Inform the user of how to interact with AdvisorBot */
    void promptUser();

    /** Get input from user and echo back the user's typed command */
    std::string getUserCommand();

    /** Sanitize user command by accounting for excess whitespace */
    void sanitizeUserCommand(std::string& userCommand);

    /** Execute the command corresponding to the user input */
    void processUserCommand(std::string userCommand);

    /** Map user input to command execution */
    void mapUserInputToCommand();

    /** Command map that maps a single user token to a command's static function pointer */
    std::map<std::string, std::function<void()>> singleTokenCommandMap;

    /** Command map that maps two user tokens to a command's static function pointer */
    std::map<std::string, std::function<void()>> twoTokenCommandMap;

    /** Command map that maps three user tokens to a command's static function pointer */
    std::map<std::string, std::function<double(std::string, std::string, std::string)>> threeTokenCommandMap;

    /** Command map that maps four user tokens to a command's static function pointer */
    std::map <std::string, std::function<double(std::string, std::string, std::string, std::string)>> fourTokenCommandMap;
};