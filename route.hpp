#include <vector>

#include "starmap.hpp"

class Route {

public:

    Route(Planet* start, Planet* end, StarMap system);

    int _no_stops;

    std::vector<Planet*> _stops;
    Planet* _destination;

    std::vector<double> _jumps;
    double _last_jump;
    double _length;

    int _VALID;

    void route_invalid();

    int is_invalid();

    void add_next_step(Route route, Route* new_route, Planet* next_stop, StarMap system);

    bool check_route(double range);

    void display(StarMap system);

    void get_jumps();

    void print_route();
};