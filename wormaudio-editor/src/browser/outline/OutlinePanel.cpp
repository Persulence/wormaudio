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

#include "OutlinePanel.hpp"

#include "editor/Editor.hpp"
#include "outline/OutlineItemComponent.hpp"
#include "outline/SharedResourceOutlineItem.hpp"
#include "util/GuiResources.hpp"
#include "outline/OutlineTypes.hpp"

namespace ui
{
    using namespace juce;

    class RootItem : public SharedResourceItem<resource::Project>
    {
    public:
        explicit RootItem(const resource::Handle<resource::Project> &resource_) :
            SharedResourceItem(resource_)
        {
            setOpen(true);
        }

        bool mightContainSubItems() override
        {
            return true;
        }

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>(this);

            ptr->label.setEditable(false, false);
            ptr->label.setText("Project", dontSendNotification);

            return ptr;
        }

        void itemClicked(const MouseEvent& event) override
        {
            if (event.mods.isRightButtonDown())
            {
                PopupMenu menu;
                menu.addItem("New Sound Def", [this]
                {
                    resource::Handle<event::EventDef> eventDef = event::createEventDef();
                    resource->addEvent(eventDef);
                    editor::getInstance().setCurrentEvent(eventDef, true);

                    auto owningResult = OutlineTypeRegistry::getInstance().get(eventDef).release();
                    addSubItem(owningResult);

                    if (const auto shared = dynamic_cast<SharedResourceItemBase*>(owningResult))
                    {
                        juce::MessageManager::callAsync([shared]
                        {
                            shared->setSelected(true, true);
                            shared->rename();
                        });
                    }
                });
                menu.showMenuAsync(PopupMenu::Options{});
            }
        }
    };

    OutlinePanel::OutlinePanel():
        root(std::make_unique<RootItem>(editor::getInstance().getProject()))
    {
        setRootItem(root.get());
        // setHasFocusOutline(true);

        // auto& registry = OutlineTypeRegistry::getInstance();

        // auto soundEvent = registry.get(editor.getEvent());
        // treeView.getRootItem()->addSubItem(soundEvent.release());

        commands()
            .add(CommandAction{Commands::RENAME, [this](auto&)
            {
                if (getNumSelectedItems() > 0)
                {
                    if (auto selected = getSelectedItem(0))
                    {
                        if (auto component = getItemComponent(selected))
                        {
                            if (auto custom = dynamic_cast<OutlineItemComponent*>(component->getChildComponent(0)))
                            {
                                custom->rename();
                            }
                        }
                    }
                }
            }})
            .add(CommandAction{Commands::DEL, [this](auto&)
            {
                if (getNumSelectedItems() > 0)
                {
                    if (auto selected = dynamic_cast<SharedResourceItemBase*>(getSelectedItem(0)))
                    {
                        if (selected->remove())
                        {
                            const auto index = selected->getIndexInParent();
                            selected->getParentItem()->removeSubItem(index, true);
                        }
                    }
                }
            }})
            .finish();
    }

    OutlinePanel::~OutlinePanel()
    {
        setRootItem(nullptr);
    }

    void OutlinePanel::paint(Graphics &g)
    {
        g.setColour(Colours::grey);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 5);
    }
}
