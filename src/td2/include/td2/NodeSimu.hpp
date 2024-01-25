#ifndef __NODESIMU_H__
#define __NODESIMU_H__

#include <cmath>
#include <chrono>
#include <iostream>

#include <eigen3/Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/float64_multi_array.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

// Définition des Quaternions
#include "tf2/LinearMath/Quaternion.h"
// Fonctions pour passer des Quaternions aux messages
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

// Attention à bien inclure chaque type de message !

using namespace std::chrono_literals;

using namespace std::placeholders;
using namespace Eigen;

/*
* Classe qui hérite de l'objet rclcpp::Node.
* Vous pouvez choisir de séparer votre classe dans un fichier .hpp et .cpp
*/
class NodeSimu : public rclcpp::Node {

public :
    /*
    Constructeur de votre node avec le nom du node "nodeSimu"
    */
    NodeSimu();

    ~NodeSimu();

    void integration_euler();

    Matrix<double, 3, 1> x_; // Créer une matrice de 3x1 initialisée avec des zéros

    double u1 = 0.0;
    double v = 0.0;
    double dt = 0.1;

    std::chrono::milliseconds loop_dt_ = 100ms;

    /* Fonction de callback du timer
    */
    void timer_callback();

    void init_interfaces();

    void twist_callback(const geometry_msgs::msg::Twist &cmd);

    void init_parameters();

    // void timer_callback_sinus()

    // void add(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response)

private:
    rclcpp::TimerBase::SharedPtr timer_; // objet timer
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_; // objet publisher
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_subscription_; // objet subscriber
    
    double initial_x_;
    double initial_y_;
    double initial_theta_;

    // size_t count_ = 0; // un compteur
    // rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_;
};

#endif