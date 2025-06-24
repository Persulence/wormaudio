#include "ConditionListPropertyFiller.hpp"

namespace ui
{
    using namespace juce;
    using namespace sm;
    using namespace condition;

    ConditionListPropertyFiller::ConditionListPropertyFiller(ConditionList &conditionList_):
        conditionList(conditionList_)
    {
    }

    void ConditionListPropertyFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Condition List"));

        for (auto& condition : conditionList.conditions)
        {
            auto child = ConditionPropertyFiller::create(condition);
            add(std::shared_ptr(std::move(child)));
        }
    }

    // void ConditionListPanel::refresh()
    // {
    //     conditions.clear();
    //     removeAllChildren();
    //
    //     // Some bodging. This entire thing should be a PropertyFiller.
    //     int newHeight = 0;
    //     for (auto& condition : conditionList.conditions)
    //     {
    //         // Generate condition panel
    //         auto child = ConditionPanel::create(condition);
    //         newHeight += child->getDesiredHeight();
    //         auto& added = conditions.emplace_back(std::move(child));
    //         addAndMakeVisible(added.get());
    //     }
    //
    //     // setBounds(getBounds().withHeight(newHeight));
    //     resized();
    // }

    void ConditionListPropertyFiller::mouseDown(const MouseEvent &event)
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

    // void ConditionListPanel::paint(Graphics &g)
    // {
    //     paintBackground(g);
    // }

    void ConditionListPropertyFiller::addCondition(const Condition &condition)
    {
        auto& added = conditionList.insertCondition(condition);
        refresh();
    }

    // void ConditionListPanel::resized()
    // {
    //     FlexBox flexBox;
    //     flexBox.flexDirection = FlexBox::Direction::column;
    //     flexBox.alignContent = FlexBox::AlignContent::stretch;
    //     flexBox.flexWrap = FlexBox::Wrap::wrap;
    //     flexBox.justifyContent = FlexBox::JustifyContent::flexStart;
    //
    //     for (auto& condition : conditions)
    //     {
    //         flexBox.items.add(FlexItem{*condition}.withMaxHeight(30).withHeight(30).withMaxWidth(300));
    //     }
    //
    //     flexBox.performLayout(getLocalBounds());
    // }

}
