//
// Created by mlrig on 9/7/20.
//

#ifndef CUSTOM_PCKG_COMMAND_H
#define CUSTOM_PCKG_COMMAND_H
#include <stdio.h>
#include <std_msgs/String.h>
#include "personal_robot.h"
std::vector<std::string> split(const std::string &c,char d);
namespace gazebo {

    class command {
    public:
        static bool process(std::string command,personal_robot * robot);

    };

}
#endif //CUSTOM_PCKG_COMMAND_H
