//
// Created by mlrig on 8/7/20.
//
#include "../src/listener.h"
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include <stdio.h>
#include <thread>
#include "std_msgs/String.h"
#include  <gazebo/gazebo.hh>
#include "command.h"

namespace gazebo{
    void Listener::init(personal_robot *robot){
        this->robot = robot;
        //Aqui definimos la inicializacion del methodo listener
       // Listener::counter = 0;
        if(!ros::isInitialized()){
            int argc=0;
            char **argv=NULL;
            //nombre del nodo es "gazebo_client"
            ros::init(argc,argv,"gazebo_client",ros::init_options::NoSigintHandler);

        }
        this->node.reset(new ros::NodeHandle("gazebo_client"));
        ros::SubscribeOptions so=ros::SubscribeOptions::create<std_msgs::String>(
                "/personal_robot",
                1,
                boost::bind(&Listener::listener,this,_1),
                ros::VoidPtr(),&this->cola);
        this->subscriber = this->node->subscribe(so);
        ros::AdvertiseOptions ad=ros::AdvertiseOptions::create<std_msgs::String>(
                "/personal_robot_ad",
                1,
                //Cuando alguien se ponga a escuchar, llama al metodo conexion
                &this->conexion,
                //Cuando alguien deje de escuchar, llamas al metodo desconexion
                &this->desconexion,
                ros::VoidPtr(),&this->cola2);
        this->publisher = this->node->advertise(ad);
        //arranca el hilo y lo enlazada con el methodo listener
        this->threadColas=std::thread(std::bind(&Listener::thread,this));
    }
    void Listener::listener(const std_msgs::String::ConstPtr& msg){
        std::string m = msg->data.c_str();
        command::process(m, this->robot);
        gzdbg<<m<<"\r\n";


    }
    void Listener::conexion(const ros::SingleSubscriberPublisher&){
        ROS_INFO("ME CONECTO");
        //Listener::counter++;

    }
    void Listener::desconexion(const ros::SingleSubscriberPublisher&){
        ROS_INFO("ME DESCONECTO");
        //Listener::counter--;


    }
    void Listener::thread(){
        static const double timeout = 0.01;
        while(this->node->ok()){
            this->cola.callAvailable(ros::WallDuration(timeout));
           // if(Listener::counter > 0){
                std_msgs::String m;
                std::stringstream ms;
               // ms<<"HAy conectados" <<counter<<"\r\n";
                ms<<this->robot->getState()<<"\r\n";
                m.data = ms.str();
                this->publisher.publish(m);

           // }
        }
    }

}

