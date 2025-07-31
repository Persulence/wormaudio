// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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