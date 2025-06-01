#include "ConditionPanel.hpp"

#include "comparison/ComparisonConditionPanel.hpp"

namespace ui
{
    using namespace juce;
    using namespace condition;

    struct Visitor
    {

        std::unique_ptr<ConditionPanel> operator()(TrueCondition& condition) const
        {
            return std::make_unique<ConditionPanel>();
        }

        std::unique_ptr<ConditionPanel> operator()(ThingCondition& condition) const
        {
            return std::make_unique<ConditionPanel>();
        }

        std::unique_ptr<ConditionPanel> operator()(ComparisonCondition& condition) const
        {
            return std::make_unique<ComparisonConditionPanel>(condition);
        }

        // std::shared_ptr<ConditionPanel> operator()(Condition& condition) const
        // {
        //     return std::make_shared<ConditionPanel>(condition);
        // }
    };

    std::unique_ptr<ConditionPanel> ConditionPanel::create(Condition &condition)
    {
        Visitor visitor;

        return std::visit(visitor, condition);
    }

    ConditionPanel::ConditionPanel()
    {
        bg = Colours::red;
        // setInterceptsMouseClicks(true, true);
    }

    void ConditionPanel::paint(Graphics &g)
    {
        paintBackground(g);
        paintBorder(g);
    }

    void ConditionPanel::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem(1, "Delete");
            menu.showMenuAsync(PopupMenu::Options{}, [this] (int result)
            {
                switch (result)
                {
                    case 1:
                        std::cout << "clicked\n";
                        break;
                    default:
                        break;
                }
            });
        }
    }
}
