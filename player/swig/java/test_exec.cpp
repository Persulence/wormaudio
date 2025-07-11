#include <iostream>

#include "../runtime.b.hpp"

int main()
{
    std::cout << "This is a test. This is only a test\n";

    binding::NRuntime runtime;

    binding::NRuntime::startMessageManager();
}
