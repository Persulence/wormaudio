#include "ComparisonConditionPanel.hpp"

#include "ComparisonComboBox.hpp"
#include "editor/Editor.hpp"

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

    void addOperandItems(ComparisonComboBox& combo)
    {
        int i = 1;
        combo.addItem("<constant>", i);
        i++;
        combo.addItem("<parameter>", i);
        i++;
        auto& editor = editor::Editor::getInstance();
        for (auto& parameter : editor.getEditorParameters().getParameters())
        {
            combo.addItem(parameter->getName(), i);
            i++;
        }
    }

    ComparisonConditionPanel::ComparisonConditionPanel(ComparisonCondition &condition_):
        condition(condition_)
    {
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

    void ComparisonConditionPanel::initProperties()
    {

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
        left.setText(condition.getLeft().toString());
        right.setText(condition.getRight().toString());
        op.setText(condition.getOp().getSymbol());
    }

    static Operand updateOperand(std::string &text)
    {
        if (parameter::isValidName(text))
        {
            auto operand = Operand{ParameterOperand{text}};
            text = operand.toString();
            return operand;
        }
        else
        {
            const auto value = parameter::parseValue(text);
            auto operand = Operand{ConstantOperand{value}};
            text = operand.toString();
            return operand;
        }
    }

    void ComparisonConditionPanel::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
    {
        if (comboBoxThatHasChanged == &op)
        {
            condition.setOp(menuOps.at(comboBoxThatHasChanged->getSelectedId()));
        }
        else if (comboBoxThatHasChanged == &left)
        {
            auto text = comboBoxThatHasChanged->getText().toStdString();
            condition.setLeft(updateOperand(text));
            comboBoxThatHasChanged->setText(text);
        }
        else if (comboBoxThatHasChanged == &right)
        {
            auto text = comboBoxThatHasChanged->getText().toStdString();
            condition.setRight(updateOperand(text));
            comboBoxThatHasChanged->setText(text);
        }
    }
}
