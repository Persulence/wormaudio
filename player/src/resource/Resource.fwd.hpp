#pragma once
#include <memory>

namespace resource
{
    class Resource;
    using ResourceHandle = std::shared_ptr<Resource>;
}
