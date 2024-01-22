#include <cmath>
#include <eigen3/Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/float64multi_array.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

// Attention à bien inclure chaque type de message !

using namespace std::chrono_literals;
std::chrono::milliseconds loop_dt_ = 100ms;

using namespace std::placeholders;
using namespace Eigen;

/*
* Classe qui hérite de l'objet rclcpp::Node.
* Vous pouvez choisir de séparer votre classe dans un fichier .hpp et .cpp
*/
class NodeSimu :
    public :
    /*
    Constructeur de votre node avec le nom du node "nodeSimu"
    */
    NodeSimu() : Node("nodeSimu");

    Matrix<double, 3, 1> x_ = Matrix<double, 3, 1>::Zero(); // Créer une matrice de 3x1 initialisée avec des zéros
    Matrix<double, 3, 1> dx_ = Matrix<double, 3, 1>::Zero();
    dx_(0) = x(1);
    double dt = 0.1;
    x_ = dx_*dt;

    /* Fonction de callback du timer
    */
    void timer_callback();

    void timer_callback_sinus()

    void add(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response)

    rclcpp::TimerBase::SharedPtr timer_; // objet timer
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; // objet publisher
    size_t count_ = 0; // un compteur
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_;