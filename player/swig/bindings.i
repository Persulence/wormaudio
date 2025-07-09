%module NEEPSound

// Add necessary symbols to generated header
%{
#include "bindings.h"
%}

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

// Process symbols in header
%include "bindings.h"
