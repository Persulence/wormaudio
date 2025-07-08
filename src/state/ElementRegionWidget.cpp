#include "ElementRegionWidget.hpp"

#include <memory>

#include "StatePropertyPanel.hpp"
#include "automation/AutomationTable.hpp"
#include "automation/Mapping.hpp"
#include "browser/FileDragSource.hpp"
#include "editor/Editor.hpp"
#include "resource/ChoiceElement.hpp"

#include "resource/ClipElement.hpp"

namespace ui
{
    using namespace juce;
    using namespace element;

    class Impl : public Component
    {

    };

    class ClipImpl : public Impl
    {
    public:
        explicit ClipImpl(resource::Handle<ClipElement> element_) :
            element(std::move(element_)) {}

        void paint(Graphics &g) override
        {
            float cornerSize = 5;
            float thickness = 2;

            auto reduced = getLocalBounds().toFloat().reduced(thickness / 2);
            g.setColour(Colours::rebeccapurple);
            g.fillRoundedRectangle(reduced, cornerSize);
            g.setColour(Colours::mediumpurple);
            g.drawRoundedRectangle(reduced, cornerSize, thickness);

            g.setColour(Colours::black);
            g.drawText(element->getName(), getLocalBounds().withTrimmedLeft(10).toFloat(), Justification::centredLeft, true);
        }

        void mouseDown(const MouseEvent &event) override
        {
            if (event.mods.isRightButtonDown())
            {
                auto& editor = editor::Editor::getInstance();

                // Menu for selecting a parameter
                PopupMenu parameters;
                for (const auto& parameter : editor.getEditorParameters().getParameters())
                {
                    parameters.addItem({parameter->getName()}, [this, &editor, parameter]
                    {
                        const automation::AutomationLink link{parameter, element->volume, automation::MappingFunction{}};
                        editor.getEvent()->getAutomation().setup(link);
                    });
                }

                PopupMenu menu;

                menu.addItem("Remove", [this]
                {
                    if (const auto parent = findParentComponentOfClass<StatePropertyPanel>())
                    {
                        parent->removeElement(element);
                    }
                });
                menu.addSubMenu("Automate volume", parameters);

                menu.showMenuAsync(PopupMenu::Options{});
            }
        }

    private:
        resource::Handle<ClipElement> element;
    };

    class ChoiceImpl : public Impl, public DragAndDropTarget
    {
    public:
        explicit ChoiceImpl(resource::Handle<ChoiceElement> element_) :
            element(std::move(element_)) {}

        void paint(Graphics &g) override
        {
            float cornerSize = 5;
            float thickness = 2;

            auto reduced = getLocalBounds().toFloat().reduced(thickness / 2);
            g.setColour(Colours::darkolivegreen);
            g.fillRoundedRectangle(reduced, cornerSize);

            g.setColour(Colours::darkgreen);
            const auto size = static_cast<float>(element->getClips().size());
            auto centreBounds = getLocalBounds().expanded(-static_cast<int>(thickness));
            for (size_t i = 0; i < size; ++i)
            {
                const float h = static_cast<float>(centreBounds.getHeight()) / size;

                auto clip = element->getClips().at(i);
                Rectangle clipBounds{static_cast<float>(centreBounds.getX()), centreBounds.getY() + i * h, static_cast<float>(centreBounds.getWidth()), h};
                clipBounds.expand(-2., -2.);

                g.fillRect(clipBounds);
            }

            g.setColour(Colours::green);
            g.drawRoundedRectangle(reduced, cornerSize, thickness);

            g.setColour(Colours::black);
            g.drawText(element->getName(), getLocalBounds().withTrimmedLeft(10).toFloat(), Justification::centredLeft, true);
        }

        bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override
        {
            return FileDragSource::test(dragSourceDetails);
        }

        void itemDropped(const SourceDetails &dragSourceDetails) override
        {
            if (auto source = FileDragSource::test(dragSourceDetails))
            {
                auto asset = editor::getInstance().createAsset(source->getFile());
                element->addClip(asset);

                repaint();
            }
        }

    private:
        resource::Handle<ChoiceElement> element;

    };

    // struct ImplVisitor
    // {
    //     std::unique_ptr<Impl> operator()(ClipElement& element) const
    //     {
    //         return std::make_unique<ClipImpl>(element);
    //     }
    //
    //     std::unique_ptr<Impl> operator()(ChoiceElement& element) const
    //     {
    //         return std::make_unique<ChoiceImpl>(element);
    //     }
    // };

    void ElementRegionWidget::mouseDown(const MouseEvent &event)
    {
    }

    void ElementRegionWidget::paint(Graphics &g)
    {
    }

    void ElementRegionWidget::resized()
    {
        impl->setBounds(getLocalBounds());
    }

    // Cursed RTTI experiment
#define THING(ElementType, ImplType) map.emplace(std::type_index(typeid(ElementType)), [](const event::ElementHandle &h)\
    {\
        return std::make_unique<ImplType>(std::dynamic_pointer_cast<ElementType>(h.ptr));\
    });

    static std::unordered_map<std::type_index, std::function<std::unique_ptr<Impl>(event::ElementHandle)>> map;

    static auto _clip = THING(ClipElement, ClipImpl)
    static auto _choice = THING(ChoiceElement, ChoiceImpl)

    void ElementRegionWidget::refresh()
    {
        removeAllChildren();
        if (const auto it = map.find(std::type_index{typeid(*element.ptr)}); it != map.end())
        {
            impl = it->second(element);
            addAndMakeVisible(impl.get());
            resized();
        }
    }
}
