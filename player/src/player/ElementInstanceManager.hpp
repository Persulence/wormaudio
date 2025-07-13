// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "instance/instance.hpp"
#include "resource/ElementInstance.hpp"
#include "util/AudioContext.hpp"
#include "util/Time.hpp"
#include "event/EventDef.fwd.hpp"

namespace player
{
    using namespace element;

    class ElementInstanceManager : public juce::AudioSource
    {
    public:
        ElementInstanceManager(const instance::Vec3f& position, const event::EventProperties& properties);

        ElementInstancePtr addInstance(const ElementInstancePtr& element);
        void stageHandoff(Sample sample);

        void clear();
        void freeReleased();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void releaseResources() override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

        [[nodiscard]] AudioContext getAudioContext() const { return audioContext; }

    private:
        // std::vector<ElementInstancePtr> active;
        // Using a collection type that does not allow duplicates
        // TODO: look into using data-oriented principles

        std::queue<ElementInstancePtr> queue;
        std::unordered_set<ElementInstancePtr> active;

        std::mutex activeMutex;

        AudioContext audioContext;

        juce::AudioSampleBuffer accumulator;

        Sample stagedHandoff{NULL_SAMPLE};
        const instance::Vec3f& position;
        const event::EventProperties& properties;
    };
}

