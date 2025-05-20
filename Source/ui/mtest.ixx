module;

// #include <iostream>
// #include <JuceHeader.h>

export module mtest;

export class C
{
public:
    explicit C(int field): field(field)
    {
        // addAndMakeVisible(loadFile);
    }

    // ~C() override = default;

    void thingy()
    {
        // std::cout << "The field in question: " << field << std::endl;
    }

private:
    int field;
    // juce::TextButton loadFile;
};
