#pragma once

#include "StocksDataBookEntry.h"
#include "StocksDataBook.h"
#include "CSVFileReader.h"
#include "AdvisorBot.h"
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>

/** Establish max or min types */
enum class MaxMinType
{
    max,
    min,
    unknown
};


class UserCommands
{
public:
    /** Initialize an instance of the User Commands class */
    UserCommands();

    /** Command 1: HELP - List all available commands */
    static void Command1_HELP();

    /** Command 2: HELP PROD - output help for the prod command */
    static void Command2_HELP_prod();

    /** Command 2: HELP MIN - output help for the min command */
    static void Command2_HELP_min();

    /** Command 2: HELP MAX - output help for the max command */
    static void Command2_HELP_max();

    /** Command 2: HELP AVG - output help for the avg command */
    static void Command2_HELP_avg();

    /** Command 2: HELP PREDICT - output help for the predict command */
    static void Command2_HELP_predict();

    /** Command 2: HELP TIME - output help for the time command */
    static void Command2_HELP_time();

    /** Command 2: HELP STEP - output help for the step command */
    static void Command2_HELP_step();

    /** Command 2: HELP MEDIAN - output help for the median command */
    static void Command2_HELP_median();

    /** Command 3: PROD - list available products in the dataset */
    static void Command3_PROD(AdvisorBot *advisorBot);

    /** Command 4: MIN - find minimum bid or ask for product in current time step */
    static double Command4_MIN(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot *advisorBot);

    /** Auxiliary function to compute minimum bid or ask for product in current time step without providing user feedback */
    static double computeMin(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot* advisorBot);

    /** Command 5: MAX - find maximum bid or ask for product in current time step */
    static double Command5_MAX(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot *advisorBot);

    /** Auxiliary function to compute maximum bid or ask for product in current time step without providing user feedback */
    static double computeMax(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot* advisorBot);

    /** Command 6: AVG - compute average bid or ask for product over sent number of time steps */
    static double Command6_AVG(std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot);

    /** Advance the timestamp in a circular manner */
    static void gotoNextTimeframe(AdvisorBot *advisorBot);

    /** Command 7: PREDICT - predict max or min bid or ask for sent product for the next time based on an EWMA */
    static double Command7_PREDICT(std::string product, std::string maxOrMin, std::string currentTime, std::string SDBEtype, AdvisorBot *advisorBot);

    /** Compute the Exponential Weighted Moving Average (EWMA) by analyzing historical data in the past sent number of time steps */
    static double computeEWMA(std::stack<double>& priceRecords, int timeStepsRemaining, std::vector<double>& intermediateEWMAs);

    /** Command 8: TIME - obtain the current time of the simulation */
    static void Command8_TIME(AdvisorBot *advisorBot);

    /** Command 9: STEP - advance to the next time step in the simulation */
    static void Command9_STEP(AdvisorBot *advisorBot);

    /** Compute the maximum ask or bid of a product for a specified number of time steps */
    static void computeMaxForPeriod(std::stack<double>& priceRecords, std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot);

    /** Compute the minimum ask or bid of a product for a specified number of time steps */
    static void computeMinForPeriod(std::stack<double>& priceRecords, std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot);

    /** Command 10: MEDIAN - find the median ask or bid for the sent product over the sent number of time steps */
    static double Command10_MEDIAN(std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot);

    /** Compute the median price of a range of prices for one or more time steps */
    static double computeMedian(std::vector<double>& priceRecords);

    /** Determine a time step's validity based on conversion success */
    static bool validateTimeStep(std::string timeStep);

    /** Determine a product's validity by checking for its existence in the dataset */
    static bool validateProduct(std::string product, AdvisorBot *advisorBot);

    /** Determine the SDBE type's validity by affirming its type is not unknown */
    static bool validateSDBEtype(std::string SDBEtype);

    /** Determine max/min validity based on its enumeration constant representation  */
    static bool validateMaxMin(std::string maxOrMin);

    /** Convert input string to lowercase */
    static void convertStringToLowercase(std::string& inputString);

    /** Convert a string to an max/min type */
    static MaxMinType stringToMaxMinType(std::string inputString);
};