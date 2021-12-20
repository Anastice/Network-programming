list(APPEND COMMON_LIBRARIES common_util net_util thread_util)

if (WIN32)
    LIST(APPEND COMMON_LIBRARIES wsock32 ws2_32)
elseif(LINUX)
    LIST(APPEND COMMON_LIBRARIES pthread)
endif()


add_subdirectory(Lab_1)
add_subdirectory(Aud_1)

add_subdirectory(Aud_2)
