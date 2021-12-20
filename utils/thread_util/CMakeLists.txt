project(thread_util)

file(GLOB SOURCE src/*.cpp src/*.cxx)

add_library(${PROJECT_NAME} ${SOURCE})

if (UNIX)
 list(APPEND ADDITIONALS pthread)
else()
 list(APPEND ADDITIONALS "")
endif()

target_link_libraries(${PROJECT_NAME} ${ADDITIONALS})

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
