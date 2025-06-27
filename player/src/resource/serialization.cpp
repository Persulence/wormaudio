#include "serialization.hpp"

#include "cereal/archives/json.hpp"

namespace resource
{
    void writeStructure(const Handle<Project> &project, std::string filePath)
    {
        if (!filePath.ends_with(FILE_EXTENSION))
        {
            filePath.append(FILE_EXTENSION);
        }

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

    void readStructure(const Handle<Project> &project, std::string filePath)
    {
        {
            std::fstream istream{filePath, std::ios::in};
            // std::stringstream ss;
            // ss << istream.rdbuf();

            // std::cout << ss.str();

            {
                cereal::JSONInputArchive archive{istream};
                archive(*project);
            }

            istream.close();
        }
    }
}


