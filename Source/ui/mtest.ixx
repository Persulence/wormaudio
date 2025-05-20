module;

// #include <iostream>
#include <JuceHeader.h>

export module mtest;

export class C : juce::Component
{
public:
    explicit C(const int _field): field(_field)
    {
        addAndMakeVisible(loadFile);
    }

    ~C() override = default;

    void thingy() const
    {
        std::cout << "The field in question: " << field << std::endl;
    }

private:
    int field;
    juce::TextButton loadFile;
};
