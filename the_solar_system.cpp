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

struct orbital_pos {
    double x, y;
};

std::pair<int, std::string> assign_planet_parameters(const std::string& name){
        int marker_size;
        std::string color;
        std::cout << name << ": calculating trajectory" << std::endl;

        if (name == "Mercury"){
            marker_size = 4;
            color = "gray";
        } else if (name == "Venus"){
            marker_size = 9;
            color = "magenta";
        } else if (name == "Earth"){
            marker_size = 10;
            color = "blue";
        } else if (name == "Mars"){
            marker_size = 5;
            color = "red";
        } else{
            marker_size = 10;
            color = "black";
        };

    return {marker_size, color};
}


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
    Planet(double a,       // semi-major axis (AU)
           double e,       // eccentricity. 0 = circle, <1 = ellipse
           double omega,   // angular velocity (rad/day)
           double theta0,  // starting angle at t0
           double t0)      // starting time
        : a(a),
          e(e),
          omega(omega),
          theta0(theta0),
          t0(t0) {}

    orbital_pos position(double t) const {
        double theta = omega * (t - t0) + theta0;
        double r = a * (1 - e * e) / (1 + e * std::cos(theta));
        return {r * std::cos(theta), r * std::sin(theta)};
    }

private:
    double a;      // semi-major axis (AU)
    double e;      // eccentricity. 0 = circle, <1 = ellipse
    double omega;  // angular velocity (rad/day)
    double theta0; // starting angle at t0
    double t0;     // starting time
};

int main() {
    using namespace matplot;

    std::cout << "Solar System Simulation\n";

    auto f = figure(true);
    hold(on);

    // Colors for planets' orbit lines
    std::vector<std::string> orbit_colors = {"gray", "orange", "blue", "red"};
    std::vector<std::string> planet_colors = {"darkgray", "goldenrod", "blue", "red"};

    // Planets: a (AU), e, omega(rad/day), theta0(rad), t0
    // Starting angles based on Jan 1st, 2000
    std::vector<std::pair<std::string, Planet>> planets = {
        {"Mercury", Planet(0.387, 0.206, 2*M_PI/88.0, 4.1, 0.0)},
        {"Venus",   Planet(0.723, 0.007, 2*M_PI/225.0, 3.2, 0.0)},
        {"Earth",   Planet(1.000, 0.017, 2*M_PI/365.25, 1.7, 0.0)},
        {"Mars",    Planet(1.524, 0.093, 2*M_PI/687.0, 6.0, 0.0)}
    };

    // double t_now = 9569.0; // days since t0, Mar 14th 2026 (Pi Day!)
    double t_now = 0.0;

    for (size_t i = 0; i < planets.size(); ++i) {
        auto& [name, planet] = planets[i];
        std::vector<double> xs;
        std::vector<double> ys;

        // Draw orbit as a line (do not label in legend)
        for (double t = 0; t <= 10000; t += 1.0) {
            orbital_pos pos = planet.position(t);
            xs.push_back(pos.x);
            ys.push_back(pos.y);
        }

        // Determine the proper size and color of the planet
        auto [mark_size, planet_color] = assign_planet_parameters(name);
        auto orbit_line = plot(xs, ys);
        orbit_line->color(planet_color);
        std::string orbital_legend_name = name + "'s Orbit";
        orbit_line->display_name(orbital_legend_name);           // show in legend

        // Draw current planet position as a circle using scatter
        orbital_pos cur = planet.position(t_now);
        std::vector<double> px = {cur.x};
        std::vector<double> py = {cur.y};
        auto marker = scatter(px, py);

        marker->marker_face(true);
        marker->marker_size(mark_size);
        marker->color(planet_color);
        marker->display_name(name);
    }

    // Draw the Sun at the center using scatter
    orbital_pos sun_pos = {0.0, 0.0};
    std::vector<double> sx = {sun_pos.x};
    std::vector<double> sy = {sun_pos.y};
    auto sun_marker = scatter(sx, sy);
    sun_marker->marker_face(true);
    sun_marker->marker_size(20);               // Sun marker size
    sun_marker->color("yellow");
    sun_marker->display_name("Sun");           // show in legend

    // Complete plot attributes
    axis(equal);
    xlabel("X (AU)");
    ylabel("Y (AU)");
    title("Inner Solar System Orbits");
    legend();
    show();

    return 0;
}
