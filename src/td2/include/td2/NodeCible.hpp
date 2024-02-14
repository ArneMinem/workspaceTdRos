#ifndef __NODECIBLE_H__
#define __NODECIBLE_H__

#include <chrono>
#include <functional>
#include <memory>
#include <cmath>
#include <eigen3/Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "tf2_ros/transform_broadcaster.h"


using namespace std::chrono_literals;
using namespace Eigen;

class NodeCible : public rclcpp::Node {

public:
    NodeCible();

    ~NodeCible();

private:
    void init_interfaces();

    void init_parameters();

    void dyn();

    void pose_cible();

    void visualisation();

    void transf_broad();

    void timer_callback();

    void cmd_callback(const geometry_msgs::msg::Twist &cmd);

    std::chrono::milliseconds loop_dt_ = 40ms;  // 25Hz
    rclcpp::TimerBase::SharedPtr timer_;  // objet timer
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;  // objet publisher pour la pose de la cible
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_marker_;  // objet publisher pour afficher la cible
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;  // objet subscriber pour déplacer la cible
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;  // objet broadcaster pour un changement de repère

    Matrix<double, 2, 1> x_cible;
    Matrix<double, 2, 1> dx_cible;
    double dt = 0.04;
};

#endif