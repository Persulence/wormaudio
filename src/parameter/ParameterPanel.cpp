#include "ParameterPanel.hpp"

#include "editor/Editor.hpp"

import parameter;

namespace ui
{
    using namespace juce;
    using namespace parameter;
    ParameterPanel::ParameterPanel():
        testParameter({std::make_shared<ParameterDef>(DiscreteParameterDef{0, 10, "test"})}),
        testInstance(testParameter)
    {
        refresh();
    }

    void ParameterPanel::refresh()
    {
        removeAllChildren();
        // for (auto& parameter : editor::Editor::getInstance().getEvent()->getParameters().parameters)
        // {
        //     widgets.emplace_back(std::make_unique<ParameterWidget>(parameter));
        // }
    }

    void ParameterPanel::resized()
    {
        // widget.setBounds(getLocalBounds());
        FlexBox flexBox;
        flexBox.flexDirection = FlexBox::Direction::column;
        flexBox.alignItems = FlexBox::AlignItems::stretch;
        flexBox.flexWrap = FlexBox::Wrap::wrap;
        for (auto& widget : widgets)
        {
            flexBox.items.add(FlexItem{*widget}.withMaxHeight(30).withMaxWidth(80));
        }

        flexBox.performLayout(getLocalBounds());
    }

    void ParameterPanel::mouseDown(const juce::MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem("New parameter", [this](){ editor::Editor::getInstance().getEvent()->getParameters().insert(
                std::make_shared<ParameterDef>(ContinuousParameterDef{0, 10, "ooer"}));
                refresh();
            });

            menu.showMenuAsync(PopupMenu::Options{});
        }
    }

}
