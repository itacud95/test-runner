# catch
option(BUILD_SHARED_LIBS "Build shared library" on)

# android logging
if(CMAKE_SYSTEM_NAME MATCHES "Android")
    option(CATCH_CONFIG_ANDROID_LOGWRITE "Android logging" on)
endif()

add_subdirectory(Catch2-3.4.0)

# android logging
target_link_libraries(Catch2 PRIVATE $<$<PLATFORM_ID:Android>:log>)

# For a cleaner output; removes version numbers
#   from .so name and therefore removes symlinks. 
set_property(TARGET Catch2 PROPERTY VERSION)
set_property(TARGET Catch2 PROPERTY SOVERSION)

# Targets (link only with one): 
#   Catch2::Catch2WithMain
#       No custom main function
#   Catch2::Catch2
#       Link with this for custom main
#         int main( int argc, char* argv[] ) {
#             int result = Catch::Session().run( argc, argv ); }

install(TARGETS 
    Catch2
    DESTINATION .)
