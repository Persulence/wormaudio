// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

%include <std_shared_ptr.i>

%{
#include "runtime.b.hpp"
%}

%include "util.i"

%shared_ptr(event::EventInstance)

//IGNORE_ALL

//EXPOSE1 binding;
////EXPOSE1 binding::NRuntime;
//EXPOSE1 binding::NRuntime::NRuntime;
//EXPOSE1 binding::NRuntime::~NRuntime;
//EXPOSE1 binding::NRuntime::connectToDevice;
//EXPOSE1 binding::NRuntime::disconnect;
//EXPOSE1 binding::NRuntime::instantiate;
//EXPOSE1 binding::NRuntime::instantiate;

%typemap(javacode) binding::MessageThreadManager %{
%}

%include "runtime.b.hpp"
//UNIGNORE_ALL