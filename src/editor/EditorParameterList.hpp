// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
