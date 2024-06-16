#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std;
using namespace std::chrono_literals;

class Talker : public rclcpp::Node
{
    public:
        Talker()
           :Node("talker_node")
           {
               publisher = this->create_publisher<std_msgs::msg::String>("talker", 10);
               timer = this->create_wall_timer(
               500ms,
               bind(&Talker::timer_callback, this)
               );
           }
      

    private:
        void timer_callback()
        {
            auto msg = std_msgs::msg::String();
            msg.data = "Calling all autobots";
            publisher->publish(msg);
        }
        rclcpp::TimerBase::SharedPtr timer;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
};

int main(int argc, char * argv[])
{
rclcpp::init(argc, argv);
rclcpp::spin(make_shared<Talker>());
rclcpp::shutdown();
return 0;
}
