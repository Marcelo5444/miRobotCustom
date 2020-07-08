//
// Created by mlrig on 8/7/20.
//

#ifndef SRC_LISTENER_H
#define SRC_LISTENER_H
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include <stdio.h>
#include<thread>
#include "std_msgs/String.h"
//#include "../../../../../../../../usr/include/c++/7/thread"

namespace gazebo{
class Listener {
    private:
     std::unique_ptr<ros::NodeHandle> node;
     ros::Subscriber subscriber;
     ros::Publisher publisher;
     ros::CallbackQueue cola;
     ros::CallbackQueue cola2;
     std::thread threadColas;
    public:
        void init();
        void listener(const std_msgs::String::ConstPtr& msg);
        //Este methodo nos va a servir para ver que nodos estan suscritos
        static void conexion(const ros::SingleSubscriberPublisher&);
        static void desconexion(const ros::SingleSubscriberPublisher&);
        void thread();



};
}

#endif //SRC_LISTENER_H
