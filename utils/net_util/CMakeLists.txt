project(net_util)

file(GLOB SOURCE src/*.cpp src/*.cxx)

add_library(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} common_util)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
