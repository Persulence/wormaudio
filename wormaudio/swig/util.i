// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

%define IGNORE_ALL %ignore ""; %enddef

%define UNIGNORE_ALL %rename("%s") ""; %enddef

%define EXPOSE(name)
%rename("%s") name;
%enddef

#define EXPOSE1 %rename("%s")
