%module NEEPSound

// Add necessary symbols to generated header
%{
#include "bindings.h"
#include "event/EventDef.hpp"
#include "resource/SharedResource.hpp"
%}

%include <std_shared_ptr.i>

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("neepsound-java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}

//%ignore "";
//%rename("%s") resource;
//%rename("%s") resource::Handle;
//%rename("%s") resource::Handle::Handle;
//%rename("%s") resource::Handle::~Handle;
//
//%rename("%s") std;
//%rename("%s") std::shared_ptr;
//%rename("%s") std::shared_ptr::shared_ptr;
//%rename("%s") std::shared_ptr::~shared_ptr;
//
//
//%rename("%s") SoundThing;
//%rename("%s") SoundThing::SoundThing;
//%rename("%s") SoundThing::~SoundThing;
//
//%rename("%s") EventDef;
//%rename("%s") EventDef::EventDef;
//%rename("%s") EventDef::~EventDef;

%include "bindings.h"

//%include "util/serialization_util.hpp"
//%include "resource/SharedResource.hpp"
//%include "event/EventDef.hpp"


//%rename("%s") "";