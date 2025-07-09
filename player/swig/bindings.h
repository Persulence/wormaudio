#pragma once

#include <iostream>

// #include "resource/Project.hpp"
// #include "resource/SharedResource.hpp"

inline void ooere()
{
    // resource::Handle<resource::Project> i = resource::make<resource::Project>();
    std::cout << "ooer\n";
}

class SoundThing
{
public:
    int field;

    void memberFunction()
    {
        std::cout << "memberFunction\n";
    }


    void printField()
    {
        std::cout << field << "\n";
    }
};
