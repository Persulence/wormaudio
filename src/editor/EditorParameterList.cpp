#include "EditorParameterList.hpp"

namespace editor
{
    void EditorParameterList::rename(const parameter::Parameter &parameter, const std::string &newName)
    {
        parameter->setName(newName);
        if (const auto it = std::ranges::find(parameters, parameter); !*it)
        {
            ParameterList::insert(parameter);
        }

        parameter->setName(newName);

        changed.emit();
    }
}
