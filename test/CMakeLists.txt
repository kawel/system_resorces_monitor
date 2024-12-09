# Add Google Test
add_subdirectory(../ext/googletest googletest)

# Set the include directories
set(INCLUDES ../inc

)

# Set the sources
set(TEST_SOURCES
    HwMonitor_test.cpp
    Scheduler_test.cpp
    SysMonitor_test.cpp
    GetOptions_test.cpp
    )

set(SOURCES
    ../src/GetOptions.cpp
    ../src/HwMonitor.cpp
    ../src/logger.cpp  # Include the logger source file
    )

set (MOCK_SOURCES)

# Add the test executable
add_executable(runTests ${TEST_SOURCES} ${MOCK_SOURCES} ${SOURCES})

# Include the specified include directories
target_include_directories(runTests PRIVATE ${INCLUDES})

# Define USE_STDOUT for the test executable
target_compile_definitions(runTests PRIVATE USE_STDOUT)

# Link Google Test and the main project
target_link_libraries(runTests gtest gtest_main
nlohmann_json::nlohmann_json)

# Add tests
# Discover and register tests
include(GoogleTest)
gtest_discover_tests(runTests)