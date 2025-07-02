#include "OutlineTypes.hpp"

#include "OutlineItemComponent.hpp"
#include "SharedResourceOutlineItem.hpp"
#include "browser/FileDragSource.hpp"
#include "browser/element/ElementDragSource.hpp"
#include "canvas/InspectorSelectionManager.hpp"
#include "item/ElementItems.hpp"
#include "editor/Editor.hpp"
#include "event/EventDef.hpp"
#include "inspector/InspectorRoot.hpp"
#include "item/Transition.hpp"
#include "parameter/ParameterConfigPanel.hpp"
#include "resource/ChoiceElement.hpp"
#include "resource/ClipElement.hpp"
#include "transition/TransitionPropertyPanel.hpp"

namespace ui
{
    using namespace juce;
    using namespace resource;

    class SoundEventItem : public SharedResourceItem<event::EventDef>
    {
    public:
        explicit SoundEventItem(const Handle<event::EventDef> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>(this, "icon/sound_event.png");

            ptr->label.setData(resource->nameValue());

            return ptr;
        }
    };

    class StateMachineDefinitionItem : public SharedResourceItem<sm::StateMachineDefinition>
    {
    public:
        explicit StateMachineDefinitionItem(const Handle<sm::StateMachineDefinition> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>(this, "icon/folder.png");

            ptr->label.setText("State machine", dontSendNotification);
            ptr->label.setEditable(false, false);

            return ptr;
        }
    };

    class ParameterListItem : public SharedResourceItem<event::ParameterList>, public editor::EditorParameterList::Changed::Listener
    {
    public:
        explicit ParameterListItem(const Handle<event::ParameterList> &resource) :
            SharedResourceItem(resource)
        {
            editor::getInstance().getEditorParameters().changed.setup(this, [this]{ refresh(); });
        }

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>(this, "icon/folder.png");
            ptr->label.setText("Global parameters", dontSendNotification);
            return ptr;
        }
    };

    class ParameterDefItem : public SharedResourceItem<parameter::ParameterDef>
    {
    public:

        explicit ParameterDefItem(const Handle<parameter::ParameterDef> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>(this, "icon/parameter.png");
            ptr->label.setData(resource->getNameAsValue());
            return ptr;
        }

        bool mightContainSubItems() override { return false; }

        void itemSelectionChanged(bool isNowSelected) override
        {
            if (auto parent = findSelectionManager<InspectorSelectionManager>())
            {
                if (isNowSelected)
                {
                    auto root = InspectorRoot::wrap(std::make_unique<ParameterProperties>(resource));
                    parent->select(SimpleSelectionTarget::of(std::move(root)));
                }
                else
                {
                    parent->deselectAll();
                }
            }
        }
    };

    class ElementListItem : public SharedResourceItem<event::ElementList>
    {
    public:
        explicit ElementListItem(const Handle<event::ElementList> &resource) :
            SharedResourceItem(resource) {}

        std::unique_ptr<Component> createItemComponent() override
        {
            auto ptr = std::make_unique<OutlineItemComponent>(this, "icon/folder.png", false);
            ptr->label.setText("Elements", dontSendNotification);
            return ptr;
        }

        bool isInterestedInDragSource(const DragAndDropTarget::SourceDetails &dragSourceDetails) override
        {
            return FileDragSource::test(dragSourceDetails);
        }

        void itemDropped(const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex) override
        {
            if (auto source = FileDragSource::test(dragSourceDetails))
            {
                auto asset = editor::getInstance().createAsset(source->getFile());
                auto handle = resource->reg(std::make_unique<element::ClipElement>(asset));
                refresh();
            }
        }

        bool customComponentUsesTreeViewMouseHandler() const override
        {
            return true;
        }

        void itemClicked(const MouseEvent& event) override
        {
            if (event.mods.isRightButtonDown())
            {
                PopupMenu menu;
                menu.addSectionHeader("Element");
                menu.addItem("New choice element", [this]
                {
                    auto element = std::make_unique<element::ChoiceElement>();
                    resource->reg(std::move(element));
                    refresh();
                });
                menu.showMenuAsync(PopupMenu::Options{});
            }
        }
    };

#define REG(Type, factory) reg<Type>([](auto handle) { return factory; });

    void OutlineTypeRegistry::regDefaults()
    {
        using namespace outline;

        // registry.reg<event::Event>([](auto handle) { return std::make_unique<SoundEventItem>(handle); });
        REG(event::EventDef, make_unique<SoundEventItem>(handle); )
        REG(sm::StateMachineDefinition, make_unique<StateMachineDefinitionItem>(handle); )
        REG(sm::StateDef, make_unique<StateDefItem>(handle); )
        REG(sm::Transition1, make_unique<TransitionItem>(handle); )
        REG(event::ParameterListImpl, make_unique<ParameterListItem>(handle); )
        REG(parameter::ParameterDef, make_unique<ParameterDefItem>(handle); )
        REG(event::ElementList, make_unique<ElementListItem>(handle); )

        REG(element::ClipElement, make_unique<ElementItem>(handle); )
        REG(element::ChoiceElement, make_unique<ChoiceElementItem>(handle); )
    }
}
