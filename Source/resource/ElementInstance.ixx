export module ElementInstance;

import AudioContext;

namespace element
{
    export class ElementInstance
    {
    protected:
        player::AudioContext audioContext;
        bool released;

    public:
        explicit ElementInstance(const player::AudioContext &context_):
            audioContext(context_),
            released(false)
        { }

        virtual void start() = 0;

        virtual void stop() = 0;

        [[nodiscard]] bool canBeFreed() const
        {
            return released;
        }

        virtual ~ElementInstance() = default;
    };
}

