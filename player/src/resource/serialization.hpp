#pragma once

#include <filesystem>
#include <fstream>

#include "Project.hpp"

namespace resource
{
    constexpr std::string FILE_EXTENSION = ".proj";

    void writeStructure(const Handle<Project> &project, const std::filesystem::path &filePath);
    void readStructure(const Handle<Project>& project, const std::filesystem::path &filePath);
}
