#include "Operand.hpp"

#include <format>
#include <string>

namespace condition
{
    std::string ConstantOperand::toString() const
    {
        return std::format("{:.2f}", value);
    }
}