#pragma once

#include <juce_core/juce_core.h>

#include "util/serialization_util.hpp"

namespace cereal
{
    EXTERNAL_SPLIT_SAVE(juce::Uuid)
    {
        std::string s = m.toString().toStdString();
        ar(cereal::make_nvp("data", s));
    }

    EXTERNAL_SPLIT_LOAD(juce::Uuid)
    {
        std::string s;
        ar(cereal::make_nvp("data", s));
        m = s;
    }

    // Not being picked up by cereal for some reason
    // template<> struct LoadAndConstruct<juce::Uuid>
    // {
    //     template <class Archive>
    //     static void load_and_construct(Archive& ar, construct<juce::Uuid>& construct)
    //     {
    //         std::string s;
    //         make_optional_nvp(ar, "data", s);
    //         construct(juce::String{s});
    //     }
    // };
}
