#include "td2/NodeSimu.hpp"


/* Constructeur de votre node avec le nom du node "nodeSimu"
*/
NodeSimu::NodeSimu() : Node("nodeSimu") {
    x_ = Matrix<double, 3, 1>::Zero();
    init_interfaces();
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
    // Créer un object message de type PoseStamped
    auto message = geometry_msgs::msg::PoseStamped();

    message.pose.position.x = x_[0];
    message.pose.position.y = x_[1];
    message.pose.position.z = 0;

    tf2::Quaternion q; // Attention ceci n'est pas un message Quaternion du package geometry_msgs
    q.setRPY(0, 0, x_[2]);
    message.pose.orientation = tf2::toMsg(q); // Converti le Quaternion en message (orientation et de type geomtry_msgs::msg::Quaternion)

    message.header.stamp = this->now();
    publisher_->publish(message);

    this->integration_euler();
}

void NodeSimu::init_interfaces() {
    // Créer un publisher pour publier des messages
    publisher_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("topic_simu", 10);

    // Créer un timer qui appelle la fonction timer_callback toutes les 500ms
    timer_ = this->create_wall_timer(1000ms, std::bind(&NodeSimu::timer_callback, this));

    // Créer un subscriber pour recevoir des commandes de type Twist
    twist_subscription_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", 10, std::bind(&NodeSimu::twist_callback, this, _1));
}

void NodeSimu::twist_callback(const geometry_msgs::msg::Twist &cmd) {
    // Affichage de la commande Twist dans le terminal
    RCLCPP_INFO(this->get_logger(), "Commande Twist reçue : %f", cmd.angular.z);

    // Traitement de la commande Twist reçue
    u1 = cmd.angular.z;  // Utilisez la composante z de la commande Twist comme consigne de rotation
    // Autres traitements en fonction de vos besoins
}

void NodeSimu::init_parameters() {
    this->declare_parameter<double>("initial_x", 0.0);
    this->declare_parameter<double>("initial_y", 0.0);
    this->declare_parameter<double>("initial_theta", 0.0);

    initial_x_ = this->get_parameter_or("initial_x", 0.0);
    initial_y_ = this->get_parameter_or("initial_y", 0.0);
    initial_theta_ = this->get_parameter_or("initial_theta", 0.0);
}

// void timer_callback_sinus() {
//     auto message = std_msgs::msg::String();
//     double time = this->now().seconds();  // Obtenez le temps actuel en secondes
//     double value = sin(time);  // Calculez la valeur de la sinusoïde en fonction du temps
//     message.data = "Sinusoid value: " + std::to_string(value);
//     RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//     publisher_->publish(message);
// }

// void add(const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
//             std::shared_ptr<std_srvs::srv::Trigger::Response> response) {

//         // Remplissez les champs de réponse avec les informations nécessaires
//         response->success = true;
//         response->message = std::string("Nom du Bateau : Titanic, État du Moteur : ") + (response->success ? "On" : "Off");

//         // Affichez un log indiquant l'état du moteur
//         RCLCPP_INFO(this->get_logger(), "État du moteur : %s", response->success ? "On" : "Off");
//     }

