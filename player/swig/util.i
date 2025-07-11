%define IGNORE_ALL %ignore ""; %enddef

%define UNIGNORE_ALL %rename("%s") ""; %enddef

%define EXPOSE(name)
%rename("%s") name;
%enddef

#define EXPOSE1 %rename("%s")
