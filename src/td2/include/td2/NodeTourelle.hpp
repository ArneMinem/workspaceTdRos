#ifndef __NODETOURELLE_HPP__
#define __NODETOURELLE_HPP__

#include <chrono>
#include <functional>
#include <memory>
#include <cmath>
#include <eigen3/Eigen/Dense>

#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2/utils.h"


using namespace std::chrono_literals;
using namespace Eigen;


class NodeTourelle : public rclcpp::Node
{
    public:
        NodeTourelle();

        ~NodeTourelle();

    private:
        void init_interfaces();

        void init_parameters();

        void control();

        void visualisation_tourelle();

        void transform_broadcaster();
        
        void transform_listener();

        void timer_callback();
        
        std::chrono::milliseconds loop_dt_ = 40ms;  // 25Hz
        rclcpp::TimerBase::SharedPtr timer_;  // objet timer
        rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr publisher_;  // objet publisher pour la pose de la tourelle
        rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_marker_;  // objet publisher pour afficher la tourelle
        std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;  // objet broadcaster pour un changement de repère
        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;  // objet buffer pour un changement de repère
        std::unique_ptr<tf2_ros::TransformListener> tf_listener_;  // objet listener pour un changement de repère

        double theta;
        double dt = 0.04;
        double u2;
        double tfx, tfy;
};

#endif