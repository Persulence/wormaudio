#pragma once

#include <memory>
#include <vector>

namespace resource
{
    class SharedResource;

    template <class T>
    concept IsResource = std::convertible_to<T&, SharedResource&>;

    using ResourceHandle = std::shared_ptr<SharedResource>;

    template<class T> requires std::convertible_to<T&, SharedResource&>
    using Handle = std::shared_ptr<T>;

    class SharedResource
    {
    public:
        virtual ~SharedResource() = default;

        virtual std::vector<ResourceHandle> getChildResources()
        {
            return {};
        }
    };

}
