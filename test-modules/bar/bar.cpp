#include "catch2/catch_all.hpp"
#include <iostream>

TEST_CASE("Bar Test") {
    std::cout << "bar test\n";
    REQUIRE(true);
}
