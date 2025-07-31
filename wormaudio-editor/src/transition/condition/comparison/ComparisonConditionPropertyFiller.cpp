// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "ComparisonConditionPropertyFiller.hpp"

#include "ComparisonComboBox.hpp"
#include "editor/Editor.hpp"

namespace ui
{
    using namespace juce;
    using namespace condition;

    std::unordered_map<int, Operator> menuOps =
    {
        {1, {OperatorType::EQUAL}},
        {2, {OperatorType::NOT_EQUAL}},
        {3, {OperatorType::LESS}},
        {4, {OperatorType::GREATER}},
        {5, {OperatorType::LESS_EQUAL}},
        {6, {OperatorType::GREATER_EQUAL}},
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

    ComparisonPropertyWidget::ComparisonPropertyWidget(ComparisonCondition &condition_):
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

    void ComparisonPropertyWidget::resized()
    {
        std::array<Component*, 3> comps = {&left, &op, &right};
        layout.layOutComponents(comps.data(), comps.size(), 0, 0, getWidth(), getHeight(), false, true);
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

    void ComparisonPropertyWidget::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
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

    void ComparisonPropertyWidget::refresh()
    {
        left.setText(condition.getLeft().toString());
        right.setText(condition.getRight().toString());
        op.setText(condition.getOp().getSymbol());
    }


    ComparisonConditionPropertyFiller::ComparisonConditionPropertyFiller(ComparisonCondition &condition_, int index):
        ConditionPropertyFiller(index),
        condition(condition_)
    {
        setHeader(std::make_unique<SectionHeader>("Comparison"));
    }

    void ComparisonConditionPropertyFiller::initProperties()
    {
        add(std::make_unique<ComparisonPropertyWidget>(condition));
    }
}
