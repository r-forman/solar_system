#include <iostream>
#include <vector>
#include <cmath>
#include <matplot/matplot.h>
#include <utility> // for std::pair

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
    using namespace matplot;

    auto f = figure(true);
    hold(on);

    std::vector<std::pair<std::string, Planet>> planets = {
        {"Mercury", Planet(0.39, 2*M_PI/88.0, 0, 0)},
        {"Venus",   Planet(0.72, 2*M_PI/225.0, 0, 0)},
        {"Earth",   Planet(1.00,  2*M_PI/365.25, 0, 0)},
        {"Mars",    Planet(1.52, 2*M_PI/687.0, 0, 0)},
        {"Jupiter", Planet(5.203, 2*M_PI/4332.59, 0, 0)},
        {"Saturn",  Planet(9.537, 2*M_PI/10759, 0, 0)},
        {"Uranus",  Planet(19.191,2*M_PI/30687, 0, 0)},
        {"Neptune", Planet(30.068,2*M_PI/60190, 0, 0)}
    };

    for (auto& [name, planet] : planets)
    {
        std::vector<double> xs;
        std::vector<double> ys;

        for (double t = 0; t <= 700; t += 0.5)
        {
            orbital_pos pos = planet.position(t);
            xs.push_back(pos.x);
            ys.push_back(pos.y);
        }

        plot(xs, ys)->display_name(name);
    }

    axis(equal);
    legend();
    title("Inner Solar System Orbits");
    xlabel("X (AU)");
    ylabel("Y (AU)");

    show();

    return 0;
}