#include <dlfcn.h>
#include "catch2/catch_all.hpp"
#include <iostream>

int main(int argc, char** argv) {
    void* handle = dlopen("libtest_runner.so", RTLD_NOW);
    if (handle == nullptr) {
        std::cout << "failed to open lib\n";
        return 1;
    }

    typedef bool (*RunTests)(int argc, char** argv);
    RunTests runTests = nullptr;
    runTests = reinterpret_cast<RunTests>(dlsym(handle, "RunTests"));
    if (runTests == nullptr) {
        std::cout << "failed to load runtests\n";
        dlclose(handle);
        return 1;
    }

    runTests(argc, argv);

    dlclose(handle);
    return 0;
}
