// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
EXPOSE1 event::EventInstance;
EXPOSE1 event::~EventInstance;
EXPOSE1 event::EventInstance::setState;
EXPOSE1 event::EventInstance::transport;
%feature("immutable", "1") event::EventInstance::transport;

%include "event/EventInstance.hpp"
%shared_ptr(event::EventInstance)

UNIGNORE_ALL

%inline %{
void setInstancePos(std::shared_ptr<event::EventInstance> instance, float x, float y, float z)
{
    instance->setPosition({x, y, z});
}
%}