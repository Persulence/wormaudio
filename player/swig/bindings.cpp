#include "bindings.h"

#include "resource/serialization.hpp"

namespace binding
{
    void sanityCheck()
    {
        std::cout << "You are not insane.\n";
    }


    NSystem NSystem::load(const std::string &path)
    {
        resource::Handle<resource::Project> project = resource::make<resource::Project>(
                std::make_unique<asset::AssetManager>(false));

        resource::readStructure(project, path);

        return NSystem{project};
    }
}
