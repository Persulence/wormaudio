// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once
#include <algorithm>
#include <vector>

namespace signal_event
{
    template <typename... Args>
    class SignalType;

    template <typename... Args>
    class ListenerBase;

    template <typename... Args>
    class ListenerType;

    template <typename... Args>
    class MultiListenerType;

    /**
     * using Thing = Callback<int, int, int>;
     * Thing::Signal s;
     * Thing::Listener l;
     * l.listen(s, callback);
     * s.emit(1, 2, 3);
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args> struct Callback
    {
        using Signal = SignalType<Args...>;
        using Listener = ListenerType<Args...>;
        using MultiListener = MultiListenerType<Args...>;
    };

    template <typename... Args>
    class UniqueSignal
    {
        using L = ListenerBase<Args...>;

    public:
        UniqueSignal(const UniqueSignal&) = delete;
        UniqueSignal& operator=(const UniqueSignal&) = delete;
        UniqueSignal(UniqueSignal&&) = delete;
        UniqueSignal& operator=(UniqueSignal&&) = delete;

        UniqueSignal() = default;

        ~UniqueSignal()
        {
            for (auto& listener : listeners)
            {
                listener->targetDestroyed(this);
            }
        }

        void reg(L* listener)
        {
            listeners.push_back(listener);
        }

        void unReg(L* listener)
        {
            listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
        }

        void emit(Args&&... args) const
        {
            for (auto& l : listeners)
            {
                // l->listenerCallback(std::forward<Args>(args)...);
                // Cheeky copy
                l->listenerCallback(args...);
            }
        }

    private:
        std::vector<L*> listeners;
        // TODO: mutex
    };
}
