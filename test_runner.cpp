#include <dlfcn.h>

#include <list>
#include <string>

#include "catch2/catch_all.hpp"

#ifdef ANDROID
#include <android/log.h>
#define log(...) __android_log_print(ANDROID_LOG_INFO, "Catch", __VA_ARGS__)
#else
#include <printf.h>
#define log(...)         \
    printf(__VA_ARGS__); \
    printf("\n")
#endif

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
    }

    bool IsLoaded() const { return _handle != nullptr; }

   private:
    void *_handle;
};

extern "C" bool RunTests(int argc, char** argv) {
    log("RunTests()");

    auto session = Catch::Session();
    auto &config = session.configData();
    config.filenamesAsTags = true;
    if (argc > 1) {
        session.applyCommandLine(argc, argv);
    }

    {
        std::list<TestRunner> testLibs;
        auto tests = {
            "libfoo_tests.so",  //
            "libbar_tests.so"   //
        };

        for (const auto &test : tests) {
            log("Loading %s", test);
            testLibs.emplace_back(test);
            if (!testLibs.back().IsLoaded()) {
                log("Failed to load test: %s", test);
                return false;
            }
        }
        int result = session.run();
        log("result: %d", result);
    }
    log("RunTests() done\n");
    return true;
}
