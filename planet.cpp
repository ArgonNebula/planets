#include <sstream>
#include <vector>
#include <string>

#include "planet.hpp"

Planet::Planet(std::string data)        /* Planet constructor */
{
    std::string s;                      /* Holder string */
    std::stringstream ss(data);         /* Pass data line into stream */
    std::vector<std::string> v, vc;     /* Two vectors of string */

    while (getline(ss,s,' '))           /* For each section of the data line, separated by space */
    {
        v.push_back(s);                 /* Add each section to vector v */
    }

    std::stringstream ssc(v[2]);        /* Pass third element (coordinates) into stream */

    while (getline(ssc,s,'-'))          /* For each section of coordinates, separated by - */
    {
        vc.push_back(s);                /* Add each coordinate to vector vc */
    }

    index = stoi(v[0]);                 /* Assign planet data variables */
    name = v[1];
    xcoord = stoi(vc[0]);
    ycoord = stoi(vc[1]);
    zcoord = stoi(vc[2]);
}

std::string Planet::get_coords()        /* Print planet coords */
{
    std::string x,y,z;                  /* Strings for coords */

    x = std::to_string(xcoord);         /* Assign coords */
    y = std::to_string(ycoord);
    z = std::to_string(zcoord);
    
    return(x + '-' + y + '-' + z);      /* Return string of coords */
}

std::string Planet::get_name()          /* Get planet name */
{
    return name;
}

int Planet::get_index()                 /* Get planet index */
{
    return index;
}

int Planet::get_xc()                    /* Get planet xcoord */
{
    return xcoord;
}

int Planet::get_yc()                    /* Get planet ycoord */
{
    return ycoord;
}

int Planet::get_zc()                    /* Get planet zcoord */
{
    return zcoord;
}

