#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class ListenerNode : public rclcpp::Node
{
    public:
       ListenerNode()
            : Node("listener_node")
            {
                subscriber = this->create_subscription<std_msgs::msg::String>(
                    "talker",
                    10,
                    std::bind(&ListenerNode::topic_callback, this, _1)
                );
            }
   private:
        void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
        {
            RCLCPP_INFO(this->get_logger(), "Received: '%s", msg->data.c_str());
        }
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ListenerNode>());
    rclcpp::shutdown();
    return 0;
}