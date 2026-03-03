
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
    double radius;
    std::cout   << "Enter solar system radius [AU]: ";
    std::cin    >> radius;
    std::cout   << "The solar system had a radius of "
                << radius
                << std::endl;
    */

    auto [x, y] = calculate_position();

    std::cout   << "Planet position: " << x << ", " << y << std::endl;

    std::cout << "*****************************" << std::endl;
    std::cout << "*****************************" << std::endl;

    // Earth example (approx)
    double radius = 1.0;                 // AU
    double period = 365.25;              // days
    double omega = 2 * M_PI / period;    // rad/day

    Planet earth(radius, omega, 0.0, 0.0);

    double t = 100.0; // days

    orbital_pos pos = earth.position(t);

    std::cout << "x = " << pos.x
              << ", y = " << pos.y << "\n"
              << "         -      -        ---            ---        -     \n"
              << "        -     -      --                      --      -   \n"
              << "      -     --     -        ------------        -     -- \n"
              << "     -     -     -      --                --      -     -\n"
              << "    -     -     -     -       -------        -     -     \n"
              << "    -    -    --    --      -------------     --     --  \n"
              << "   -    -     -    -     --                     -     -  \n"
              << "   -    -    -    -     -                                \n"
              << "  -    -    -    --    -     .-- ‾‾‾‾‾ --.    .          \n"
              << "  -    -    -    -    -    /   .- ‾‾‾ -.   \\   -        \n"
              << " -    -    -    -    -    |   |    O    |   |     -    - \n"
              << "  -    -    -    -    -    \\   -. ___ .-   /  -     -     - \n"
              << "  -    -    -    --         ` -- _____ -- '  .    -    --- \n"
              << "   -    -    -    -     -                  -     -    -   -  \n"
              << "   -    -     -    -     -                -     -    -     -  \n"
              << "    -    -    --    --     --          --     --    --    -   \n"
              << "    -     -     -     -                      -     -     -    \n"
              << "-    -     -     -      --                --      -     -     \n"
              << " -    -     --     -        ------------        -     --      \n"
              << "  -     -     -      --                      --      -        \n";
    /*
    // Circle
    const int width = 100;
    const int height = 20;

    const double aspect = 2.0; // compensate for terminal character height

    // Orbit size
    double orbits[] = {4, 10, 16, 26};

    for (int y = height / 2; y > -height / 2; --y) {
        for (int x = -width / 2; x < width / 2; ++x) {

            bool printed = false;

            for (double a : orbits) {
                double b = a * 0.6;  // flatten to make oval-ish

                double eq =
                    (x * x) / (a * a) +
                    (y * y) / (b * b * aspect);

                if (std::abs(eq - 1.0) < 0.05) {
                    std::cout << "*";
                    printed = true;
                    break;
                }
            }

            if (!printed)
                std::cout << " ";
        }
        std::cout << "\n";
    }
    */
    return 0;
}
