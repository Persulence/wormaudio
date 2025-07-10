%define DEFINE_OPTIONAL_SIMPLE(OptT, T)

// Use reference, not pointer, typemaps for member variables of this type.
%naturalvar OptionalValue< T >;

%template(OptT) OptionalValue< T >;

// Note the use of "jboxtype" instead of just "jstype": for primitive types,
// such as "double", they're different and we must use the former as
// Optional<> can only be used with reference types in Java.
%typemap(jstype) OptionalValue< T >, const OptionalValue< T >& "java.util.Optional<$typemap(jboxtype, T)>"

// This typemap is used for function arguments of this type.
%typemap(javain,
         pre="    OptT opt$javainput = $javainput.isPresent() ? new OptT($javainput.get()) : new OptT();",
         pgcppname="opt$javainput")
         const OptionalValue< T >& "$javaclassname.getCPtr(opt$javainput)"

// This typemap is for functions returning objects of this type.
%typemap(javaout) OptionalValue< T >, const OptionalValue< T >& {
    OptT optvalue = new OptT($jnicall, $owner);
    if (optvalue.IsValid())
      return java.util.Optional.of(optvalue.Get());
    else
      return java.util.Optional.empty();
  }

%enddef