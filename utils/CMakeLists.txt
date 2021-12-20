add_subdirectory(common_util)
add_subdirectory(net_util)
add_subdirectory(thread_util)


#list(APPEND COMMON_LIBRARIES common_util net_util thread_util)
#
#if (WIN32)
#    LIST(APPEND COMMON_LIBRARIES wsock32 ws2_32)
#elseif(LINUX)
#    LIST(APPEND COMMON_LIBRARIES pthread)
#endif()
