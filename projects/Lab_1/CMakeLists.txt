project(Lab_1_scanner)

file(GLOB SOURCE src/*.cpp src/*.cxx)

add_executable(${PROJECT_NAME} ${SOURCE})

list(APPEND HLP_DEPS iphlpapi)

if (MINGW)
 list(APPEND HLP_DEPS icmp)
endif()

target_link_libraries(${PROJECT_NAME} ${COMMON_LIBRARIES} ${HLP_DEPS})
