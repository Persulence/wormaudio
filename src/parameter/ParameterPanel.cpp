#include "ParameterPanel.hpp"

#include <format>
#include <ranges>

#include "editor/Editor.hpp"

namespace ui
{
    using namespace juce;
    using namespace parameter;

    ParameterPanel::ParameterPanel()
    {
        editor::Editor::getInstance().lifecycleChanged.setup(this, [this](int){ refresh(); });

        editor::Editor::getInstance().parametersChanged.setup(this, [this] { refresh(); });
    }

    void ParameterPanel::refresh()
    {
        removeAllChildren();
        widgets.clear();
        auto& lookup = editor::Editor::getInstance().getRuntime().getParameters();
        for (auto &parameter: lookup.instances | std::views::values)
        {
            auto& widget = widgets.emplace_back(std::make_unique<ParameterWidget>(lookup, parameter->parameter));
            addAndMakeVisible(*widget);
        }
        resized();
    }

    void ParameterPanel::paint(Graphics &g)
    {
        paintBackground(g);
    }

    void ParameterPanel::resized()
    {
        // widget.setBounds(getLocalBounds());
        FlexBox flexBox;
        flexBox.flexDirection = FlexBox::Direction::column;
        flexBox.alignItems = FlexBox::AlignItems::stretch;
        flexBox.flexWrap = FlexBox::Wrap::wrap;
        flexBox.alignContent = FlexBox::AlignContent::flexStart;
        flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
        for (auto& widget : widgets)
        {
            flexBox.items.add(FlexItem{*widget}.withMinWidth(100).withMinHeight(40).withMaxHeight(40).withMaxWidth(100));
            // widget->setBounds(getLocalBounds());
        }

        flexBox.performLayout(getLocalBounds());
    }

    void ParameterPanel::addNewParameter(const Parameter &parameter)
    {
        auto& editor = editor::Editor::getInstance();
        parameter->setName(std::format("Parameter{}", editor.getEditorParameters().getParameters().size()));
        editor.getEditorParameters().insert(parameter);
        refresh();
    }

    void ParameterPanel::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem("New continuous parameter", [this]
            {
                addNewParameter(std::make_shared<ParameterDef>(ContinuousParameterDef{-5, 5, "p"}));
                refresh();
            });
            menu.addItem("New discrete parameter", [this]
            {
                addNewParameter(std::make_shared<ParameterDef>(DiscreteParameterDef{0, 10, "p"}));
            });
            menu.addItem("New enum parameter", [this]
            {
                addNewParameter(std::make_shared<ParameterDef>(EnumParameterDef::createDefault("p")));
            });

            menu.showMenuAsync(PopupMenu::Options{});
        }
    }

}
