#include "td2/NodeControl.hpp"
#include "tf2/utils.h"

using namespace std::chrono_literals;
using namespace std::placeholders;
using namespace Eigen;

/* Constructeur de votre node avec le nom du node "NodeControl"
*/
NodeControl::NodeControl() : Node("nodeControl") {
    this->init_interfaces();
    this->init_parameters();
}


NodeControl::~NodeControl() {
    // destructeur
}

/* Fonction de callback du timer
*/
void NodeControl::timer_callback() {
    this->control();
}

void NodeControl::init_interfaces() {
    // Créer un publisher pour publier des messages
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd", 10);

    // Créer un timer qui appelle la fonction timer_callback toutes les 100ms
    timer_ = this->create_wall_timer(loop_dt_, std::bind(&NodeControl::timer_callback, this));

    // Créer un subscriber pour recevoir des commandes de type PoseStamped
    subscription_bat = this->create_subscription<geometry_msgs::msg::PoseStamped>("pos_bat", 10, std::bind(&NodeControl::pos_callback, this, _1));

    // Créer un subscriber pour recevoir les positions de la cible
    subscription_cible = this->create_subscription<geometry_msgs::msg::PoseStamped>("pose_cible", 10, std::bind(&NodeControl::cible_callback, this, _1));
}

void NodeControl::init_parameters() {
    
    x_cible << 0.0, 0.0;

    x_bat << 0.0 , 0.0;
    theta = 0.0;
}

void NodeControl::control() {
    Matrix<double, 2, 1> proj;  // Projection de la cible sur l'axe x du bateau
    proj(0) = x_cible(0);
    proj(1) = x_bat(1);
    double phi = acos((proj - x_bat).norm()/(x_cible - x_bat).norm());  // Angle entre l'axe x du bateau et la cible
    // Ajustement de phi en fonction du cadran dans lequel se trouve la cible
    if ((x_cible(0) < x_bat(0)) && (x_cible(1) > x_bat(1))) {  // Cible dans le cadran en haut à gauche
        phi = M_PI - phi;
    }
    else if ((x_cible(0) < x_bat(0) && (x_cible(1) < x_bat(1)))) {  // Cible dans le cadran en bas à gauche
        phi = M_PI + phi;
    }
    else if ((x_cible(0) > x_bat(0) && (x_cible(1) < x_bat(1)))) {  // Cible dans le cadran en bas à droite
        phi = -phi;
    }
    double delta = phi - theta;  // Angle entre le cap du bateau et la cible
    double e = 2 * atan(tan(delta/2));  // Erreur de cap

    // Calcul de la commande
    if(e > M_PI/4) {
        u1 = -0.6;  // On tourne à fond à droite
    }
    else {
        u1 = kp * e;
        // Saturation de la commande
        if(u1 > 0.6) {
            u1 = 0.6;
        }
        else if(u1 < -0.6) {
            u1 = -0.6;
        }
    }

    if (std::isnan(u1)) {
        u1 = -0.6;
    }

    // Création du message
    auto cmd = geometry_msgs::msg::Twist();
    cmd.angular.z = u1;
    // Publication du message
    RCLCPP_INFO(this->get_logger(), "Publishing u1 : %f", u1);
    publisher_->publish(cmd);
}

void NodeControl::pos_callback(const geometry_msgs::msg::PoseStamped &msg) {
    // Affichage de la position du bateau dans le terminal
    RCLCPP_INFO(this->get_logger(), "Position du bateau (x, y, theta): %f %f %f", msg.pose.position.x, msg.pose.position.y, msg.pose.orientation.z);

    x_bat(0) = msg.pose.position.x;
    x_bat(1) = msg.pose.position.y;

    tf2::Quaternion q(msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z, msg.pose.orientation.w);
    // theta = tf2::getYaw(q);
    theta = atan2(2.0*(q.w()*q.z() + q.x()*q.y()), 1.0 - 2.0*(q.y()*q.y() + q.z()*q.z()));
}

void NodeControl::cible_callback(const geometry_msgs::msg::PoseStamped &msg) {
    // Affichage de la position de la cible dans le terminal
    RCLCPP_INFO(this->get_logger(), "Position de la cible (x, y): %f %f", msg.pose.position.x, msg.pose.position.y);

    x_cible(0) = msg.pose.position.x;
    x_cible(1) = msg.pose.position.y;
}