module;

#include <format>
#include <string>

module sm;

namespace condition
{
    std::string ConstantOperand::toString() const
    {
        return std::format("{:.2f}", value);
    }
}