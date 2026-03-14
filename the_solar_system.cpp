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

// The below planet class is for perfectly circular orbits
// class Planet {
// public:
//     Planet(double radius,
//            double angular_velocity,
//            double theta0,
//            double t0)
//         : radius(radius),
//           omega(angular_velocity),
//           theta0(theta0),
//           t0(t0) {}

//     orbital_pos position(double t) const {
//         double theta = omega * (t - t0) + theta0;

//         return {
//             radius * std::cos(theta),
//             radius * std::sin(theta)
//         };
//     }

// private:
//     double radius;
//     double omega;
//     double theta0;
//     double t0;
// };

class Planet {
public:
    Planet(double a, // semi-major axis (AU)
           double e, // eccentricity. 0 = circle, <1 = ellipse
           double omega, // angular velocity (rad/day)
           double theta0, // starting angle at t0
           double t0) // starting time
        : a(a),
          e(e),
          omega(omega),
          theta0(theta0),
          t0(t0) {}

    orbital_pos position(double t) const {
        double theta, r;
        theta = omega * (t-t0) + theta0;
        r = a * (1-e*e) / (1+e*std::cos(theta));
        return {r*std::cos(theta), r*std::sin(theta)};
    }

private:
    double a; // semi-major axis (AU)
    double e; // eccentricity. 0 = circle, <1 = ellipse
    double omega; // angular velocity (rad/day)
    double theta0; // starting angle at t0
    double t0; // starting time
};

int main()
{
    using namespace matplot;

    auto f = figure(true);
    hold(on);

    // For circular orbits
    // std::vector<std::pair<std::string, Planet>> planets = {
    //     {"Sun", Planet(0.01, 0.01, 0, 0)},
    //     {"Mercury", Planet(0.39, 2*M_PI/88.0, 0, 0)},
    //     {"Venus",   Planet(0.72, 2*M_PI/225.0, 0, 0)},
    //     {"Earth",   Planet(1.00,  2*M_PI/365.25, 0, 0)},
    //     {"Mars",    Planet(1.52, 2*M_PI/687.0, 0, 0)},
    //     // {"Jupiter", Planet(5.203, 2*M_PI/4332.59, 0, 0)},
    //     // {"Saturn",  Planet(9.537, 2*M_PI/10759, 0, 0)},
    //     // {"Uranus",  Planet(19.191,2*M_PI/30687, 0, 0)},
    //     // {"Neptune", Planet(30.068,2*M_PI/60190, 0, 0)}
    // };


    // Planets: a (AU), e, omega(rad/day), theta0(rad), t0
    // Starting angles are based on Jan 1st, 2000
    std::vector<std::pair<std::string, Planet>> planets = {
        {"Mercury", Planet(0.387, 0.206, 2*M_PI/88.0, 4.1, 0.0)},
        {"Venus",   Planet(0.723, 0.007, 2*M_PI/225.0, 3.2, 0.0)},
        {"Earth",   Planet(1.000, 0.017, 2*M_PI/365.25, 1.7, 0.0)},
        {"Mars",    Planet(1.524, 0.093, 2*M_PI/687.0, 6.0, 0.0)}
    };

    double t_now = 9569.0; // days since t0

    for (auto& [name, planet] : planets) {
        std::vector<double> xs;
        std::vector<double> ys;

        // Draw orbit
        for (double t = 0; t <= 10000; t += 1.0) {
            orbital_pos pos = planet.position(t);
            xs.push_back(pos.x);
            ys.push_back(pos.y);
        }
        plot(xs, ys)->display_name(name);

        // Draw current position
        orbital_pos cur = planet.position(t_now);
        plot({cur.x}, {cur.y}, "o")->display_name(name + " now");
    }

    axis(equal);
    xlabel("X (AU)");
    ylabel("Y (AU)");
    title("Inner Solar System Orbits with Ellipticity");
    legend();
    show();

    return 0;
}