%module swig_example

// Add necessary symbols to generated header
%{
#include "bindings.h"
%}

// Process symbols in header
%include "bindings.h"
