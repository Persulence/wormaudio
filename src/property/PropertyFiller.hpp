#pragma once
#include <memory>

#include "PropertyWidget.hpp"

namespace ui
{
    // Creates the property fields for an object
    class PropertyFiller : public PropertyMember
    {
    public:
        auto add(auto property) -> decltype(*property)&
        {
            addInner(property);
            return *property;
        }

        void resized() override;
        [[nodiscard]] float getDesiredHeight() const override;
        void refresh(PropertyFiller* child = nullptr);

        /// Creates all property components. Must be called in the constructor. Also called when properties must be refreshed.
        virtual void initProperties() = 0;

    protected:
        /// Call when a property is modified.
        void onChanged(RefreshLevel level = SOFT);

    private:
        struct Priv;

        void addInner(std::shared_ptr<PropertyWidget> property);
        void addInner(std::shared_ptr<PropertyFiller> filler);

        std::vector<std::shared_ptr<PropertyMember>> children;
    };
}
