#pragma once
#include <memory>

#include "PropertyWidget.hpp"

namespace ui
{

    // Creates the property fields for an object
    class PropertyFiller : public PropertyMember
    {
    public:
        struct  SectionHeader : public juce::Label
        {
            explicit SectionHeader(const std::string &name_);

            void paint(juce::Graphics &g) override;

            int h = 20;
        };

        auto add(auto property) -> decltype(*property)&
        {
            auto& ref = *property;
            addInner(std::shared_ptr{std::move(property)});
            return ref;
        }

        void resized() override;
        [[nodiscard]] int getDesiredHeight() const override;
        void refresh(PropertyFiller* child = nullptr);

        /// Creates all property components. Must be called in the constructor. Also called when properties must be refreshed.
        virtual void initProperties() = 0;

        [[nodiscard]] virtual std::unique_ptr<SectionHeader> createHeader() const { return nullptr; }

    protected:

        /// Call when a property is modified.
        void onChanged(RefreshLevel level = SOFT);
        void setHeader(std::unique_ptr<SectionHeader> header_);

    private:
        struct Priv;

        void addInner(const std::shared_ptr<PropertyWidget> &property);
        void addInner(const std::shared_ptr<PropertyFiller>& filler);

        std::vector<std::shared_ptr<PropertyMember>> children;
        std::unique_ptr<SectionHeader> header;
    };

    extern std::shared_ptr<PropertyFiller> EMPTY_PROPERTY_FILLER;
}
