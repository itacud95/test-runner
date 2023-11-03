#include "catch2/catch_all.hpp"
#include <iostream>

TEST_CASE("Foo Test") {
    std::cout << "foo test\n";
    REQUIRE(true);
}
