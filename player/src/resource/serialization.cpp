#include "serialization.hpp"

#include "cereal/archives/json.hpp"

void resource::writeStructure(const Handle<Project> &project, std::string filePath)
{
    if (!filePath.ends_with(FILE_EXTENSION))
    {
        filePath.append(FILE_EXTENSION);
    }

    std::fstream ostream{filePath, std::ios::out};
    {
        cereal::JSONOutputArchive archive{ostream};
        archive(*project);
    }

    ostream.close();
}
