//
// Created by mlrig on 7/7/20.
//


#ifndef SRC_PERSONAL_ROBOT_H
#define SRC_PERSONAL_ROBOT_H
#include "listener.h"
#include "../../../../../../../../usr/include/c++/7/string"
#include  <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
namespace gazebo {
    //structura donde estara todan las joints
    struct Union{
        gazebo::physics::JointPtr joint;
        gazebo::common::PID pid;
        gazebo::common::Time actualtime;
        double velocidad;
        double anguloFinal;
        bool moving=false;


    };
    //Declaramos Listener aqui arriba ya que sino hay un deadlock de declaraciones, vemos que hace uso de la clase listener en la linea 13.
    class Listener;
    class command;
    class personal_robot : public ModelPlugin {
        Listener *listener;
        physics::ModelPtr  modelo;
        sdf::ElementPtr  sdf;
        std::string  state;
        std::map<std::string,Union> uniones;
        double velocity;
        //puntero a la conexion
        event::ConnectionPtr connectionUpdate;
        std::map<std::string,physics::BasePtr> search(physics::BasePtr container,const physics::Entity::EntityType &);
        public:
        void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
        void parametrizar(std::string laUnion,std::string type, double valor);
        void mover(std::string laUnion, double valor);
        const std::string& getState() const {
            return state;
        }

        void display(std::string);
        void OnUpdate(const common::UpdateInfo & _info);
        void loadUnions();

    };
}
#endif //SRC_PERSONAL_ROBOT_H
