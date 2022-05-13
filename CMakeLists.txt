cmake_minimum_required(VERSION 3.22)
project(tidy_custom_tags_bug_example)

set(CMAKE_CXX_STANDARD 14)

add_executable(tidy_custom_tags_bug_example main.cpp)
include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG ee7f91f5566b6279aadf6d0b1aaf56b11963f527) # The commit hash for 1.8.2. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(tidy GIT_REPOSITORY https://github.com/htacg/tidy-html5.git
        GIT_TAG d08ddc2860aa95ba8e301343a30837f157977cba)
FetchContent_MakeAvailable(tidy)

target_link_libraries(
        tidy_custom_tags_bug_example
        tidy-static
        cpr
)

