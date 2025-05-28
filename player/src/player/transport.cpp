module;

module transport;

void player::TransportControl::setState(TransportState state_)
{
    state = state_;
    signal.emit(state);
}

bool player::TransportControl::stopped() const
{
    return state == STOPPED;
}


