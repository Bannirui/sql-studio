project(sha_test)

aux_source_directory(. SRCS)
add_executable(${PROJECT_NAME} ${SRCS})

add_test(NAME ${PROJECT_NAME}
        COMMAND "./${PROJECT_NAME}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})