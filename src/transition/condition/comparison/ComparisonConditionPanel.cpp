#include "ComparisonConditionPanel.hpp"

#include "ComparisonComboBox.hpp"

import control;
import parameter;

namespace ui
{
    using namespace juce;
    using namespace condition;

    std::unordered_map<int, Operator> menuOps =
    {
        {1, {Equal{}}},
        {2, {NotEqual{}}},
        {3, {Less{}}},
        {4, {Greater{}}},
        {5, {LessEqual{}}},
        {6, {GreaterEqual{}}},
    };

    struct Processor
    {
        virtual ~Processor() = default;

        // Return false to mark invalid
        // virtual bool thing(std::string text, );
    };

    struct ParameterProcessor : Processor
    {

    };

    void addOperandItems(ComparisonComboBox& combo)
    {
        combo.addItem("<constant>", 1);
        combo.addItem("<parameter>", 2);
    }

    ComparisonConditionPanel::ComparisonConditionPanel(ComparisonCondition &condition_):
        condition(condition_)
    {
        bg = Colours::green;

        addAndMakeVisible(left);
        addAndMakeVisible(right);
        addAndMakeVisible(op);

        for (auto& [id, value] : menuOps)
        {
            op.addItem(value.getSymbol(), id);
        }

        addOperandItems(left);
        addOperandItems(right);

        left.setEditableText(true);
        right.setEditableText(true);

        op.addListener(this);
        left.addListener(this);
        right.addListener(this);

        layout.setItemLayout(0, -0.33, -0.4, -0.33);
        layout.setItemLayout(1, -0.33, -0.4, -0.33);
        layout.setItemLayout(2, -0.33, -0.4, -0.33);

        refresh();
    }

    void ComparisonConditionPanel::paint(Graphics &g)
    {
        ConditionPanel::paint(g);
    }

    void ComparisonConditionPanel::mouseDown(const MouseEvent &event)
    {
    }

    void ComparisonConditionPanel::resized()
    {
        std::array<Component*, 3> comps = {&left, &op, &right};
        layout.layOutComponents(comps.begin(), comps.size(), 0, 0, getWidth(), getHeight(), false, true);
    }

    void ComparisonConditionPanel::refresh()
    {
        left.setText(condition.left.toString());
        right.setText(condition.right.toString());
        op.setText(condition.op.getSymbol());
    }

    std::string updateOperand(Operand& operand, const std::string &text)
    {
        if (parameter::isValidName(text))
        {
            operand = {ParameterOperand{text}};
            return operand.toString();
        }
        else
        {
            const auto value = parameter::parseValue(text);
            operand = {ConstantOperand{value}};
            return operand.toString();
        }
    }

    void ComparisonConditionPanel::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
    {
        if (comboBoxThatHasChanged == &op)
        {
            condition.op = menuOps.at(comboBoxThatHasChanged->getSelectedId());
        }
        else if (comboBoxThatHasChanged == &left)
        {
            // left.showEditor();
            comboBoxThatHasChanged->setText(updateOperand(condition.left, comboBoxThatHasChanged->getText().toStdString()));
        }
        else if (comboBoxThatHasChanged == &right)
        {
            // right.showEditor();
            comboBoxThatHasChanged->setText(updateOperand(condition.right, comboBoxThatHasChanged->getText().toStdString()));
        }
    }
}
