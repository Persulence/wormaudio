#include "AutomationTableInstance.hpp"

namespace automation
{
    AutomationTableInstance::AutomationTableInstance():
        AutomationInstance()
    {

    }

    PropertyInstanceContainer AutomationTableInstance::getContainer(const PropertyProviderPtr provider)
    {
        return containers.at(provider);
    }
}
