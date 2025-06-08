#include "ElementRegion.hpp"

#include "automation/AutomationTable.hpp"
#include "automation/Mapping.hpp"
#include "editor/Editor.hpp"

namespace ui
{
    using namespace juce;

    void ElementRegion::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            auto& editor = editor::Editor::getInstance();

            // Menu for selecting a parameter
            PopupMenu parameters;
            for (const auto& parameter : editor.getGlobalParameters().parameters)
            {
                parameters.addItem({parameter->getName()}, [this, &editor, parameter]
                {
                    const automation::AutomationLink link{parameter, element->volume, automation::MappingFunction{}};
                    editor.getEvent()->getAutomation().setup(link);
                });
            }

            PopupMenu menu;
            menu.addItem("ooer", []{});
            menu.addSubMenu("Automate volume", parameters);

            menu.showMenuAsync(PopupMenu::Options{});
        }
    }

    void ElementRegion::paint(Graphics &g)
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
}
