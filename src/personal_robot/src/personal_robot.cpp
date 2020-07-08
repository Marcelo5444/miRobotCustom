//
// Created by mlrig on 7/7/20.
//
#include "personal_robot.h"
#include "listener.h"
#include  <gazebo/gazebo.hh>
namespace gazebo{

class personal_robot: public ModelPlugin{
    Listener *listener;
    virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf){
    gzdbg<<"Hola Mundo\r\n";
    listener = new Listener();
    //Llamamos al metodo init asi
    listener->init(); }



};
//para que gazebo registre el objeto
GZ_REGISTER_MODEL_PLUGIN(personal_robot);

}