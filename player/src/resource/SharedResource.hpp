
#pragma once
#include <memory>

namespace resource
{
    class SharedResource
    {

    };

    using ResourceHandle = std::shared_ptr<SharedResource>;

    template<class T> requires std::convertible_to<T&, SharedResource&>
    using Handle = std::shared_ptr<T>;
}
