add_library(dsc-miner dsc-miner.cpp)
target_include_directories(dsc-miner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(dsc-miner PRIVATE choma fmt::fmt)
