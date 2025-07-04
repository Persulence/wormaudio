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
            SharedResourceItem(resource_) {}

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
