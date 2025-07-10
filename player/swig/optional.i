%module example

%{
#include <optional>
%}

namespace std
{
  template<typename T> class optional {};
}

// std::optional<double>
%typemap(jni) std::optional<double> "jobject"
%typemap(jtype) std::optional<double> "Double"
%typemap(jstype) std::optional<double> "Double"
%typemap(in, noblock=1) std::optional<double> {
  if ($input) {
    jclass sbufClass = JCALL1(GetObjectClass, jenv, $input);
    jmethodID mid = JCALL3(GetMethodID, jenv, sbufClass, "doubleValue", "()D");
    jdouble val = (jdouble)JCALL2(CallDoubleMethod, jenv, $input, mid);
    if (JCALL0(ExceptionCheck, jenv)) return $null;
    $1 = (double)val;
  }
}
%typemap(out, noblock=1) std::optional<double> {
  jclass clazz = JCALL1(FindClass, jenv, "java/lang/Double");
  jmethodID mid = JCALL3(GetMethodID, jenv, clazz, "<init>", "(D)V");
  jobject obj = $1 ? JCALL3(NewObject, jenv, clazz, mid, *$1) : 0;
  $result = obj;
}
%typemap(javain) std::optional<double> "$javainput"
%typemap(javaout) std::optional<double> {
    return $jnicall;
  }

%template() std::optional<double>;

// std::optional<std::string>
%include <std_string.i>

%typemap(jni) std::optional<std::string> "jstring"
%typemap(jtype) std::optional<std::string> "String"
%typemap(jstype) std::optional<std::string> "String"
%typemap(in) std::optional<std::string> %{
  if ($input) {
    const char *pstr = (const char *)jenv->GetStringUTFChars($input, 0);
    if (!pstr) return $null;
    $1 = std::string(pstr);
    jenv->ReleaseStringUTFChars($input, pstr);
  }
%}
%typemap(out) std::optional<std::string>
%{ $result = $1 ? jenv->NewStringUTF($1->c_str()) : 0; %}
%typemap(javain) std::optional<std::string> "$javainput"
%typemap(javaout) std::optional<std::string> {
    return $jnicall;
  }

%template() std::optional<std::string>;

%inline %{
#include <iostream>
  std::optional<double> optional_double_test(std::optional<double> x) {
    if (x)
      std::cout << "C++ " << *x << std::endl;
    else
      std::cout << "C++ " << "NULL" << std::endl;
    return x;
  }
  std::optional<std::string> optional_string_test(std::optional<std::string> x) {
    if (x)
      std::cout << "C++ " << *x << std::endl;
    else
      std::cout << "C++ " << "NULL" << std::endl;
    return x;
  }
%}