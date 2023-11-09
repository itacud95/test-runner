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


TEST_CASE("Bar Test") {
    log("bar test");
    REQUIRE(true);
}
