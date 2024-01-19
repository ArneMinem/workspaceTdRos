#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class BoatHeadingSubscriber : public rclcpp::Node {
public:
    BoatHeadingSubscriber() : Node("minimal_subscriber") {
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "/cap", 10, std::bind(&BoatHeadingSubscriber::topic_callback, this, std::placeholders::_1)
        );
    }

private:
    void topic_callback(const std_msgs::msg::Float32::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "Received boat heading: '%f'", msg->data);
        // Ajoutez ici votre logique de traitement pour le cap du bateau
    }

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BoatHeadingSubscriber>());
    rclcpp::shutdown();
    return 0;
}
