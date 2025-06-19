#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "resource/SharedResource.hpp"
#include "resource/Asset.hpp"

namespace ui
{
    class SharedResourceItemBase : public juce::TreeViewItem
    {
    public:
        virtual void createChildren() = 0;

        void refresh(SharedResourceItemBase* origin = nullptr, bool strong = false)
        {
            if (strong)
            {
                if (const auto parent = dynamic_cast<SharedResourceItemBase*>(getParentItem()))
                {
                    parent->refresh(this, false);
                }
            }
            else
            {
                if (getOpenness() == Openness::opennessOpen)
                {
                    clearSubItems();
                    createChildren();
                }
                else
                {
                    clearSubItems();
                }
            }
        }
    };

    template <class T>
    class SharedResourceItem : public SharedResourceItemBase
    {
    public:
        explicit SharedResourceItem(const resource::Handle<T> &resource):
            resource(resource)
        {

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
            return std::make_unique<OutlineItemComponent>("icon/file.png", false);
        }

        resource::Handle<T> resource;
    };

    class AssetOutlineItem : public juce::TreeViewItem
    {
    public:
        explicit AssetOutlineItem(const asset::AssetHandle &asset) :
            asset(asset) {}

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
        auto ptr = std::make_unique<OutlineItemComponent>("icon/audio.png", false);
        ptr->label.setText(asset->getFile().getFileName(), juce::dontSendNotification);
        return ptr;
    }
}
