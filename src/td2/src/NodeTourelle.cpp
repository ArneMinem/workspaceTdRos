#include "td2/NodeTourelle.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;


NodeTourelle::NodeTourelle() : Node("nodeTourelle")
{
    init_interfaces();
    init_parameters();
}

NodeTourelle::~NodeTourelle()
{
    // destructeur
}

void NodeTourelle::init_interfaces()
{
    // // Créer un publisher pour publier des messages
    // publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("pos_tourelle", 10);

    // Créer un publisher pour publier des markers
    publisher_marker_ = this->create_publisher<visualization_msgs::msg::Marker>("marker_tourelle", 10);

    // Créer un timer qui appelle la fonction timer_callback toutes les 100ms
    timer_ = this->create_wall_timer(loop_dt_, std::bind(&NodeTourelle::timer_callback, this));

    // Créer un broadcaster pour les transformations
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_unique<tf2_ros::TransformListener>(*tf_buffer_);
}

void NodeTourelle::init_parameters()
{
    // Initialisation des paramètres
    theta = 0.0;
    u2 = 0.0;
    tfx = 0.0;
    tfy = 0.0;
}

void NodeTourelle::timer_callback()
{
    // Fonction appelée à chaque tick du timer
    this->control();
    this->visualisation_tourelle();
    this->transform_broadcaster();
}

void NodeTourelle::control()
{
    this->transform_listener();
    u2 = atan2(tfy, tfx);
    theta += dt * u2;
}

void NodeTourelle::visualisation_tourelle()
{
    visualization_msgs::msg::Marker marker;
    std::string name = this->get_namespace();


    marker.header.frame_id = name + "_tourelle";
    marker.header.stamp = this->now();
    marker.ns = this->get_namespace();
    marker.id = 1;
    marker.type = visualization_msgs::msg::Marker::MESH_RESOURCE;
    marker.action = visualization_msgs::msg::Marker::ADD;

    marker.pose.position.x = 0.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0.0;

    tf2::Quaternion q;
    q.setRPY(0, 0, 0);
    marker.pose.orientation = tf2::toMsg(q);

    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;
    marker.color.a = 1.0;  // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;

    marker.mesh_resource = "package://td2/meshes/turret.dae";

    publisher_marker_->publish(marker);
}

void NodeTourelle::transform_broadcaster()
{
    geometry_msgs::msg::TransformStamped t;
    std::string name = this->get_namespace();

    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = this->get_namespace();
    t.child_frame_id = name + "_tourelle";
    t.transform.translation.x = 3.5;
    t.transform.translation.y = 0.0;
    t.transform.translation.z = 0.0;
    tf2::Quaternion q;
    q.setRPY(0, 0, theta);
    t.transform.rotation = tf2::toMsg(q);

    tf_broadcaster_->sendTransform(t);
}

void NodeTourelle::transform_listener()
{
    geometry_msgs::msg::TransformStamped tf;
    std::string name = this->get_namespace();

    try
    {
        tf = tf_buffer_->lookupTransform(name.substr(1) + "_tourelle", name.substr(1) + "cible", tf2::TimePointZero);
        tfx = tf.transform.translation.x;
        tfy = tf.transform.translation.y;
    }
    catch (tf2::TransformException &ex)
    {
        RCLCPP_WARN(this->get_logger(), "%s", ex.what());
        return;
    }
}