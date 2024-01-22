#include "NodeSimu.hpp"


/* Constructeur de votre node avec le nom du node "nodeSimu"
*/
NodeSimu() : Node("nodeSimu") {
    // Créer un publisher de type std_msgs/msg/String sur le topic "topic", avec
    // une liste d'attente de 10 messages maximum
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    
    // Créer un service de type std_srvs/srv/Trigger sur le topic "status_boat"
    // avec la fonction add comme callback
    service_ = this->create_service<std_srvs::srv::Trigger>("status_boat", std::bind(&NodeSimu::add, this, _1, _2));
    
    // Créer un timer qui appelle la fonction time_callback toutes les 500ms
    timer_ = this->create_wall_timer(500ms, std::bind(&NodeSimu::timer_callback_sinus, this));
    // À noter qu'il existe plusieurs base de temps possible
}

/* Fonction de callback du timer
*/
void timer_callback() {
    // Créer un object message de type String
    auto message = std_msgs::msg::String();
    // Rempli le contenu du message
    message.data = "Hello, world! " + std::to_string(count_++);
    // Affiche un log dans la console (format de fprintf)
    // Il est également possible d'utiliser RCLCPP_WARN
    // En dehors d'un node, on peut utiliser rclcpp::get_logger("rclcpp")
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    // Publie le message en utilisation l'objet publisher
    publisher_->publish(message);
}

void timer_callback_sinus() {
    auto message = std_msgs::msg::String();
    double time = this->now().seconds();  // Obtenez le temps actuel en secondes
    double value = sin(time);  // Calculez la valeur de la sinusoïde en fonction du temps
    message.data = "Sinusoid value: " + std::to_string(value);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
}

void add(const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
            std::shared_ptr<std_srvs::srv::Trigger::Response> response) {

        // Remplissez les champs de réponse avec les informations nécessaires
        response->success = true;
        response->message = std::string("Nom du Bateau : Titanic, État du Moteur : ") + (response->success ? "On" : "Off");

        // Affichez un log indiquant l'état du moteur
        RCLCPP_INFO(this->get_logger(), "État du moteur : %s", response->success ? "On" : "Off");
    }

