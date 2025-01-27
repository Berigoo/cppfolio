#######
# nlohmann/json
#######
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/json")

#######
# inja
#######
SET(INJA_USE_EMBEDDED_JSON OFF)
SET(BUILD_TESTING OFF)
set(INJA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/inja")
add_subdirectory(${INJA_DIR})
include_directories("${INJA_DIR}/include/inja")
