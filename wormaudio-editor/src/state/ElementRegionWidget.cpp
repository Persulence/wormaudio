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

#include "ElementRegionWidget.hpp"

#include <memory>

#include "StatePropertyPanel.hpp"
#include "automation/AutomationTable.hpp"
#include "automation/Mapping.hpp"
#include "browser/FileDragSource.hpp"
#include "canvas/InspectorSelectionManager.hpp"
#include "editor/Editor.hpp"
#include "inspector/filler/ElementInspectorFiller.hpp"
#include "resource/ChoiceElement.hpp"

#include "resource/ClipElement.hpp"

namespace ui
{
    using namespace juce;
    using namespace element;

    PopupMenu createParametersSubmenu(const std::vector<parameter::Parameter>& parameters, std::function<void(const parameter::Parameter&)> f)
    {
        PopupMenu menu;

        for (const auto& parameter : parameters)
        {
            menu.addItem({parameter->getName()}, [parameter, f] { f(parameter); });
        }

        return menu;
    }

    class ElementRegionImpl : public Component
    {

    };

    class ClipImpl : public ElementRegionImpl
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

            g.setColour(Colours::white);
            g.drawText(element->getName(), getLocalBounds().withTrimmedLeft(10).toFloat(), Justification::centredLeft, true);
        }

        void mouseDown(const MouseEvent &event) override
        {
            if (auto manager = findParentComponentOfClass<InspectorSelectionManager>())
            {
                manager->select(SimpleSelectionTarget::of(std::make_unique<ElementInspectorFiller>(event::ElementHandle{element})));
            }

            if (event.mods.isRightButtonDown())
            {
                auto& editor = editor::Editor::getInstance();

                const auto& parameters = editor.getEditorParameters().getParameters();

                // Menu for selecting a parameter
                const PopupMenu volumeMenu = createParametersSubmenu(parameters, [this, &editor](auto& p)
                {
                    const automation::AutomationLink link{p, element->volume, automation::MappingFunction{}};
                    editor.getEvent()->getAutomation().setup(link);
                });

                const PopupMenu speedMenu = createParametersSubmenu(parameters, [this, &editor](auto& p)
                {
                    const automation::AutomationLink link{p, element->speed, automation::MappingFunction{}};
                    editor.getEvent()->getAutomation().setup(link);
                });

                PopupMenu menu;

                menu.addItem("Remove", [this]
                {
                    if (const auto parent = findParentComponentOfClass<StatePropertyPanel>())
                    {
                        parent->removeElement(element);
                    }
                });

                menu.addSubMenu("Automate volume", volumeMenu);
                menu.addSubMenu("Automate speed", speedMenu);

                menu.showMenuAsync(PopupMenu::Options{});
            }
        }

    private:
        resource::Handle<ClipElement> element;
    };

    class ChoiceImpl : public ElementRegionImpl, public DragAndDropTarget
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

            g.setColour(Colours::white);
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

        void mouseDown(const MouseEvent &event) override
        {
            if (auto manager = findParentComponentOfClass<InspectorSelectionManager>())
            {
                manager->select(SimpleSelectionTarget::of(std::make_unique<ElementInspectorFiller>(event::ElementHandle{element})));
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

    static std::unordered_map<std::type_index, std::function<std::unique_ptr<ElementRegionImpl>(event::ElementHandle)>> map;

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
