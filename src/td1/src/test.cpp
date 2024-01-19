#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"
#include <memory>

class NodeA : public rclcpp::Node {
public:
    NodeA() : Node("boat_info_server") {
        service_ = this->create_service<std_srvs::srv::Trigger>(
            "boat_info", std::bind(&NodeA::boat_info_callback, this, std::placeholders::_1, std::placeholders::_2)
        );
    }

private:
    void boat_info_callback(
        const std::shared_ptr<rmw_request_id_t> request_header,
        const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
        std::shared_ptr<std_srvs::srv::Trigger::Response> response
    ) {
        (void)request_header;
        RCLCPP_INFO(this->get_logger(), "Received request for boat info");
        // Remplir la réponse avec le nom du bateau et l'état du moteur
        response->success = true;
        response->message = "Nom du bateau: VotreNomDeBateau, État du moteur: On";
    }

    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodeA>());
    rclcpp::shutdown();
    return 0;
}
