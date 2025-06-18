#include "OutlinePanel.hpp"

#include "editor/Editor.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    class OutlineItemComponent : public Component
    {
    public:
        OutlineItemComponent():
            icon(ImageCache::getFromFile(loadResource("icon/sound_event.png")))
        {
            label.setEditable(false, true);

            addAndMakeVisible(label);
        }

        Label label;
        Image icon;

        void paint(Graphics &g) override
        {
            if (!icon.isNull())
            {
                g.drawImage(icon, iconBounds.toFloat(), RectanglePlacement::fillDestination, false);
            }
        }

        void resized() override
        {
            auto bounds = getLocalBounds();
            iconBounds = bounds.removeFromLeft(getHeight()).reduced(4, 4);


            label.setBounds(bounds);
        }

    private:
        Rectangle<int> iconBounds;
    };

    class RootItem : public TreeViewItem
    {
    public:
        bool mightContainSubItems() override
        {
            return true;
        }
    };

    template <class T>
    class SharedResourceItem : public TreeViewItem
    {
    public:
        explicit SharedResourceItem(const resource::Handle<T> &resource) :
            resource(resource)
        {

        }

        resource::Handle<T> resource;
    };

    class SoundEventItem : public SharedResourceItem<event::Event>
    {
    public:
        explicit SoundEventItem(const resource::Handle<event::Event> &resource) :
            SharedResourceItem(resource) {}

    private:
        bool mightContainSubItems() override
        {
            return true;
        }

        class Comp : public OutlineItemComponent
        {

        };

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<Comp>();

            ptr->label.getTextValue().referTo(resource->nameValue());

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
        root(std::make_unique<RootItem>())
    {
        auto& editor = editor::getInstance();

        addAndMakeVisible(treeView);
        treeView.setRootItem(root.get());

        auto eventItem = new SoundEventItem{editor.getEvent()};
        // auto machine = new StateMachineItem{};
        // auto state1 = new StateItem{};
        // auto state2 = new StateItem{};
        // auto state3 = new StateItem{};

        // machine->addSubItem(state1);
        // machine->addSubItem(state2);
        // machine->addSubItem(state3);
        // eventItem->addSubItem(machine);

        treeView.getRootItem()->addSubItem(eventItem);
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
