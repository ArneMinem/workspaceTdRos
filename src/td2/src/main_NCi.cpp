#include "td2/NodeCible.hpp"

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = std::make_shared<NodeCible>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}