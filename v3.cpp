/* Libraries */
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

/* Header Files */
#include "route.hpp"

/* Definitions */
#define PLANET_NO 12
#define RANGE 10
#define DATA_FILE "data2.txt"
#define DASH "---------------------------------------------------"

int main()
{
    /* READ IN DATA */

    std::string data_line;
    std::ifstream MyReadFile(DATA_FILE);
    std::vector<Planet*> planets;                   /* Vector of pointers to each planet */

    while (getline (MyReadFile, data_line, '\n'))   /* Go through each line in the data file */
    {
        Planet *planet = new Planet(data_line);     /* Create new planet from data line */
        planets.push_back(planet);                  /* Add planet pointer to planets */
    }

    MyReadFile.close();

    /* PRINT PLANET LIST */

    StarMap system(planets);

    std::cout << std::endl << DASH << std::endl;

    std::cout << std::endl << "Planet List:" << std::endl << std::endl;  /* Print planet list */

    system.print_planet_list();

    /* INPUT */

    std::string sinput;

    /* TAKE IN LOCATION */

    std::cout << std::endl << DASH << std::endl;

    std::cout << std::endl << "Please select your current location:" << std::endl;

    std::cin >> sinput;

    Planet *loc = system.planet_input(sinput);

    if(loc==NULL)
    {
        std::cout << "PLANET INPUT ERROR" << std::endl;
        return 0;
    }

    std::cout << std::endl << "Selected location: " << loc->get_name() << std::endl;

    /* TAKE IN DESTINATION */

    std::cout << std::endl << "Please select your destination:" << std::endl;

    std::cin >> sinput;

    Planet *dest = system.planet_input(sinput);

    if(dest==NULL)
    {
        std::cout << "PLANET INPUT ERROR" << std::endl;
        return 0;
    }

    std::cout << std::endl << "Selected destination: " << dest->get_name() << std::endl << std::endl;

    if(loc == dest)                 /* Check if location = destination */
    {
        std::cout << std:: endl << "Well done genius, you're already here!";
        return 0;
    }

    /* LOOK FOR ROUTE */

    bool route_found = false;

    std::vector<Route> route_list;
    Route primary_route(loc, dest, system);
    route_list.push_back(primary_route);
    
    Route final_route(loc, dest, system);
    final_route._length = 999999;

    int checking = 0;

    while(route_found == false)
    {
        checking++;

        const int elements = route_list.size();

        std::cout << "Checking routes with " << checking << " jumps..." << std::endl;
        std::cout << "NO. ROUTES TO CHECK: " << route_list.size() << std::endl;
        
        for(int i=0;i<elements;i++)
        {
            std::cout << checking+1 << ". Checking route " << i+1 << " of " << elements << std::endl;
            //route_list[i].get_jumps();
            //route_list[i].print_route();
            bool state = route_list[i].check_route(RANGE);
            //std::cout << "CHECK" << i << " : " << state <<std::endl;
            if(state == true && route_list[i]._length < final_route._length)
            {
                final_route = route_list[i];
            }
        }

        if(final_route._length < 999999)
        {
            route_found = true;
        }
        else
        {
            std::cout << std::endl;

            if(checking == system._size-1)
            {
                std::cout << "ROUTE NOT POSSIBLE" << std::endl;
                return 0;
            }

            for(int i=0;i<elements;i++)
            {
                if(route_list[i]._VALID == 1)
                {
                    //std::cout << "Route is valid - adding more" << std::endl;
                    for(int j=0;j<system._size;j++)
                    {
                        Route *new_route = new Route(loc, dest, system);
                        route_list[i].add_next_step(route_list[i],new_route,system._cargo[j],system);
                        route_list.push_back(*new_route);
                    }
                    route_list[i].route_invalid();
                }
                else
                {
                    //std::cout << "Route is invalid - skipping" <<std::endl;
                }
            }
            std::cout << std::endl;
            route_list.erase (route_list.begin(),route_list.begin()+elements);
        }
    }

    std::cout << "*Route calculated*" << std::endl << std::endl;

    final_route.display(system);

    std::cout << "All Done" << std::endl;

    return 0;
}