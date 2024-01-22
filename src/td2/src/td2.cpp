#include "NodeSimu.hpp"

int main(int argc, char * argv[]) {
    // Initialise ROS 2 pour l'executable
    rclcpp::init(argc, argv);
    // Créer le node et se met en attente de messages ou d'évènements du timer
    // Attention, cette fonction est bloquante !
    rclcpp::spin(std::make_shared<NodeSimu>());
    // Coupe ROS 2 pour l'executable
    rclcpp::shutdown(); 
    return 0;
}