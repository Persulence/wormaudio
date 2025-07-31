// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once
#include <memory>

#include "PropertyWidget.hpp"

namespace ui
{

    // Creates the property fields for an object
    class PropertyFiller : public PropertyMember
    {
    public:
        struct SectionHeader : public juce::Label
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
        void paint(juce::Graphics &g) override;
        [[nodiscard]] int getDesiredHeight() const override;
        void refresh(PropertyFiller* child = nullptr);

        /// Creates all property components. Must be called in the constructor. Also called when properties must be refreshed.
        virtual void initProperties() = 0;

        [[nodiscard]] virtual std::unique_ptr<SectionHeader> createHeader() const { return nullptr; }

    protected:
        /// Call when a property is modified.
        void onChanged(RefreshLevel level = SOFT);
        void setHeader(std::unique_ptr<SectionHeader> header_);

        std::vector<std::shared_ptr<PropertyMember>> children;

    private:
        struct Priv;

        std::unique_ptr<SectionHeader> header;

        void addInner(const std::shared_ptr<PropertyMember> &member);
    };

    extern std::shared_ptr<PropertyFiller> EMPTY_PROPERTY_FILLER;
}
