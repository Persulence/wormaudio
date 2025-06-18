#pragma once
#include "event/ParameterList.hpp"
#include "signal/Signal.hpp"

namespace editor
{
    class EditorParameterList : public event::ParameterList
    {
    public:
        using Changed = signal_event::Callback<>;

        resource::Handle<event::ParameterListImpl> target;
        Changed::Signal changed;

        explicit EditorParameterList(const resource::Handle<event::ParameterListImpl> &target_):
            target(target_)
        {}

        auto size() const
        {
            return target->parameters.size();
        }

        void insert(const parameter::Parameter &parameter) override
        {
            target->insert(parameter);
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

        bool rename(const parameter::Parameter& parameter, const std::string & newName);

        bool changeType(const parameter::Parameter& parameter, const parameter::Parameter& newParameter)
        {
            using namespace parameter;

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
    };
}
