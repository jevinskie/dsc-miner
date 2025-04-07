add_executable(dsc-miner-util dsc-miner-util.cpp)
target_link_libraries(dsc-miner-util PRIVATE dsc-miner fmt::fmt)
set_target_properties(dsc-miner-util PROPERTIES
    CXX_STANDARD 23
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED ON
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)
