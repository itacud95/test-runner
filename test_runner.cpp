#include <dlfcn.h>

#include <iostream>
#include <list>
#include <string>

#include "catch2/catch_all.hpp"

class TestRunner {
   public:
    TestRunner(const TestRunner &) = delete;
    TestRunner(TestRunner &&) = delete;
    TestRunner &operator=(const TestRunner &) = delete;
    TestRunner &operator=(TestRunner &&) = delete;

    TestRunner(std::string library) : _handle(dlopen(library.c_str(), RTLD_NOW)) {}
    ~TestRunner() {
        if (!_handle) {
            return;
        }
        int ret = dlclose(_handle);
        std::cout << "dlclose: " << ret << '\n';
    }

    bool IsLoaded() const { return _handle != nullptr; }

   private:
    void *_handle;
};

extern "C" bool RunTests(int argc, char** argv) {
    std::cout << "RunTests()\n";

    auto session = Catch::Session();
    auto &config = session.configData();
    config.filenamesAsTags = true;
    session.applyCommandLine(argc, argv);

    {
        std::list<TestRunner> testLibs;
        const std::string kPath = "/home/jk/dev/test-runner/build/test-modules/";
        auto tests = {
            "foo/libfoo_tests.so",  //
            "bar/libbar_tests.so"   //
        };

        for (const auto &test : tests) {
            testLibs.emplace_back(kPath + test);
            if (!testLibs.back().IsLoaded()) {
                std::cout << "Failed to load test: " << kPath + test << '\n';
                return false;
            }
        }
        int result = session.run();
        std::cout << "result: " << result << '\n';
    }
    std::cout << "RunTests() done\n";
    return true;
}
