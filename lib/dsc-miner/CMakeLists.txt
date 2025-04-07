set(DSCM_SRC
    dsc-miner.cpp
)

set(DSCM_HDR_STANDALONE
    bitvec.hpp
    histogram.hpp
)

set(DSCM_HDR_STANDALONE_PRIVATE
)

set(DSCM_HDR)
foreach(HDR ${DSCM_HDR_STANDALONE})
    set(RELHDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/dsc-miner/${HDR}")
    if(NOT EXISTS ${RELHDR})
        message(ERROR "DSCM_HDR_STANDALONE missing: ${HDR} ${RELHDR}")
    endif()
    list(APPEND DSCM_HDR ${RELHDR})
endforeach()

foreach(HDR ${DSCM_HDR_STANDALONE_PRIVATE})
    set(RELHDR "${CMAKE_CURRENT_SOURCE_DIR}/${HDR}")
    if(NOT EXISTS ${RELHDR})
        message(ERROR "DSCM_HDR_STANDALONE_PRIVATE missing: ${HDR} ${RELHDR}")
    endif()
    list(APPEND DSCM_HDR ${RELHDR})
endforeach()

foreach(SRC ${DSCM_SRC})
    get_filename_component(HDR_NAME ${SRC} NAME_WLE)
    set(HDR "${CMAKE_CURRENT_SOURCE_DIR}/../../include/dsc-miner/${HDR_NAME}.hpp")
    if(EXISTS ${HDR})
        list(APPEND DSCM_HDR ${HDR})
    endif()
endforeach()

set(DSCM_PUBLIC_LIBS
)

set(DSCM_PRIVATE_LIBS
    absl::flat_hash_map
    choma
    fmt::fmt
)

# DSCM_HDR added for Xcode project generation
add_library(dsc-miner ${DSCM_SRC} ${DSCM_HDR})
set_target_properties(dsc-miner PROPERTIES PUBLIC_HEADER "${DSCM_HDR}")

target_link_libraries(dsc-miner
PUBLIC
    ${DSCM_PUBLIC_LIBS}
PRIVATE
    ${DSCM_PRIVATE_LIBS}
)

target_include_directories(dsc-miner
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(dsc-miner PROPERTIES
    CXX_STANDARD 23
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED ON
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)
