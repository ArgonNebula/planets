#include <vector>

#include "planet.hpp"

class StarMap   {

public:

    StarMap(std::vector<Planet *> planets);                 /* Starmap constructor */

    void print_planet_list();                               /* Print planet list */
    Planet* planet_input(std::string input);                /* Select planet from starmap from input */

    int _size;                                              /* Number of planets in system */
    std::vector<Planet*> _cargo;                            /* Container for list of planets */
    double **_dist;                                         /* Start of distances array */

private:

    void calc_distances(std::vector<Planet *> input);    
};