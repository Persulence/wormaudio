%include "enums.swg"
%javaconst(1);

%include "util.i"
%include "juce.i"

%ignore player::TransportControl;
%include "player/transport.hpp"
UNIGNORE_ALL