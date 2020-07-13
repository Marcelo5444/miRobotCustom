//
// Created by mlrig on 9/7/20.
//

#include "command.h"
#include <stdio.h>
#include<std_msgs/String.h>
#include <vector>
#include "personal_robot.h"

namespace gazebo{
   bool command::process(std::string command,personal_robot * robot) {
       //con esto divides la cadena de texto en dos partes
       std::vector<std::string> partes=split(command,' ');
        if(partes.size()==0){
            gzdbg<<"No command used"<<"\r\n";
        }else{
            switch (partes[0][0]) {
                case 'd':
                    if(partes.size()>1){
                        robot->display(partes[1]);}


            break;
            case 'p':
                //p given_union tipo valor_velocidad

                if(partes.size()>3){
                    robot->parametrizar(partes[1],partes[2],std::stod(partes[3]));

                }
                break;
                case 'm':
                    //m given_union valor_radiants

                    if(partes.size()>2){
                        robot->mover(partes[1],std::stod(partes[3]));

                    }
                    break;
        }}
        return false;
   }


}
std::vector<std::string> split(const std::string &c,char d){
    std::vector<std::string> result;
    std::stringstream  cs(c);
    std::string part;
    while(std::getline(cs,part,d)){
        //push backs appends the character part to the string
        result.push_back(part);

    }
    return result;


}