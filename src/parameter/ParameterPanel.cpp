#include "ParameterPanel.hpp"

#include <format>
#include <ranges>

#include "editor/Editor.hpp"

import parameter;

namespace ui
{
    using namespace juce;
    using namespace parameter;

    ParameterPanel::ParameterPanel()
    {
        listen(editor::Editor::getInstance().lifecycleChanged, [this](int i){ refresh(); });
    }

    void ParameterPanel::refresh()
    {
        removeAllChildren();
        widgets.clear();
        for (auto &parameter: editor::Editor::getInstance().getRuntime().getParameters().instances | std::views::values)
        {
            auto& widget = widgets.emplace_back(std::make_unique<ParameterWidget>(*parameter));
            addAndMakeVisible(*widget);
        }
        resized();
    }

    void ParameterPanel::resized()
    {
        // widget.setBounds(getLocalBounds());
        FlexBox flexBox;
        flexBox.flexDirection = FlexBox::Direction::column;
        flexBox.alignItems = FlexBox::AlignItems::stretch;
        flexBox.flexWrap = FlexBox::Wrap::wrap;
        flexBox.alignContent = FlexBox::AlignContent::stretch;
        for (auto& widget : widgets)
        {
            flexBox.items.add(FlexItem{*widget}.withMinWidth(100).withMinHeight(40).withMaxHeight(40).withMaxWidth(100));
            // widget->setBounds(getLocalBounds());
        }

        flexBox.performLayout(getLocalBounds());
    }

    void ParameterPanel::mouseDown(const juce::MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem("New parameter", [this]()
            {
                static int i = 0;
                i++;
                editor::Editor::getInstance().getGlobalParameters().insert(
                    std::make_shared<ParameterDef>(ContinuousParameterDef{0, 10, std::format("Parameter{}", i)}));
                refresh();
            });

            menu.showMenuAsync(PopupMenu::Options{});
        }
    }

}
