#include "EditorParameterList.hpp"

namespace editor
{
    /**
     *
     * @return true if the parameter was renamed, false if not.
     */
    bool EditorParameterList::rename(const parameter::Parameter &parameter, const std::string &newName)
    {
        // Fail if the name would conflict with an existing parameter
        if (const auto it = std::ranges::find_if(parameters, [newName](auto& p){ return p->getName() == newName; }); it != parameters.end())
        {
            auto s = (*it)->getName();
            return false;
        }

        parameter->setName(newName);
        if (const auto it = std::ranges::find(parameters, parameter); it != parameters.end())
        {
            // Already present handling?
        }
        else
        {
            ParameterList::insert(parameter);
        }

        parameter->setName(newName);

        changed.emit();
        return true;
    }
}
