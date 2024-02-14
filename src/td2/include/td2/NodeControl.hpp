#ifndef __NODECONTROL_H__
#define __NODECONTROL_H__

#include <cmath>
#include <chrono>
#include <iostream>

#include <functional>
#include <memory>

#include <eigen3/Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/float64_multi_array.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

// Définition des Quaternions
#include "tf2/LinearMath/Quaternion.h"
// Fonctions pour passer des Quaternions aux messages
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

// Pour les markers
#include "visualization_msgs/msg/marker.hpp"

// Attention à bien inclure chaque type de message !

using namespace std::chrono_literals;

using namespace std::placeholders;
using namespace Eigen;

/*
* Classe qui hérite de l'objet rclcpp::Node.
* Vous pouvez choisir de séparer votre classe dans un fichier .hpp et .cpp
*/
class NodeControl : public rclcpp::Node {

public :
    /*
    Constructeur de votre node avec le nom du node "NodeControl"
    */
    NodeControl();

    ~NodeControl();

private:
    /* Fonction de callback du timer
    */
    void timer_callback();

    void init_interfaces();

    void init_parameters();

    void control();

    void pos_callback(const geometry_msgs::msg::PoseStamped &msg);

    void cible_callback(const geometry_msgs::msg::PoseStamped &msg);

    Matrix<double, 2, 1> x_bat;
    double theta;
    Matrix<double, 2, 1> x_cible;
    double u1;
    float kp = 1;

    std::chrono::milliseconds loop_dt_ = 40ms;
    rclcpp::TimerBase::SharedPtr timer_; // objet timer
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; // objet publisher
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_cible_; // objet publisher pour la cible
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr subscription_bat; // objet subscriber pour la position du bateau
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr subscription_cible; // objet subscriber pour la position de la cible
};

#endif