%include <std_shared_ptr.i>

%include "util.i"

%{
#include "instance/instance.hpp"
%}


%include "instance/instance.hpp"
//%template(Vec3f) instance::Vec3<float>;
//using instance::Vec3f = instance::Vec3<float>;

IGNORE_ALL

EXPOSE1 event;
EXPOSE(event::EventInstance)
EXPOSE(event::~EventInstance)
EXPOSE(event::EventInstance::setState)

%include "event/EventInstance.hpp"
%shared_ptr(event::EventInstance)

UNIGNORE_ALL

%inline %{
void setInstancePos(std::shared_ptr<event::EventInstance> instance, float x, float y, float z)
{
    instance->setPosition({x, y, z});
}
%}