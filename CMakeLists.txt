cmake_minimum_required(VERSION 3.25)
project(cppfolio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)
add_subdirectory("${CMAKE_SOURCE_DIR}/libs")

file(GLOB CONTROLLERS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/controllers/*.cpp")
file(GLOB SERVER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/server/*.cpp")
file(GLOB UTILS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/json/*.cpp")

add_library(SERVER STATIC ${SERVER_SOURCE})
target_link_libraries(SERVER ${OPENSSL_LIBRARIES} nlohmann_json::nlohmann_json inja)

add_library(UTILS STATIC ${UTILS_SOURCE})
target_link_libraries(UTILS nlohmann_json::nlohmann_json)
target_compile_definitions(UTILS PRIVATE PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(SERVER UTILS)

add_executable(cppfolio "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" ${CONTROLLERS_SOURCE}) #TODO refactor

target_link_libraries(cppfolio nlohmann_json::nlohmann_json inja SERVER)

install(TARGETS cppfolio DESTINATION "usr/local/bin/cppfolio")


