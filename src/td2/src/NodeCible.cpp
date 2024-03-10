#include "td2/NodeCible.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

NodeCible::NodeCible() : Node("nodeCible") {
    init_interfaces();
    init_parameters();
}

NodeCible::~NodeCible() {}

void NodeCible::init_interfaces() {
    publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("pose_cible", 10);
    publisher_marker_ = this->create_publisher<visualization_msgs::msg::Marker>("marker_cible", 10);
    subscription_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_cible", 10, std::bind(&NodeCible::cmd_callback, this, _1));
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    timer_ = this->create_wall_timer(loop_dt_, std::bind(&NodeCible::timer_callback, this));
}

void NodeCible::init_parameters() {
    std::vector<double> x_cible_init = {0., 0.};
    this->declare_parameter<std::vector<double>>("x_cible", x_cible_init);
    std::vector<double> x_cible_param = this->get_parameter_or("x_cible", x_cible_init);
    x_cible << x_cible_param[0], x_cible_param[1], 0.;
    dx_cible << 0., 0., 0.;
}

void NodeCible::dyn() {
    x_cible += dx_cible * dt;
}

void NodeCible::pose_cible() {
    geometry_msgs::msg::PoseStamped msg;
    msg.header.stamp = this->now();
    msg.header.frame_id = "map";
    msg.pose.position.x = x_cible(0);
    msg.pose.position.y = x_cible(1);
    msg.pose.position.z = 0;
    tf2::Quaternion q;
    q.setRPY(0, 0, x_cible(2));
    msg.pose.orientation = tf2::toMsg(q);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%f' '%f'", msg.pose.position.x, msg.pose.position.y);
    publisher_->publish(msg);
}

void NodeCible::visualisation() {
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = this->now();
    marker.ns = this->get_namespace();
    marker.id = 2;
    marker.type = visualization_msgs::msg::Marker::SPHERE;
    marker.action = visualization_msgs::msg::Marker::ADD;
    marker.pose.position.x = x_cible(0);
    marker.pose.position.y = x_cible(1);
    marker.pose.position.z = 0;
    tf2::Quaternion q;
    q.setRPY(0, 0, x_cible(2));
    marker.pose.orientation = tf2::toMsg(q);
    marker.scale.x = 1.;
    marker.scale.y = 1.;
    marker.scale.z = 1.;
    marker.color.a = 1.;
    marker.color.r = 1.;
    marker.color.g = 0.0;
    marker.color.b = 0.0;
    publisher_marker_->publish(marker);
}

void NodeCible::transf_broad() {
    geometry_msgs::msg::TransformStamped transform;
    std::string namespace_name = this->get_namespace();

    transform.header.stamp = this->get_clock()->now();
    transform.header.frame_id = "map";
    transform.child_frame_id = namespace_name + "_cible";

    tf2::Quaternion q;
    q.setRPY(0, 0, x_cible(2));

    transform.transform.translation.x = x_cible(0);
    transform.transform.translation.y = x_cible(1);
    transform.transform.rotation = tf2::toMsg(q);

    tf_broadcaster_->sendTransform(transform);
}

void NodeCible::timer_callback() {
    this->dyn();
    this->pose_cible();
    this->visualisation();
    this->transf_broad();
}

void NodeCible::cmd_callback(const geometry_msgs::msg::Twist &cmd) {
    dx_cible(0) = cmd.linear.x;
    dx_cible(1) = cmd.linear.y;
    dx_cible(2) = cmd.angular.z;
}