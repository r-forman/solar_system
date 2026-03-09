
#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>
#include <utility> // for std:pair

/*      New Workflow
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

// void plot_planets()

struct orbital_pos {
    double x, y;
};


class Planet {
public:
    Planet(double radius,
           double angular_velocity,
           double theta0,
           double t0)
        : radius(radius),
          omega(angular_velocity),
          theta0(theta0),
          t0(t0) {}

    orbital_pos position(double t) const {
        double theta = omega * (t - t0) + theta0;

        return {
            radius * std::cos(theta),
            radius * std::sin(theta)
        };
    }
private:
    double radius;
    double omega;
    double theta0;
    double t0;
};

int main()
{

    std::cout << "Solar System Simulation\n";

    /*
    double date;
    std::cout   << "Enter the date desired: ";
    std::cin    >> date;
    */

    auto [x, y] = calculate_position();

    std::cout   << "Planet position: " << x << ", " << y << std::endl;

    std::cout << "                            *" << std::endl;
    std::cout << "                            *" << std::endl;

    // Earth example (approx)
    double radius = 1.0;                 // AU
    double period = 365.25;              // days
    double omega = 2 * M_PI / period;    // rad/day

    Planet earth(radius, omega, 0.0, 0.0);



    double t = 100.0; // days

    orbital_pos pos = earth.position(t);

    /*

    Celestial
    Body        | Symbol
    ---------   | ------
    Sun	        | ☉
    Mercury     | ☿
    Venus       | ♀
    Earth       | ⊕ or ♁
    Moon        | ☾ or ☽
    Mars        | ♂
    Jupiter     | ♃
    Saturn      | ♄
    Uranus      | ♅ or ⛢|
    Neptune     | ♆
    Pluto       | ♇
    */

    std::cout << "x = " << pos.x << ", y = " << pos.y << "\n"
              << "   -      -        ---            ---        -     \n"
              << "  -     -      --                      --      -   \n"
              << "-     --     -        ------------        -     -- \n"
              << "     -     -      --                --      -     -\n"
              << "    -     -                            -     -     \n"
              << "   -     -               _ _ _ _ _                 \n"
              << "  -     -           - ‾‾           ‾‾ -            \n"
              << "  -    -         -                       -         \n"
              << " -    -        -       .-- ‾‾‾‾‾ --.       -       \n"
              << " -    -       -      /   .- ‾‾‾ -.   \\      -     \n"
              << "-    -        -     |   |    ☉    |   |     -      \n"
              << " -    -       -      \\   -. ___ .-   /      -     \n"
              << " -    -        -      ` -- _____ -- '      -       \n"
              << "  -     -    -    -                     -          \n"
              << "   -    --    --    ‾  - - - - - - -  ‾            \n"
              << "    -     -     -                                  \n"
              << "     -     -      --                    --         \n"
              << "-     --     -        ----------------             \n"
              << "  -     -      --                                  \n";

    return 0;
}
