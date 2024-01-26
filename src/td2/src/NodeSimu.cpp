#include "td2/NodeSimu.hpp"


/* Constructeur de votre node avec le nom du node "nodeSimu"
*/
NodeSimu::NodeSimu() : Node("nodeSimu") {
    this->init_interfaces();
    this->init_parameters();
}


NodeSimu::~NodeSimu() {
    // destructeur
}

void NodeSimu::integration_euler() {
    x_[0] += dt * cos(x_[2]) * v;
    x_[1] += dt * sin(x_[2]) * v;
    x_[2] += dt * u1;
}

/* Fonction de callback du timer
*/
void NodeSimu::timer_callback() {
    this->integration_euler();

    // Créer un object message de type PoseStamped
    auto message = geometry_msgs::msg::PoseStamped();

    message.pose.position.x = x_[0];
    message.pose.position.y = x_[1];
    message.pose.position.z = 0;

    tf2::Quaternion q; // Attention ceci n'est pas un message Quaternion du package geometry_msgs
    q.setRPY(0, 0, x_[2]);
    message.pose.orientation = tf2::toMsg(q); // Converti le Quaternion en message (orientation et de type geomtry_msgs::msg::Quaternion)

    message.header.stamp = this->now();
    message.header.frame_id = "carte";

    // Affichage du message dans le terminal et publication
    RCLCPP_INFO(this->get_logger(), "Publishing (x, y, théta): %f %f %f", message.pose.position.x, message.pose.position.y, message.pose.orientation.z);

    publisher_->publish(message);
}

void NodeSimu::init_interfaces() {
    // Créer un publisher pour publier des messages
    publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("topic_simu", 10);

    // Créer un timer qui appelle la fonction timer_callback toutes les 100ms
    timer_ = this->create_wall_timer(loop_dt_, std::bind(&NodeSimu::timer_callback, this));

    // Créer un subscriber pour recevoir des commandes de type Twist
    twist_subscription_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd", 10, std::bind(&NodeSimu::twist_callback, this, _1));

    // Créer un publisher de type visualization_msgs/msg/Marker sur le topic "visuel", avec une liste d'attente de 10 messages maximum
    publisher_marker_ = this->create_publisher<visualization_msgs::msg::Marker>("visuel", 10);
}

void NodeSimu::twist_callback(const geometry_msgs::msg::Twist &cmd) {
    // Affichage de la commande Twist dans le terminal
    RCLCPP_INFO(this->get_logger(), "Commande reçue : %f", cmd.angular.z);

    // Traitement de la commande Twist reçue
    u1 = cmd.angular.z;  // Utilisez la composante z de la commande Twist comme consigne de rotation
    // Autres traitements en fonction de vos besoins
}

void NodeSimu::init_parameters() {
    // Créer un paramètre init_pos de type tableau de double avec comme valeur par défaut {0.0, 0.0, 0.0}
     std::vector<double> init_pos_vector = {0.0, 0.0, 0.0};
    this->declare_parameter<std::vector<double>>("init_pos", init_pos_vector);

    // Récupérer la valeur du paramètre init_pos
    std::vector<double> init_pos_param = this->get_parameter_or("init_pos", init_pos_vector);
    x_ << init_pos_param[0], init_pos_param[1], init_pos_param[2];

    u1 = 0.5;
    v = 1.0;
}

void NodeSimu::visualization()
{
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = "carte";
    marker.header.stamp = this->now();
    marker.ns = "boat";
    marker.id = 0;
    marker.type = visualization_msgs::msg::Marker::MESH_RESOURCE;
    marker.action = visualization_msgs::msg::Marker::ADD;

    // Position du marker
    marker.pose.position.x = x_[0];
    marker.pose.position.y = x_[1];
    marker.pose.position.z = 0;

    // Orientation du marker
    tf2::Quaternion q; 
    q.setRPY(0, 0, x_[2]); 
    marker.pose.orientation = tf2::toMsg(q);

    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;
    marker.color.a = 1.0; // alpha = transparence
    marker.color.r = 1.0;
    marker.color.g = 1.0;
    marker.color.b = 1.0;
    marker.mesh_resource = "package://td2/meshes/boat.dae";

    publisher_marker_->publish(marker);
}