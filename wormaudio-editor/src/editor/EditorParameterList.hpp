// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once
#include "event/ParameterList.hpp"
#include "signal/Signal.hpp"

namespace editor
{
    class EditorParameterList : public event::ParameterList, parameter::ParameterDefBase::Changed::MultiListener
    {
    public:
        using Changed = signal_event::Callback<>;

        resource::Handle<event::ParameterListImpl> target;
        Changed::Signal changed;

        explicit EditorParameterList(const resource::Handle<event::ParameterListImpl> &target_):
            target(target_)
        {
            setCallback([this]
            {
                changed.emit();
            });
        }

        auto size() const
        {
            return target->parameters.size();
        }

        void insert(const parameter::Parameter &parameter) override
        {
            target->insert(parameter);
            listen(parameter->getChanged());

            changed.emit();
        }

        bool remove(const parameter::Parameter &parameter) override
        {
            if (target->remove(parameter))
            {
                changed.emit();
                return true;
            }

            return false;
        }

        bool rename(const parameter::Parameter& parameter, const std::string& newName);

        bool changeType(const parameter::Parameter& parameter, const parameter::Parameter& newParameter)
        {
            using namespace parameter;

            newParameter->getChanged().setup(this);
            *parameter = std::move(*newParameter);
            // ParameterList::remove(parameter);
            // ParameterList::insert(newParameter);

            changed.emit();
            return true;
        }

        std::vector<parameter::Parameter> & getParameters() override
        {
            return target->getParameters();
        }

        void setTarget(const resource::Handle<event::ParameterListImpl> &target_)
        {
            target = target_;
            changed.emit();
        }
    };
}
