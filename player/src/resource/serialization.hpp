// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
