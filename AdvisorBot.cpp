#include "AdvisorBot.h"
#include "UserCommands.h"
#include <regex>

/** Initialize an instance of the Advisor Bot class */
AdvisorBot::AdvisorBot() = default;

/** Prompt the user for input - validate and process the input and execute corresponding command */
void AdvisorBot::init()
{
    std::string userInput;

    UserCommands userCommands;

    // Begin simulation at earliest timestamp
    currentTime = stocksDataBook.getEarliestTimeStamp();

    // Continually process and validate user commands
    while (true)
    {
        // Inform the user of how to interact with the simulation
        promptUser();

        // Map each user input string to a command to execute
        mapUserInputToCommand();

        // Obtain input from the user
        userInput = getUserCommand();

        // Sanitize the input by removing excess whitespace characters
        sanitizeUserCommand(userInput);
        try
        {
            // Execute a command based on string to command mapping
            processUserCommand(userInput);
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception caught: The program will now continue..." << std::endl;
        }
    }
}

/** Inform the user of how to interact with AdvisorBot */
void AdvisorBot::promptUser()
{
    std::cout << "\nEnter a command, or type \"help\" to view all commands" << std::endl;
}

/** Get input from user and echo back the user's typed command 
 *
 *  @return user-inputted command to be echoed back
 * 
 */
std::string AdvisorBot::getUserCommand()
{
    std::string userCommand;

    // Get user input
    std::getline(std::cin, userCommand);

    return userCommand;
}

/** Sanitize user command by accounting for excess whitespace 
 *
 *  @param userCommand Command entered by user to be sanitized
 * 
 */
void AdvisorBot::sanitizeUserCommand(std::string& userCommand)
{
    // Remove leading, trailing, and extra spaces from the user command
    userCommand = std::regex_replace(userCommand, std::regex("^ +| +$|( ) +"), "$1");
}

/** Map user input to command execution */
void AdvisorBot::mapUserInputToCommand()
{
    // Populate single token command map with user inputs mapped to static function pointers representing commands 

    singleTokenCommandMap["help"] = [this]() { UserCommands::Command1_HELP(); };
    singleTokenCommandMap["prod"] = [this]() { UserCommands::Command3_PROD(this); };
    singleTokenCommandMap["time"] = [this]() { UserCommands::Command8_TIME(this); };
    singleTokenCommandMap["step"] = [this]() { UserCommands::Command9_STEP(this); };

    // Populate two token command map with user inputs mapped to static function pointers representing commands 

    twoTokenCommandMap["helpprod"] = [this]() { UserCommands::Command2_HELP_prod();  };
    twoTokenCommandMap["helpmin"] = [this]() { UserCommands::Command2_HELP_min();  };
    twoTokenCommandMap["helpmax"] = [this]() { UserCommands::Command2_HELP_max();  };
    twoTokenCommandMap["helpavg"] = [this]() { UserCommands::Command2_HELP_avg();  };
    twoTokenCommandMap["helppredict"] = [this]() { UserCommands::Command2_HELP_predict();  };
    twoTokenCommandMap["helptime"] = [this]() { UserCommands::Command2_HELP_time();  };
    twoTokenCommandMap["helpstep"] = [this]() { UserCommands::Command2_HELP_step();  };
    twoTokenCommandMap["helpmedian"] = [this]() { UserCommands::Command2_HELP_median();  };

    // Populate three token command map with user inputs mapped to static function pointers representing commands 

    threeTokenCommandMap["min"] = [this](std::string SDBEtype, std::string product, std::string currentTime) { return UserCommands::Command4_MIN(SDBEtype, product, currentTime, this); };
    threeTokenCommandMap["max"] = [this](std::string SDBEtype, std::string product, std::string currentTime) { return UserCommands::Command5_MAX(SDBEtype, product, currentTime, this); };

    // Populate four token command map with user inputs mapped to static function pointers representing commands 

    fourTokenCommandMap["avg"] = [this](std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps) { return UserCommands::Command6_AVG(SDBEtype, product, currentTime, numTimesteps, this); };
    fourTokenCommandMap["median"] = [this](std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps) { return UserCommands::Command10_MEDIAN(SDBEtype, product, currentTime, numTimesteps, this); };
    fourTokenCommandMap["predict"] = [this](std::string product, std::string maxOrMin, std::string currentTime, std::string SDBEtype) { return UserCommands::Command7_PREDICT(product, maxOrMin, currentTime, SDBEtype, this); };
}

/** Determine a command's validity based on token contents and quantity
 *
 *  @param userCommand User-entered command
 *
 */
void AdvisorBot::processUserCommand(std::string userCommand)
{
    // Tokenize user input based on whitespace delimiter
    std::vector<std::string> tokens = CSVFileReader::tokenize(userCommand, ' ');

    // Determine if the token quantity falls outside the valid command range
    if (tokens.size() < 1 || tokens.size() > 4)
    {
        std::cout << "Too few or too many tokens detected" << std::endl;
        throw std::exception{};
    }

    // Number of user-inputted tokens parsed
    int numTokens = tokens.size();

    // Execute command based on token quantity
    switch (numTokens)
    {

    // Process single token user command
    case 1:
        // Execute single token command using command map given that it is recognized
        try
        {
            singleTokenCommandMap[tokens[0]]();
        }
        catch (const std::exception& e)
        {
            // Single token command does not belong to the recognized command list
            std::cout << "Unrecognized single token command" << std::endl;
            throw std::exception{};
        }
        break;
    // Process two token user command
    case 2:
        // Execute two token command using command map given that it is recognized
        try
        {
            twoTokenCommandMap[tokens[0] + tokens[1]]();
        }
        catch (const std::exception& e)
        {
            // Two token command does not belong to the recognized command list
            std::cout << "Unrecognized two token command" << std::endl;
            throw std::exception{};
        }
        break;

    // Process three token user command
    case 3:
        // Execute three token command using command map given that it is recognized
        try
        {
            threeTokenCommandMap[tokens[0]](tokens[2], tokens[1], currentTime);
        }
        catch (const std::exception& e)
        {
            // Three token command does not belong to the recognized command list
            std::cout << "Unrecognized three token command" << std::endl;
            throw std::exception{};
        }
        break;
    // Process four token user command
    case 4:
        // Execute four token command using command map given that it is recognized
        try
        {
            // Retrieve PREDICT, MEDIAN, or AVG function from map and execute it with ordered user arguments
            fourTokenCommandMap[tokens[0]](tokens[2], tokens[1], currentTime, tokens[3]);
        }
        catch (const std::exception& e)
        {
            // Four token command does not belong to the recognized command list
            std::cout << "Unrecognized four token command" << std::endl;
            throw std::exception{};
        }
        break;
    }
}