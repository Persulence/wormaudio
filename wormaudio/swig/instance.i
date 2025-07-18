// Copyright (c) 2025 Thomas Paley-Menzies
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
EXPOSE1 event::EventInstance::markFreed;
EXPOSE1 event::EventInstance::canFree;
%rename("markDone") event::EventInstance::markFreed;
%rename("WASoundInstance") event::EventInstance;
%feature("immutable", "1") event::EventInstance::transport;

%include "event/EventInstance.hpp"
%shared_ptr(event::EventInstance)

UNIGNORE_ALL

%inline %{
void setInstancePos(std::shared_ptr<event::EventInstance> instance, WORMAUDIO_COORDINATE_TYPE x, WORMAUDIO_COORDINATE_TYPE y, WORMAUDIO_COORDINATE_TYPE z)
{
    instance->setPosition({x, y, z});
}
%}