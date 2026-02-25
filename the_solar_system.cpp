
#include <iostream>
#include <vector>
#include <cmath>

/****  New Workflow ****
cd build
cmake ..    <- only needed if CMakeLists changes
make
./solar

*/


int main()
{

    std::cout << "Solar System Simulation\n";

    float radius;
    scanf("%f",&radius);
    printf("The solar system had a radius of %.1f AU.\n", radius);

    return 0;
}
