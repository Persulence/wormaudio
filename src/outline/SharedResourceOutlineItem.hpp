// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <utility>

#include "juce_gui_basics/juce_gui_basics.h"

#include "resource/SharedResource.hpp"
#include "resource/Asset.hpp"
#include "settings/settings.hpp"
#include "OutlineTypes.hpp"
#include "OutlineItemComponent.hpp"
#include "SharedResourceOutlineItemBase.hpp"

namespace ui
{
    template <class T>
    class SharedResourceItem : public SharedResourceItemBase
    {
    public:
        explicit SharedResourceItem(const resource::Handle<T> &resource):
            resource(resource)
        {

        }

        int getItemHeight() const override
        {
            return settings::browserEntryHeight;
        }

        void itemOpennessChanged(bool isNowOpen) override
        {
            refresh();
        }

        void createChildren() override
        {
            for (auto child : resource->getChildResources())
            {
                auto result = OutlineTypeRegistry::getInstance().get(child);
                addSubItem(result.release());
            }
        }

        bool mightContainSubItems() override
        {
            return true;
        }

        std::unique_ptr<juce::Component> createItemComponent() override
        {
            return std::make_unique<OutlineItemComponent>(this, "icon/file.png", false);
        }

        bool customComponentUsesTreeViewMouseHandler() const override
        {
            return true;
        }

        void itemClicked(const juce::MouseEvent &) override
        {
            setSelected(true, true, juce::sendNotification);
        }

        void rename() override
        {
            if (const auto owner = getOwnerView())
            {
                if (auto component = owner->getItemComponent(this))
                {
                    if (auto custom = dynamic_cast<OutlineItemComponent*>(component->getChildComponent(0)))
                    {
                        custom->rename();
                    }
                }
            }
        }

        resource::Handle<T> resource;
    };

    class AssetOutlineItem : public juce::TreeViewItem
    {
    public:
        explicit AssetOutlineItem(asset::AssetHandle asset) :
            asset(std::move(asset)) {}

        bool mightContainSubItems() override
        {
            return false;
        }

        std::unique_ptr<juce::Component> createItemComponent() override;

    private:
        asset::AssetHandle asset;
    };

    inline std::unique_ptr<juce::Component> AssetOutlineItem::createItemComponent()
    {
        auto ptr = std::make_unique<OutlineItemComponent>(this, "icon/audio.png", false);
        ptr->label.setText(asset->getFile().getFileName(), juce::dontSendNotification);
        return ptr;
    }
}
