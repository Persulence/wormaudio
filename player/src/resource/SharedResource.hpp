#pragma once

#include <memory>
#include <vector>

namespace resource
{
    class SharedResource;

    template <class T>
    concept IsResource = std::convertible_to<T&, SharedResource&>;

    using ResourceHandle = std::shared_ptr<SharedResource>;

    template<IsResource T>
    using Handle = std::shared_ptr<T>;

    /// Creates a
    template<IsResource T, typename... Args>
    Handle<T> make(Args&&... args)
    {
        // Pointer implementation can be changed without affecting other code
        return std::make_shared<T, Args...>(std::forward<Args>(args)...);
    }
    // using makeResource = std::make_shared<T, Args...>;

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
