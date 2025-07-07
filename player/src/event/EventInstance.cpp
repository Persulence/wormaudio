#include "EventInstance.hpp"

namespace event
{
    EventInstance::EventInstance(resource::Handle<EventDef> parent_):
        parent(std::move(parent_)),
        automationInstance(std::make_unique<automation::AutomationTableInstance>(parent->getAutomation())),
        stateManager(StateMachineInstance(parent->getDefinition()->getStates(), parent->getDefinition()->getStart())),
        elementManager(std::make_unique<player::ElementInstanceManager>(position, parent->getProperties()))
    {}

    void EventInstance::prepareToPlay(player::AudioContext ctx)
    {
        elementManager->prepareToPlay(ctx.samplesPerBlock, ctx.sampleRate);
    }

    void EventInstance::logicTick(sm::GlobalParameterLookup &globalParameters, player::TransportControl &globalTransport, const LogicTickInfo &info)
    {
        // This can't be a good idea
        parameters.setParent(&globalParameters);

        if (transport.getState() == player::STARTING)
        {
            // Starting on the block
            parameters.resetStateTimer(info.blockBeginSamples);
            transport.setState(player::PLAYING);
        }

        if (transport.getState() == player::PLAYING)
        {
            EventElementInstancer instancer{*elementManager, *automationInstance};
            automationInstance->logicTick(parameters, transport);
            stateManager.logicTick(parameters, instancer, transport, info);
        }
        else
        {
            return;
        }

        if (transport.stopped())
        {
            stop();
        }
    }

    void EventInstance::stop() const
    {
        stateManager.stop();
        elementManager->clear();
    }

    player::ElementInstanceManager & EventInstance::getElements()
    {
        return *elementManager;
    }
}
