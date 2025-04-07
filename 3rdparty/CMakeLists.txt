set(ABSL_USE_SYSTEM_INCLUDES ON)
set(ABSL_ENABLE_INSTALL OFF)
add_subdirectory(abseil-cpp)

add_subdirectory(choma-cmake)

set(FMT_DOC OFF)
set(FMT_TEST OFF)
add_subdirectory(fmt)
