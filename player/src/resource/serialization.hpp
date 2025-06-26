#pragma once

#include <fstream>

#include "Project.hpp"

namespace resource
{
    constexpr std::string FILE_EXTENSION = ".proj";

    void writeStructure(const Handle<Project> &project, std::string filePath);
}
