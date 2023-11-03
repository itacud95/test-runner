#include <dlfcn.h>

#include <iostream>

int main() {
    void* handle = dlopen("libtest_runner.so", RTLD_NOW);
    if (handle == nullptr) {
        std::cout << "failed to open lib\n";
        return 1;
    }

    typedef bool (*RunTests)();
    RunTests runTests = nullptr;
    runTests = reinterpret_cast<RunTests>(dlsym(handle, "RunTests"));
    if (runTests == nullptr) {
        std::cout << "failed to load runtests\n";
        dlclose(handle);
        return 1;
    }

    runTests();

    dlclose(handle);
    return 0;
}
