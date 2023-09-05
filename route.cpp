#include <algorithm>
#include <set>
#include <vector>
#include <iostream>

#include "route.hpp"

Route::Route(Planet* start, Planet* end, StarMap system){
    _no_stops = 2;
    _destination = end;
    _stops.push_back(start);

    _length = system._dist[start->get_index()][end->get_index()];
    _last_jump = system._dist[start->get_index()][end->get_index()];

    _VALID = 1;
}

void Route::route_invalid()
{
    _VALID = 0;
}

bool Route::check_route(double range)
{
    if(_VALID == 0)
    {
        //std::cout << "Already Invalid" << std::endl;
        return false;
    }

    if(std::count(_stops.begin(), _stops.end(), _destination) != 0)
    {
        //std::cout << "Destination in stops" << std::endl;
        route_invalid();
        return false;
    }
    
    std::set<Planet*> test(_stops.begin(), _stops.end());

    if(_stops.size() != test.size())
    {
        //std::cout << "Repeat in stops" << std::endl;
        route_invalid();
        return false;
    }

    if(_jumps.empty() == false)
    {
        double biggest_jump = *max_element(_jumps.begin(),_jumps.end());
        //std::cout << "BIGGEST JUMP: " << biggest_jump << std::endl;

        if(biggest_jump > range)
        {
            //std::cout << "Intermediate jump too long" << std::endl;
            route_invalid();
            return false;
        }
    }

    if(_last_jump > range)
    {
        //std::cout << "Last jump too long" << std::endl;
        return false;
    }

    return true;
}

void Route::add_next_step(Route route, Route* new_route, Planet* next_stop, StarMap system)
{
    *new_route = route;

    new_route->_no_stops++;

    new_route->_length -= system._dist[route._stops.back()->get_index()][route._destination->get_index()];
    new_route->_length += system._dist[route._stops.back()->get_index()][next_stop->get_index()];
    new_route->_length += system._dist[next_stop->get_index()][route._destination->get_index()];

    new_route->_jumps.push_back(system._dist[route._stops.back()->get_index()][next_stop->get_index()]);
    new_route->_last_jump = system._dist[next_stop->get_index()][route._destination->get_index()];

    new_route->_stops.push_back(next_stop);
}

void Route::display(StarMap system)
{
    std::cout << "Calculated Route:" << std::endl;
    std::cout << "Route length: " << _length << std::endl << std::endl;

    std::cout << "Route details:" << std::endl << std::endl;

    std::cout << "1. " << _stops[0]->get_name() << std::endl;

    for(int i=0;i<_no_stops-2;i++)
    {
        std::cout << i+2 << ". " << _stops[i+1]->get_name()  << " - " << system._dist[_stops[i]->get_index()][_stops[i+1]->get_index()]<< std::endl;
    }

    std::cout << _no_stops << ". " << _destination->get_name() << " - " << system._dist[_stops[_no_stops-2]->get_index()][_destination->get_index()] << std::endl;

    std::cout << std::endl;
}

int Route::is_invalid()
{
    return _VALID;
}

void Route::get_jumps()
{
    if(!_jumps.empty())
    {
        for(int i=0; i<(_no_stops-2);i++)
        {
            std::cout << _jumps[i] << "-";
        }
    }
    std::cout << _last_jump;

    std::cout << std::endl;
}

void Route::print_route()
{
    for(int i=0; i<_no_stops-1;i++)
    {
        std::cout << _stops[i]->get_index() << " - "; 
    }
    std::cout << _destination->get_index() << std::endl;
}