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

        {
            std::fstream ostream{filePath, std::ios::out};
            cereal::JSONOutputArchive archive{ostream};
            archive(*project);
            ostream.close();
        }
    }

    void readStructure(const Handle<Project> &project, std::string filePath)
    {
        {
            std::fstream istream{filePath, std::ios::in};
            cereal::JSONInputArchive archive{istream};
            archive(*project);
            istream.close();
        }
    }
}


