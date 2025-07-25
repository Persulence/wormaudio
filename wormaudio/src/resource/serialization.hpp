// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <filesystem>
#include <fstream>

#include "Project.hpp"

namespace resource
{
    constexpr std::string FILE_EXTENSION = ".proj";

    class IOException : public std::exception
    {
    public:
        explicit IOException(const std::string &message_): message(message_) {}

        const char *what() const noexcept override
        {
            return message.c_str();
        }

    private:
        std::string message;
    };

    void writeStructure(const Handle<Project> &project, const std::filesystem::path &filePath);
    void readStructure(const Handle<Project>& project, const std::filesystem::path &filePath);
}
