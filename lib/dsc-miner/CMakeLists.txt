add_library(dsc-miner dsc-miner.cpp)
target_include_directories(dsc-miner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(dsc-miner PRIVATE choma fmt::fmt)
set_target_properties(dsc-miner PROPERTIES
    CXX_STANDARD 23
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED ON
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)
