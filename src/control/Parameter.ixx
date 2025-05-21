module;

#include <string>

export module Parameter;

export using ParameterValue = float;

export struct Parameter
{
    std::string name;
};

export struct ParameterInstance
{
    static const ParameterInstance& defaultInstance();

    ParameterInstance(): value(defaultInstance().value)
    {

    }

    ParameterInstance(const ParameterInstance& other) = delete;
    ParameterInstance& operator=(const ParameterInstance& other) = delete;

    ParameterValue value;

private:
    explicit ParameterInstance(ParameterValue value): value(value)
    {

    }
};

const ParameterInstance& ParameterInstance::defaultInstance()
{
    static ParameterInstance DEFAULT = ParameterInstance{0};
    return DEFAULT;
}

