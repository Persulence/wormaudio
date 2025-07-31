
// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "bindings.h"


namespace binding
{
    class LoggerAdaptor : WrapperBase, public juce::Logger
    {
    public:
        LoggerAdaptor() = default;
        ~LoggerAdaptor() override
        {
            // Hopefully this class's lifetime will be managed by the target language
            juce::Logger::setCurrentLogger(nullptr);
        }

        virtual void logMessage(const std::string& message) = 0;

    protected:
        void logMessage(const juce::String &message) override
        {
            logMessage(message.toStdString());
        }
    };

    inline void setLogger(LoggerAdaptor* logger)
    {
        juce::Logger::setCurrentLogger(logger);
    }
}
