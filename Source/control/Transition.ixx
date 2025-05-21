module;

#include <string>
#include <vector>
#include <variant>

export module control:Transition;

import ParameterLookup;
import Parameter;

export template <class T>
struct Condition
{
    bool test(const ParameterLookup& pl) const
    {
        return static_cast<T*>(this)->testImpl(pl);
    }
};

export struct ParameterCondition : Condition<ParameterCondition>
{
    std::string name;
    ParameterValue value;

    bool testImpl(const ParameterLookup& pl) const
    {
        auto current = pl.get(name).value;
        return current > value;
    }
};

export struct ThingCondition : Condition<ThingCondition>
{

};

// export struct ThingCond

using Thing = std::variant<Condition<ParameterCondition>, Condition<ThingCondition>>;

struct Visitor
{
    void operator()(const int& i) const
    {

    }

    void operator()(const bool& i) const
    {

    }
};

export class Transition
{
    std::vector<Thing> things;

public:
    void insertCondition(Thing&& condition)
    {
        things.push_back(condition);
    }

    bool test(const ParameterLookup& parameters) const
    {
        for (const auto& thing : things)
        {
            Visitor visitor;
            // std::visit(visitor, thing);
        }

        return false;
    }
};
