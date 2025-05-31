#include "ConditionListPanel.hpp"

namespace ui
{
    using namespace juce;
    using namespace sm;

    ConditionListPanel::ConditionListPanel(condition::ConditionList &conditionList_):
        conditionList(conditionList_)
    {

    }

    void ConditionListPanel::refresh()
    {
        conditions.clear();
        removeAllChildren();
        for (auto& condition : conditionList.conditions)
        {
            // Generate condition panel
            auto& child = conditions.emplace_back(std::make_unique<ConditionPanel>(condition));
            addAndMakeVisible(child.get());
        }
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
            flexBox.items.add(FlexItem{*condition}.withMaxHeight(50).withHeight(50).withMaxWidth(200));
        }

        flexBox.performLayout(getLocalBounds());
    }
}
