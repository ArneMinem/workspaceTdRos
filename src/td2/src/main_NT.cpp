#include "td2/NodeTourelle.hpp"


int main(int argc, char * argv[]) 
{
    // Initialise ROS 2 pour l'executable
    rclcpp::init(argc, argv);

    // Créer le node
    std::shared_ptr<rclcpp::Node> node = std::make_shared<NodeTourelle>();

    // Met en attente le node en écoutant d'éventuelles demandes de service
    rclcpp::spin(node);

    // Coupe ROS 2 pour l'executable
    rclcpp::shutdown();
    return 0;
}