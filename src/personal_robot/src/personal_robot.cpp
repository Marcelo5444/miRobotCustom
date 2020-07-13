//
// Created by mlrig on 7/7/20.
//
#include "personal_robot.h"
#include "listener.h"

#include <gazebo/gazebo.hh>
#include<map>

#include <gazebo/physics/physics.hh>
namespace gazebo{


     void personal_robot::Load (physics::ModelPtr _model, sdf::ElementPtr _sdf) {
         this->modelo = _model;
         this->sdf = _sdf;
         //Con esto ya obtenemos las uniones de nuestro robot
         loadUnions();
         gzdbg<<"Hola Mundo\r\n";
         listener = new Listener();
    //Llamamos al metodo init asi
    listener->init(this);
     //this->state = "init";
     //Si miras la documentacion, la connection se conecta mediante un subscriber.
     this->connectionUpdate = event::Events::ConnectWorldUpdateBegin(boost::bind(&personal_robot::OnUpdate,this,_1)) ;

     }
     //Cuando se triggerea el evento de WorldUpdateBegin, esta funcion se corre todo el rato
     void personal_robot::OnUpdate(const common::UpdateInfo & _info){
         common::Time actual = modelo->GetWorld()->GetSimTime();
         //En cada actualizacion pintamos el nombre de nuestras joints
         this->state = "Elementos \r\n";
         //look for input elements


         for(auto it=uniones.begin(); it!=uniones.end();it++){
             Union *_union = &it->second;
             //this->state+=it->first+"A:"+std::to_string(_union->joint->GetForce(0));
             this->state+="V:"+std::to_string(_union->joint->GetVelocity(0));
             this->state+="\r\n";
             _union->joint->SetVelocity(0,_union->velocidad);
             if(_union->moving){
                 common::Time ticActual = actual-_union->actualtime;
                 //el error es la dif del valor que queremos alcanzar y el angulo
                 double error = _union->joint->Position(0).Radian() - _union->anguloFinal;
                 double abserror = (error>0)?error:-1*error;
                 double velocidad=0;
                 //si estamos lejos,hacemos el update
                 if(abserror < 0.0001){
                     velocidad = union->pid.Update(error,ticActual);
                     _union->moving = false;
                 }else{
                     //si estamos a 0.001 del valor deseado,seteamos la velocidad a 0.
                 _union->velocidad = velocidad;}



             }

         }
     }
    void personal_robot::mover(std::string laUnion, double valor){
        Union *_union =&uniones[laUnion];
        if (_union){
            if(type=="V"){
                _union->anguloFinal=valor;
                _union.actualtime = 0;
                _union->moving = true;

            }

        }


    }
     void personal_robot::parametrizar(std::string laUnion,std::string type, double valor){
        Union *_union =&uniones[laUnion];
        if (_union){
            if(type=="V"){
            _union->velocidad=valor;
            _union->moving = false;

                    }

        }


     }

     void personal_robot::display(std::string type) {
         gzdbg<<"Hola Mundo\r\n";
          if(type=="unions"){
              //gzdbg<<"Hola Mundo\r\n";
              //this->state = "Elementos \r\n";
              //look for input elements
              std::map<std::string,physics::BasePtr> unions = search(this->modelo,physics::Entity::EntityType::JOINT);
              for(auto it=unions.begin();it!=unions.end();it++){
                  //this->state+=it->first+"\r\n";
                  this->state+=it->first;
                  //this->state+="V:"+std::to_string(_union->joint->GetVelocity(0));
                  //this->state+="vfdmnvdfmnvfm,dnvm,dfn";
              }

          }

     }
//Metodo que mediante recursion busca en el fichero los joints que tiene nuestro model, we se encuentra en el fichero de world
std::map<std::string,physics::BasePtr> personal_robot::search(physics::BasePtr container,const physics::Entity::EntityType & t) {
     unsigned  int n=container->GetChildCount();
     std::map<std::string,physics::BasePtr> resultado;
     for (int i =0;i<n;i++){
         if (container->GetChild(i)->HasType(t)){
             //Si lo encuentra lo metemos dentro del map
             resultado[container->GetChild(i)->GetName()] = container->GetChild(i);
                      }
         std::map<std::string,physics::BasePtr> resultado2 = search(container->GetChild(i),t);
         resultado.insert(resultado2.begin(),resultado2.end());

         }
     return resultado;
        //gzdbg<<"Hola Mundo\r\n";
     }

        void personal_robot::loadUnions(){
            std::map<std::string,physics::BasePtr> unions = search(this->modelo,physics::Entity::EntityType::JOINT);

            for(auto it=unions.begin();it!=unions.end();it++){
                Union   _union;
                //hacemos un casting de puntero cogiendo un objeto que es un puntero a un Joint y lo devolvemos a un objeto
                _union.joint = boost::static_pointer_cast<physics::Joint>(it->second);
                _union.pid.Init(2,1,1,0,0,_union.joint->GetVelocityLimit(0),-1*_union->joint->GetVelocityLimit(0));
                _union.actualtime = 0;
                this->uniones[it->first] =_union;
            }
     }

//para que gazebo registre el objeto
GZ_REGISTER_MODEL_PLUGIN(personal_robot);

}