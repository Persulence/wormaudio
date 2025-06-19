#include "ConditionListPanel.hpp"

namespace ui
{
    using namespace juce;
    using namespace sm;
    using namespace condition;

    ConditionListPanel::ConditionListPanel(ConditionList &conditionList_):
        conditionList(conditionList_)
    {
        bg = Colours::darkgrey;
    }

    void ConditionListPanel::refresh()
    {
        conditions.clear();
        removeAllChildren();
        for (auto& condition : conditionList.conditions)
        {
            // Generate condition panel
            auto& child = conditions.emplace_back(ConditionPanel::create(condition));
            addAndMakeVisible(child.get());
        }

        resized();
    }

    void ConditionListPanel::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem("New comparison condition", [this]
            {
                addCondition(ComparisonCondition{});
            });
            menu.addItem("New time condition", [this]
            {
                addCondition(TimeCondition{});
            });
            menu.showMenuAsync(PopupMenu::Options{});
        }
    }

    void ConditionListPanel::paint(Graphics &g)
    {
        paintBackground(g);
    }

    void ConditionListPanel::addCondition(const Condition &condition)
    {
        auto& added = conditionList.insertCondition(condition);
        refresh();
    }

    void ConditionListPanel::resized()
    {
        FlexBox flexBox;
        flexBox.flexDirection = FlexBox::Direction::column;
        flexBox.alignContent = FlexBox::AlignContent::stretch;
        flexBox.flexWrap = FlexBox::Wrap::wrap;
        flexBox.justifyContent = FlexBox::JustifyContent::flexStart;

        for (auto& condition : conditions)
        {
            flexBox.items.add(FlexItem{*condition}.withMaxHeight(30).withHeight(30).withMaxWidth(300));
        }

        flexBox.performLayout(getLocalBounds());
    }

}
