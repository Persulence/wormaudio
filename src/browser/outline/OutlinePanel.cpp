#include "OutlinePanel.hpp"

#include "editor/Editor.hpp"
#include "outline/OutlineItemComponent.hpp"
#include "outline/SharedResourceOutlineItem.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    class RootItem : public SharedResourceItem<resource::Project>
    {
    public:
        explicit RootItem(const resource::Handle<resource::Project> &resource) :
            SharedResourceItem(resource) {}

        bool mightContainSubItems() override
        {
            return true;
        }

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>();

            ptr->label.setEditable(false, false);
            ptr->label.setText("Project", dontSendNotification);

            return ptr;
        }
    };


    // class StateMachineItem : public SharedResourceItem
    // {
    // public:
    //     explicit StateMachineItem(const resource::ResourceHandle &resource) :
    //         SharedResourceItem(resource) {}
    //
    // private:
    //     bool mightContainSubItems() override
    //     {
    //         return true;
    //     }
    // };
    //
    // class StateItem : public TreeViewItem
    // {
    //     bool mightContainSubItems() override
    //     {
    //         return true;
    //     }
    // };

    OutlinePanel::OutlinePanel():
        root(std::make_unique<RootItem>(editor::getInstance().getProject()))
    {
        auto& editor = editor::getInstance();

        addAndMakeVisible(treeView);
        treeView.setRootItem(root.get());

        // auto& registry = OutlineTypeRegistry::getInstance();

        // auto soundEvent = registry.get(editor.getEvent());
        // treeView.getRootItem()->addSubItem(soundEvent.release());
    }

    void OutlinePanel::resized()
    {
        Panel::resized();
        treeView.setBounds(getLocalBounds());
    }

    void OutlinePanel::paint(juce::Graphics &g)
    {
        paintBackground(g);
    }
}
