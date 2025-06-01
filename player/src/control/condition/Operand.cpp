module;

#include <format>
#include <string>

module control;

namespace condition
{
    std::string ConstantOperand::toString() const
    {
        return std::format("{:.2f}", value);
    }
}