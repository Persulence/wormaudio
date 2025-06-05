#pragma once
#include "event/ParameterList.hpp"
#include "signal/Signal.hpp"

namespace editor
{
    class EditorParameterList : public event::ParameterList
    {
    public:
        using Changed = signal_event::Callback<>;

        Changed::Signal changed;

        void insert(const parameter::Parameter &parameter) override
        {
            ParameterList::insert(parameter);
            changed.emit();
        }

        void remove(const parameter::Parameter &parameter) override
        {
            ParameterList::remove(parameter);
            changed.emit();
        }
    };
}
