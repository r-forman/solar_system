
#include <iostream>
#include <vector>
#include <cmath>
#include <utility> // for std:pair

/****  New Workflow ****
cd build
cmake ..    <- only needed if CMakeLists changes
make
./solar

*/

// Planet class
// attributes:
//      orbit equation
//      t0
//      polar coordinates @ t0

std::pair<float, float> calculate_position(){
    float current_x = 0.0, current_y = 0.0;
    return {current_x, current_y};
}


int main()
{

    std::cout << "Solar System Simulation\n";

    /*
    double radius;
    std::cout   << "Enter solar system radius [AU]: ";
    std::cin    >> radius;
    std::cout   << "The solar system had a radius of "
                << radius
                << std::endl;
    */

    auto [x, y] = calculate_position();

    std::cout   << "Planet position: " << x << ", " << y << std::endl;
    return 0;
}
