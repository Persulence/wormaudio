#pragma once

#include <iostream>

// #include "resource/Project.hpp"
// #include "resource/SharedResource.hpp"

inline void ooere()
{
    // resource::Handle<resource::Project> i = resource::make<resource::Project>();
    std::cout << "ooer\n";
}

class Classe
{
public:
    int i;

    void memberFunction()
    {
        std::cout << "memberFunction\n";
    }

    const Classe* makeCopie() const
    {
        // return new Classe{i};
        return this;
    }
};
