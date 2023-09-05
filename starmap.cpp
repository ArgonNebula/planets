#include <cmath>
#include <iostream>

#include "starmap.hpp"

StarMap::StarMap(std::vector<Planet*> planets)      /* Starmap constructor */
{
    _size = planets.size();                         /* Set Starmap size */

    _dist = new double*[_size];                     /* Create distances array */
    for(int n=0; n<_size; ++n)
    {
        _dist[n] = new double[_size];
    }

    for(int i=0;i<_size;i++)                        /* Put planets into starmap */
    {
        _cargo.push_back(planets[i]);
    }

    calc_distances(planets);
}

void StarMap::calc_distances(std::vector<Planet*> input)
{
    for(int i=0;i<_size;i++)
    {
        for(int j=0;j<_size;j++)
        {
            _dist[i][j] = (sqrt(pow(input[i]->get_xc()-input[j]->get_xc(),2)+
                                pow(input[i]->get_yc()-input[j]->get_yc(),2)+
                                pow(input[i]->get_zc()-input[j]->get_zc(),2)));
        }
    }
}

void StarMap::print_planet_list()
{
    for(int i=0; i<_size; i++)
    {
        std::cout << _cargo[i]->get_index() << ": " << _cargo[i]->get_name() << std::endl;
    }
}

Planet* StarMap::planet_input(std::string planet_id)
{
    int planet_int;

    try
    {
        planet_int = stoi(planet_id);
    }
    catch(const std::exception& e)
    {
        std::cerr << planet_id << " is not an accepted integer." << '\n';
        return NULL;
    }

    if( planet_int < 0 || planet_int > _size-1)
    {
        std::cout << std::endl << "Selected planet does not exist. Please try again." << std::endl;
        return NULL;
    }

    Planet* planet_store = _cargo[planet_int];

    return planet_store;
}