#include "console/headers/base.h"
#include "HLnetwork/headers/base.h"

int main()
{
    console::lib_test();
    hlnet::lib_test();
    int exit_code = console::window_test();
    std::cout << "exiting with code: " << exit_code << '\n';
    return exit_code;
}