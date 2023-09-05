#include <string>

class Planet {

public:

    Planet(std::string data);       /* Planet constructor */

    std::string get_coords();       /* Print coordinates of a planet */
    std::string get_name();
    int get_xc();
    int get_yc();
    int get_zc();
    int get_index();

private:

    std::string name;               /* Planet data entries */
    int xcoord;
    int ycoord;
    int zcoord;
    int index;
};