set(ABSL_USE_SYSTEM_INCLUDES ON)
set(ABSL_ENABLE_INSTALL OFF)
add_subdirectory(abseil-cpp)

add_subdirectory(binja-arm64dis)

set(CAPSTONE_BUILD_MACOS_THIN ON)
set(CAPSTONE_BUILD_CSTOOL ON)
set(CAPSTONE_AARCH64_SUPPORT ON)
set(CAPSTONE_ARCHITECTURE_DEFAULT OFF)
add_subdirectory(capstone)

add_subdirectory(choma-cmake)

set(FMT_DOC OFF)
set(FMT_TEST OFF)
add_subdirectory(fmt)
