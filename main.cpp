#include <dlfcn.h>

#include <catch2/catch_all.hpp>
#include <cstddef>
#include <iostream>
#include <string>

#include "CatchEventListener.h"

TEST_CASE("Foo Test") {
    // std::cout << "foo test\n";
    REQUIRE(true);
    CHECK(true);
    CHECK(false);
    CHECK(false);
}
TEST_CASE("Bar Test", "[myTag]") {
    // std::cout << "bar test\n";
    REQUIRE(true);
    REQUIRE(false);
}

CATCH_REGISTER_LISTENER(EventListener)

class CatchTestRunner {
   public:
    static CatchTestRunner& GetInstance() {
        static CatchTestRunner instance;
        return instance;
    }
    CatchTestRunner(CatchTestRunner const&) = delete;
    void operator=(CatchTestRunner const&) = delete;

    std::set<std::string> GetTags() {
        std::set<std::string> tags;
        auto const& testSpec = session.config().testSpec();
        if (testSpec.hasFilters()) {
            for (auto const& test : Catch::getAllTestCasesSorted(session.config())) {
                for (auto const& tag : test.getTestCaseInfo().tags) {
                    std::string taggg(tag.original.begin(), tag.original.size());
                    tags.insert(taggg);
                }
            }
        }
        return tags;
    }

    bool RunTests() {
        failedTests.clear();
        output = "";
        static int counter = 0;

        auto& config = session.configData();
        config.filenamesAsTags = true;
        config.defaultOutputFilename = "%debug";
        // config.defaultOutputFilename = "output";// %debug
        config.defaultColourMode = Catch::ColourMode::ANSI;
        config.testsOrTags.push_back("[myTag]");
        config.listTags = true;
        session.useConfigData(config);
        int result = session.run();

        std::vector<std::string> list = config.testsOrTags;

        std::set<std::string> tags = GetTags();

        for (auto tag : tags) {
            std::cout << "----------: " << tag << '\n';
        }

        return result == 0;
    }

   private:
    CatchTestRunner() : session(Catch::Session()) {
        
    }
    Catch::Session session;
};

int main() {
    constexpr auto numruns = 4;
    for (int i = 0; i < numruns; i++) {
        auto res = CatchTestRunner::GetInstance().RunTests();

        std::cout << fullOutput << '\n';

        if (!res) {
            //
            // EventListener::getFailedTestCases();
            // std::cout << "=================output: " << output << '\n';
        }
    }
}