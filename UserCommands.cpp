#include "UserCommands.h"

/** Initialize an instance of the User Commands class */
UserCommands::UserCommands() = default;

/** Command 1: HELP - List all available commands */
void UserCommands::Command1_HELP()
{
	std::cout << "The available commands are help, help <cmd>, prod, min, max, avg, predict, time, step, and median." << std::endl;
}

/** Command 2: HELP PROD - output help for the prod command */
void UserCommands::Command2_HELP_prod()
{
    std::cout << "Prod - this command lists all available products.\nCommand syntax: prod" << std::endl;
}

/** Command 2: HELP MIN - output help for the min command */
void UserCommands::Command2_HELP_min()
{
    std::cout << "Min - this command finds the minimum bid or ask for a product in the current time step.\nCommand syntax: min product bid/ask" << std::endl;
}

/** Command 2: HELP MAX - output help for the max command */
void UserCommands::Command2_HELP_max()
{
    std::cout << "Max - this command finds the maximum bid or ask for a product in the current time step.\nCommand syntax: max product bid/ask" << std::endl;
}

/** Command 2: HELP AVG - output help for the avg command */
void UserCommands::Command2_HELP_avg()
{
    std::cout << "Avg - this command finds the average ask or bid for the sent product over the sent number of time steps.\nCommand syntax: avg product ask/bid time steps" << std::endl;
}

/** Command 2: HELP PREDICT - output help for the predict command */
void UserCommands::Command2_HELP_predict()
{
    std::cout << "Predict - this command predicts the max or min ask or bid for the sent product for the next time step.\nCommand syntax: predict max/min product ask/bid" << std::endl;
}

/** Command 2: HELP TIME - output help for the time command */
void UserCommands::Command2_HELP_time()
{
    std::cout << "Time - this command states the current time in dataset (i.e. the time frame).\nCommand syntax: time" << std::endl;
}

/** Command 2: HELP STEP - output help for the step command */
void UserCommands::Command2_HELP_step()
{
    std::cout << "Step - this command advances to the next time step.\nCommand syntax: step" << std::endl;
}

/** Command 2: HELP MEDIAN - output help for the median command */
void UserCommands::Command2_HELP_median()
{
    std::cout << "Median - this command finds the median ask or bid for the sent product over the sent number of time steps.\nCommand syntax: median product ask/bid time steps" << std::endl;
}

/** Command 3: PROD - list available products in the dataset */
void UserCommands::Command3_PROD(AdvisorBot *advisorBot)
{
    // Retrieve unique products from the dataset
    std::vector<std::string> products = advisorBot->stocksDataBook.getUniqueProducts();

    // Indicate that a product list will be displayed
    std::cout << "The unique products in the simulation include: ";

    // Counter to track vector position while iterating
    int index = 0; 

    // Display formatted products to user
    for (std::vector<std::string>::iterator it = products.begin(), end = products.end(); it != end; ++it, ++index)
    {
        if (index != products.size() - 1)
        {
            std::cout << *it << ", ";
        }
        else
        {
            std::cout << *it << ". " << std::endl;
        }
    }
}

/** Command 4: MIN - find minimum bid or ask for product in current time step
 *
 *  @param SDBEtype    SDBE type - ask/bid/unknown
 *  @param product     Product name
 *  @param currentTime Current timestamp of simulation
 *  @return            Minimum price within filtered SDBE entries
 *
 */
double UserCommands::Command4_MIN(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot *advisorBot)
{
    // Validate StocksDataBookEntry type
    if (!validateSDBEtype(SDBEtype))
    {
        std::cout << "Three token user command failed. StocksDataBookEntry type not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate product
    if (!validateProduct(product,advisorBot))
    {
        std::cout << "Three token user command failed. Product not recognized." << std::endl;
        throw std::exception{};
    }

    // Filter out the dataset based on the SDBE type, product, and current time step of the simulation
    std::vector<StocksDataBookEntry> StocksDataBookEntries = advisorBot->stocksDataBook.filterSDBEentries(StocksDataBookEntry::stringToStocksDataBookType(SDBEtype),
        product, currentTime);

    // Provide feedback to user about minimum price and filter parameters entered
    std::cout << "====================================" << std::endl;
    std::cout << "The min " << SDBEtype << " for " << product << " is " << advisorBot->stocksDataBook.getMinMaxPrice(StocksDataBookEntries).min << std::endl;
    std::cout << "====================================" << std::endl;

    // Retrieve the minimum price among the filtered entries
    return advisorBot->stocksDataBook.getMinMaxPrice(StocksDataBookEntries).min;
}

/* Auxiliary function to compute minimum bid or ask for product in current time step without providing user feedback
 *
 * @param SDBEtype    SDBE type - ask/bid/unknown
 * @param product     Product name
 * @param currentTime Current timestamp of simulation
 *
 */
double UserCommands::computeMin(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot* advisorBot)
{
    // Validate StocksDataBookEntry type
    if (!validateSDBEtype(SDBEtype))
    {
        std::cout << "Three token user command failed. StocksDataBookEntry type not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate product
    if (!validateProduct(product, advisorBot))
    {
        std::cout << "Three token user command failed. Product not recognized." << std::endl;
        throw std::exception{};
    }

    // Filter out the dataset based on the SDBE type, product, and current time step of the simulation
    std::vector<StocksDataBookEntry> StocksDataBookEntries = advisorBot->stocksDataBook.filterSDBEentries(StocksDataBookEntry::stringToStocksDataBookType(SDBEtype),
        product, currentTime);

    // Retrieve the minimum price among the filtered entries
    return advisorBot->stocksDataBook.getMinMaxPrice(StocksDataBookEntries).min;
}

/** Command 5: MAX - find maximum bid or ask for product in current time step
 *
 *  @param SDBEtype    SDBE type - ask/bid/unknown
 *  @param product     Product name
 *  @param currentTime Current timestamp of simulation
 *  @return            Maximum price within filtered SDBE entries
 *
 */
double UserCommands::Command5_MAX(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot *advisorBot)
{
    // Validate StocksDataBookEntry type
    if (!validateSDBEtype(SDBEtype))
    {
        std::cout << "Three token user command failed. StocksDataBookEntry type not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate product
    if (!validateProduct(product, advisorBot))
    {
        std::cout << "Three token user command failed. Product not recognized." << std::endl;
        throw std::exception{};
    }

    // Filter out the dataset based on the SDBE type, product, and current time step of the simulation
    std::vector<StocksDataBookEntry> StocksDataBookEntries = advisorBot->stocksDataBook.filterSDBEentries(StocksDataBookEntry::stringToStocksDataBookType(SDBEtype),
        product, currentTime);

    // Provide feedback to user about maximum price and filter parameters entered
    std::cout << "====================================" << std::endl;
    std::cout << "The max " << SDBEtype << " for " << product << " is " << advisorBot->stocksDataBook.getMinMaxPrice(StocksDataBookEntries).max << std::endl;
    std::cout << "====================================" << std::endl;

    advisorBot->stocksDataBook.getMinMaxPrice(StocksDataBookEntries);


    // Retrieve the maximum price among the filtered entries
    return advisorBot->stocksDataBook.getMinMaxPrice(StocksDataBookEntries).max;
}

/* Auxiliary function to compute maximum bid or ask for product in current time step without providing user feedback 
 *
 * @param SDBEtype    SDBE type - ask/bid/unknown
 * @param product     Product name
 * @param currentTime Current timestamp of simulation
 * 
 */
double UserCommands::computeMax(std::string SDBEtype, std::string product, std::string currentTime, AdvisorBot* advisorBot)
{
    // Validate StocksDataBookEntry type
    if (!validateSDBEtype(SDBEtype))
    {
        std::cout << "Three token user command failed. StocksDataBookEntry type not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate product
    if (!validateProduct(product, advisorBot))
    {
        std::cout << "Three token user command failed. Product not recognized." << std::endl;
        throw std::exception{};
    }

    // Filter out the dataset based on the SDBE type, product, and current time step of the simulation
    std::vector<StocksDataBookEntry> StocksDataBookEntries = advisorBot->stocksDataBook.filterSDBEentries(StocksDataBookEntry::stringToStocksDataBookType(SDBEtype),
        product, currentTime);

    // Retrieve the maximum price among the filtered entries
    return advisorBot->stocksDataBook.getMinMaxPrice(StocksDataBookEntries).max;
}

/** Advance the timestamp in a circular manner */
void UserCommands::gotoNextTimeframe(AdvisorBot *advisorBot)
{
    // Indicate to user that simulation is moving forward one time step
    std::cout << "Advancing to next time frame..." << std::endl;

    /* Set current time to next timestamp
       If current timestamp is the last timestamp in the dataset, then it is set to the first timestamp */
    advisorBot->currentTime = advisorBot->stocksDataBook.getNextTimeStamp(advisorBot->currentTime);
}

/** Command 6: AVG - compute average bid or ask for product over sent number of time steps
 *
 *  @param SDBEtype     SDBE type - ask/bid/unknown
 *  @param product      Product name
 *  @param currentTime  Current timestamp of simulation
 *  @param numTimesteps Number of time steps to factor into average
 *  @return             Average bid or ask price of a product for a given time frame
 *
 */
double UserCommands::Command6_AVG(std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot)
{
    // Validate SDBE type
    if (!validateSDBEtype(SDBEtype))
    {
        std::cout << "Four token user command failed. StocksDataBookEntry type not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate product
    if (!validateProduct(product, advisorBot))
    {
        std::cout << "Four token user command failed. Product not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate time step
    if (!validateTimeStep(numTimesteps))
    {
        std::cout << "Four token user command failed. Time step not recognized." << std::endl;
        throw std::exception{};
    }

    // Record current time in simulation
    std::string currentTimeStep = currentTime;

    // Convert time representation to double for computation
    double totalTimesteps = std::stod(numTimesteps);

    // Subset of dataset which will be filtered based on SDBE type, product, and current time step of user command
    std::vector<StocksDataBookEntry> StocksDataBookEntries;

    // Record the sum of the averages of the number of time steps considered
    double totalAvgAllTimesteps = 0;

    // Compute averages for each time step
    for (size_t i = 0; i < totalTimesteps; ++i)
    {
        // Filter dataset into relevant subset of entries based on input parameters
        StocksDataBookEntries = advisorBot->stocksDataBook.filterSDBEentries(StocksDataBookEntry::stringToStocksDataBookType(SDBEtype),
            product, currentTimeStep);

        double avgPriceOneTimestep = 0;

        // Compute total price accumulated over one time step
        for (const StocksDataBookEntry& e : StocksDataBookEntries)
        {
            avgPriceOneTimestep += e.price;
        }

        // Record the number of entries in the filtered subset
        int numEntries = StocksDataBookEntries.size();

        /* Compute average price for one time step
        Avoid divide by zero exception if the filtered subset is empty */
        avgPriceOneTimestep = numEntries != 0 ? avgPriceOneTimestep / StocksDataBookEntries.size() : 0;

        // Provide user feedback for the average price for each time step before the initial timestamp
        std::cout << "Average price " << i << " time step(s) ago: " << avgPriceOneTimestep << " - Time: " << currentTimeStep << std::endl;

        // Move simulation one time step into the past in a circular manner
        currentTimeStep = advisorBot->stocksDataBook.getPreviousTimeStamp(currentTimeStep);

        // Add average price of individual time step to total sum
        totalAvgAllTimesteps += avgPriceOneTimestep;
    }

    // Compute overall average price across a set number of historical time steps
    double averagePrice = totalAvgAllTimesteps / totalTimesteps;
    std::cout << "======================================================================" << std::endl;
    std::cout << "The average " << product << " " << SDBEtype << " price over the last " << numTimesteps << " time steps was " << averagePrice << std::endl;
    std::cout << "======================================================================" << std::endl;
    return averagePrice;
}


/** Command 7: PREDICT - predict max or min bid or ask for sent product for the next time based on an EWMA
 *
 *  @param SDBEtype    SDBE type - ask/bid/unknown
 *  @param product     Product name
 *  @param currentTime Current timestamp of simulation
 *  @param maxOrMin    Maximum or minimum price to predict
 *  @return            Predicted price based on a 10 time step EWMA
 *
 */
double UserCommands::Command7_PREDICT(std::string product, std::string maxOrMin, std::string currentTime, std::string SDBEtype, AdvisorBot *advisorBot)
{
    // Validate product
    if (!validateProduct(product,advisorBot))
    {
        std::cout << "Four token user command failed. Product not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate max or min
    if (!validateMaxMin(maxOrMin))
    {
        std::cout << "Four token user command failed. Max or min not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate SDBE type
    if (!validateSDBEtype(SDBEtype))
    {
        std::cout << "Four token user command failed. StocksDataBookEntry type not recognized." << std::endl;
        throw std::exception{};
    }

    /* Use an Exponentially Weighted Moving Average(EWMA) over a ten day period which applies weight factors which decrease exponentially for less recent time steps
    This yields a more accurate prediction result compared to a Simple Moving Average (SMA) - which does not apply weights based on time step recency */
    

    // Storage for price records spanning ten historical time steps
    std::stack<double> priceRecords;

    // Determine if maximum or minimum should be computed
    enum MaxMinType maxMinType = stringToMaxMinType(maxOrMin);

    if (maxMinType == MaxMinType::max)
    {
        // Compute maximum prices over a time period of ten days for a specified SDBE type and product
        computeMaxForPeriod(priceRecords, SDBEtype, product, currentTime, "10",advisorBot);
    }
    else if (maxMinType == MaxMinType::min)
    {
        // Compute minimum prices over a time period of ten days for a specified SDBE type and product
        computeMinForPeriod(priceRecords, SDBEtype, product, currentTime, "10",advisorBot);
    }

    // Storage for intermediate EWMA values
    std::vector<double> intermediateEWMAs;

    // Delegate computation of EWMA to auxiliary function
    double EWMAresult = computeEWMA(priceRecords, priceRecords.size(), intermediateEWMAs);

    // Output the predicted price based on EWMA to the command line 
    std::cout << "======================================================================================================================" << std::endl;
    std::cout << "The predicted " << maxOrMin << " " << product << " " << SDBEtype << " price for the next time step is " << EWMAresult << " based on a 10 time step EWMA with an SF of 2/11" << std::endl;
    std::cout << "======================================================================================================================" << std::endl;
    return EWMAresult;
}

/** Compute the Exponential Weighted Moving Average (EWMA) by analyzing historical data in the past sent number of time steps
 *
 *  @param priceRecords       Price records spanning ten historical time steps
 *  @param timeStepsRemaining Number of remaining time steps to be considered
 *  @param intermediateEWMAs  Storage for intermediate EWMA values computed from historical price records
 *  @return                   EWMA computed over given time frame 
 *
 */
double UserCommands::computeEWMA(std::stack<double>& priceRecords, int timeStepsRemaining, std::vector<double>& intermediateEWMAs)
{
    if (timeStepsRemaining == 1)
    {
        // Initial EWMA is equivalent to the max/min bid/ask for the SDBE entry ten time steps ago
        double res = priceRecords.top();
        std::cout << "Earliest time step. Initial EWMA: " << res << std::endl;

        // Move to next time step
        priceRecords.pop();
        return res;
    }
    else
    {
        // Acquire max/min price of current time step
        double currentPrice = priceRecords.top();

        // Move to next time step
        priceRecords.pop();

        /* Smoothing factor : 2.0 / (number of time steps + 1)
        This parameter controls the rate at which the influence of observations at prior time steps decay exponentially */
        double smoothingFactor = 2.0 / (10 + 1);

        // Compute the intermediate EWMAs using the Single Exponential Smoothing parameter
        double EWMA = currentPrice * smoothingFactor + (1 - smoothingFactor) * computeEWMA(priceRecords, timeStepsRemaining - 1, intermediateEWMAs);

        // Indicate the intermediate EWMA values to the user
        std::cout << timeStepsRemaining-1 << " time step(s) since earliest time step - EWMA: " << EWMA << std::endl;

        // Record the intermediate EWMA 
        intermediateEWMAs.push_back(EWMA);
        return EWMA;
    }
}

/** Command 8: TIME - obtain the current time of the simulation */
void UserCommands::Command8_TIME(AdvisorBot *advisorBot)
{
    std::cout << "=================================================================" << std::endl;
    std::cout << "The current time of the simulation is: " << advisorBot->currentTime << std::endl;
    std::cout << "=================================================================" << std::endl;
}

/** Command 9: STEP - advance to the next time step in the simulation */
void UserCommands::Command9_STEP(AdvisorBot *advisorBot)
{
    gotoNextTimeframe(advisorBot);
    std::cout << "===============================================" << std::endl;
    std::cout << "Simulation is now at " << advisorBot->currentTime << std::endl;
    std::cout << "===============================================" << std::endl;
}

/** Compute the maximum ask or bid of a product for a specified number of time steps
 *
 *  @param priceRecords Price records spanning ten historical time steps
 *  @param SDBEtype     SDBE type - ask/bid/unknown
 *  @param product      Product names
 *  @param currentTime  Current timestamp of simulation
 *  @param numTimesteps Number of historical time steps to consider
 *
 */
void UserCommands::computeMaxForPeriod(std::stack<double>& priceRecords, std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot)
{
    // Record current timestamp in simulation
    std::string currentTimeStep = currentTime;

    // Convert time representation to double for computation
    double totalTimesteps = std::stod(numTimesteps);

    // Begin from initial timestamp and iterate into past timestamps
    for (size_t i = 0; i < totalTimesteps; ++i)
    {
        // Extract maximum from current timestamp
        double maxPriceOneTimestep = computeMax(SDBEtype, product, currentTimeStep, advisorBot);
        priceRecords.push(maxPriceOneTimestep);

        // Move simulation one time step into the past
        currentTimeStep = advisorBot->stocksDataBook.getPreviousTimeStamp(currentTimeStep);
    }
}

/** Compute the minimum ask or bid of a product for a specified number of time steps
 *
 *  @param priceRecords Price records spanning ten historical time steps
 *  @param SDBEtype SDBE type - ask/bid/unknown
 *  @param product Product names
 *  @param currentTime Current timestamp of simulation
 *  @param numTimesteps Number of historical time steps to consider
 *
 */
void UserCommands::computeMinForPeriod(std::stack<double>& priceRecords, std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot)
{
    // Record current timestamp in simulation
    std::string currentTimeStep = currentTime;

    // Convert time representation to double for computation
    double totalTimesteps = std::stod(numTimesteps);

    // Begin from initial timestamp and iterate into past timestamps
    for (size_t i = 0; i < totalTimesteps; ++i)
    {
        // Extract minimum from current timestamp
        double minPriceOneTimestep = computeMin(SDBEtype, product, currentTimeStep, advisorBot);
        priceRecords.push(minPriceOneTimestep);

        // Move simulation one time step into the past
        currentTimeStep = advisorBot->stocksDataBook.getPreviousTimeStamp(currentTimeStep);
    }
}

/** Compute the median price of a range of prices for one or more time steps
 *
 *  @param SDBEtype     SDBE type - ask/bid/unknown
 *  @param product      Product name
 *  @param currentTime  Current timestamp of simulation
 *  @param numTimesteps Number of historical time steps to consider
 *  @return             Median price over a given time frame
 *
 */
double UserCommands::Command10_MEDIAN(std::string SDBEtype, std::string product, std::string currentTime, std::string numTimesteps, AdvisorBot *advisorBot)
{
    // Validate SDBE type
    if (!validateSDBEtype(SDBEtype))
    {
        std::cout << "Four token user command failed. StocksDataBookEntry type not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate product
    if (!validateProduct(product, advisorBot))
    {
        std::cout << "Four token user command failed. Product not recognized." << std::endl;
        throw std::exception{};
    }

    // Validate time step
    if (!validateTimeStep(numTimesteps))
    {
        std::cout << "Four token user command failed. Time step not recognized." << std::endl;
        throw std::exception{};
    }

    // Record current timestamp in simulation
    std::string currentTimeStep = currentTime;

    // Convert time representation to double for computation
    double totalTimesteps = std::stod(numTimesteps);

    // Store a subset of the dataset based on input parameters
    std::vector<StocksDataBookEntry> StocksDataBookEntries;

    // Store all prices for the specified number of time steps
    std::vector<double> priceRecords;

    // Storage for the median price of all relevant time steps
    double medianPrice = 0;

    // Begin from initial timestamp and iterate into past timestamps
    for (size_t i = 0; i < totalTimesteps; ++i)
    {
        // Filter a subset of the dataset based on the SDBE type, product, and current time step
        StocksDataBookEntries = advisorBot->stocksDataBook.filterSDBEentries(StocksDataBookEntry::stringToStocksDataBookType(SDBEtype),
            product, currentTimeStep);

        // Record each entry's price
        for (const StocksDataBookEntry& e : StocksDataBookEntries)
        {
            priceRecords.emplace_back(e.price);
        }

        // Move simulation one time step into the past
        currentTimeStep = advisorBot->stocksDataBook.getPreviousTimeStamp(currentTimeStep);
    }

    // Delegate computation of the price median to an auxiliary function
    medianPrice = computeMedian(priceRecords);
    std::cout << "======================================================================" << std::endl;
    std::cout << "The median " << product << " " << SDBEtype << " price over the last " << numTimesteps << " time step(s) was " << medianPrice << std::endl;
    std::cout << "======================================================================" << std::endl;
    return medianPrice;
}

/** Compute the median price of a range of prices from one or more time steps
 *
 *  @param priceRecords Price records for one or more time steps
 *  @return             Median of a set of price records 
 *
 */
double UserCommands::computeMedian(std::vector<double>& priceRecords)
{
    // Sort the price records in ascending order
    std::sort(priceRecords.begin(), priceRecords.end());

    // Determine the number of records 
    int length = priceRecords.size();

    /* Case 1: odd number of records
    Median is single middle element */
    if (length % 2 != 0)
    {
        // Retrieve middle element
        return priceRecords[length / 2];
    }
    /* Case 2: even number of records
    Median is the average of the two middle elements */
    return (priceRecords[length / 2] + priceRecords[length / 2 - 1]) / 2.0;
}

/** Determine a time step's validity based on conversion success
 *
 *  @param timeStep User-entered time step
 *  @return         true if the number of time steps is valid, false otherwise
 */
bool UserCommands::validateTimeStep(std::string timeStep)
{
    try
    {
        // Attempt to convert token into integer 
        int intTimeStep = std::stoi(timeStep);
        return true;
    }
    catch (const std::exception& e)
    {
        // Unsuccessful conversion from string time step to integer 
        std::cout << "Unsuccessful conversion from string time step to integer" << std::endl;
        return false;
    }
}

/** Determine a product's validity by checking for its existence in the dataset
 *
 *  @param product User-entered product
 *  @return        true if the product exists in the dataset, false otherwise
 */
bool UserCommands::validateProduct(std::string product, AdvisorBot *advisorBot)
{
    try
    {
        // Query list of known products from dataset
        std::vector<std::string> uniqueProducts = advisorBot->stocksDataBook.getUniqueProducts();

        // Input product assumed to be not present
        bool isValid = false;

        // Consider each unique product in the dataset
        for (auto& uniqueProduct : uniqueProducts)
        {
            // Normalize the user input and known product name by conversion to lowercase
            convertStringToLowercase(uniqueProduct);
            convertStringToLowercase(product);

            // Determine success of match between user input and known product
            if (uniqueProduct == product)
            {
                isValid = true;
                break;
            }
        }
        return isValid;
    }
    catch (const std::exception& e)
    {
        // Error in validating product against dataset products
        std::cout << "Error processing product" << std::endl;
    }
}

/** Determine the SDBE type's validity by affirming its type is not unknown
 *
 *  @param SDBEtype User-entered SDBE type - ask/bid/unknown
 *  @return         true if the string is represented by an ask or bid enumerator, false otherwise
 *
 */
bool UserCommands::validateSDBEtype(std::string SDBEtype)
{
    // Convert input string to lowercase
    convertStringToLowercase(SDBEtype);

    // Affirm that the user-entered SDBE type is not an unknown enumeration after conversion
    enum StocksDataBookType stocksDataBookType = StocksDataBookEntry::stringToStocksDataBookType(SDBEtype);
    return stocksDataBookType != StocksDataBookType::unknown;
}

/** Determine max/min validity based on its enumeration constant representation 
 *
 *  @param maxOrMin String to be validated
 *  @return         true if the string is represented by a max or min enumerator, false otherwise
 *
 */
bool UserCommands::validateMaxMin(std::string maxOrMin)
{
    enum MaxMinType maxMinType = stringToMaxMinType(maxOrMin);
    
    // Match to valid enumeration constants
    if (maxMinType == MaxMinType::min || maxMinType == MaxMinType::max)
    {
        return true;
    }
    
    // Unknown enumeration constant
    return false;
}

/* Convert an input string to lowercase 
 *
 * @param inputString The string to be converted
 * 
 */
void UserCommands::convertStringToLowercase(std::string& inputString)
{
    // Convert each character in the input string to lowercase
    std::for_each(inputString.begin(), inputString.end(), [](unsigned char inputCharacter) {
    inputCharacter = ::tolower(inputCharacter);
    });
}

/** Convert a string to an max/min type 
 *   
 *  @param inputString string to be converted
 *  @return            max/min enumerator representing the input string
 * 
 */
MaxMinType UserCommands::stringToMaxMinType(std::string inputString)
{
    // Convert input string to lowercase 
    convertStringToLowercase(inputString);

    // Match input string to max
    if (inputString == "max")
    {
        // Return max enumerator
        return MaxMinType::max;
    }

    // Match input string to min
    if (inputString == "min")
    {
        // Return min enumerator
        return MaxMinType::min;
    }

    // Unrecognized max/min type, return unknown enumerator
    return MaxMinType::unknown;
}