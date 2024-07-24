project(parse_test)

if (APPLE)
    # openssl
    set(OPENSSL_DIR "/usr/local/Cellar/openssl@3/3.3.1")
endif ()
include_directories(
        # OpenSSL库的头文件路径
        ${OPENSSL_DIR}/include
)

aux_source_directory(. SRCS)
add_executable(${PROJECT_NAME} ${SRCS} ./../../mysql/util/util.cpp)
target_link_directories(${PROJECT_NAME}
        # OpenSSL库文件
        PRIVATE ${OPENSSL_DIR}/lib
)
target_link_libraries(${PROJECT_NAME}
        # OpenSSl的库libssl.a
        PRIVATE ssl
)

add_test(NAME ${PROJECT_NAME}
        COMMAND "./${PROJECT_NAME}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})