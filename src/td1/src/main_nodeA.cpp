#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_srvs/srv/trigger.hpp"

// Attention à bien inclure chaque type de message !

using namespace std::chrono_literals;
using namespace std::placeholders;

/*
* Classe qui hérite de l'objet rclcpp::Node.
* Vous pouvez choisir de séparer votre classe dans un fichier .hpp et .cpp
*/
class NodeA : public rclcpp::Node {
public:
    /* Constructeur de votre node avec le nom du node "nodeA"
    */
    NodeA() : Node("nodeA") {
        // Créer un publisher de type std_msgs/msg/String sur le topic "topic", avec
        // une liste d'attente de 10 messages maximum
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        
        // Créer un service de type std_srvs/srv/Trigger sur le topic "status_boat"
        // avec la fonction add comme callback
        service_ = this->create_service<std_srvs::srv::Trigger>("status_boat", std::bind(&NodeA::add, this, _1, _2));
        
        // Créer un timer qui appelle la fonction time_callback toutes les 500ms
        timer_ = this->create_wall_timer(500ms, std::bind(&NodeA::timer_callback_sinus, this));
        // À noter qu'il existe plusieurs base de temps possible
    }
private:
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

    rclcpp::TimerBase::SharedPtr timer_; // objet timer
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; // objet publisher
    size_t count_ = 0; // un compteur
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_;
};

int main(int argc, char * argv[]) {
    // Initialise ROS 2 pour l'executable
    rclcpp::init(argc, argv);
    // Créer le node et se met en attente de messages ou d'évènements du timer
    // Attention, cette fonction est bloquante !
    rclcpp::spin(std::make_shared<NodeA>());
    // Coupe ROS 2 pour l'executable
    rclcpp::shutdown(); 
    return 0;
}