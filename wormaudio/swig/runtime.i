// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

%include <std_shared_ptr.i>

%{
#include "runtime.b.hpp"
%}

%include "util.i"

%shared_ptr(event::EventInstance)

//IGNORE_ALL

//EXPOSE1 binding;
////EXPOSE1 binding::WARuntime;
//EXPOSE1 binding::WARuntime::WARuntime;
//EXPOSE1 binding::WARuntime::~WARuntime;
//EXPOSE1 binding::WARuntime::connectToDevice;
//EXPOSE1 binding::WARuntime::disconnect;
//EXPOSE1 binding::WARuntime::instantiate;
//EXPOSE1 binding::WARuntime::instantiate;

%typemap(javacode) binding::MessageThreadManager %{
%}

%include "runtime.b.hpp"
//UNIGNORE_ALL