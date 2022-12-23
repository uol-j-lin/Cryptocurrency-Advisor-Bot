#include <iostream>
#include "AdvisorBot.h"

int main()
{
    // Create an instance of Advisor Bot
    AdvisorBot app{};

    // Begin simulation, and request user to continuously enter commands
    app.init();
}