// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "serialization.hpp"

#include "cereal/archives/json.hpp"

namespace resource
{
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

    void writeStructure(const Handle<Project> &project, const std::filesystem::path &filePath)
    {
        // if (!filePath.ends_with(FILE_EXTENSION))
        // {
        //     filePath.append(FILE_EXTENSION);
        // }

        std::fstream ostream{filePath, std::ios::out};
        // std::stringstream ss;
        
        {
            cereal::JSONOutputArchive archive{ostream};
            archive(*project);
        }

        // std::cout << ss.str();
        // ostream << ss.rdbuf();
        ostream.close();
    }

    void readStructure(const Handle<Project> &project, const std::filesystem::path &filePath)
    {
        {
            std::fstream istream{filePath, std::ios::in};

            if (!istream.good())
            {
                throw IOException{std::format("File invalid: {}", filePath.string())};
            }

            {
                cereal::JSONInputArchive archive{istream};
                archive(*project);
            }

            istream.close();
        }
    }
}


