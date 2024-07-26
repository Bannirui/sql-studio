project(sha_test)

if (APPLE)
    # openssl
    set(OPENSSL_HOME "/usr/local/Cellar/openssl@3/3.3.0")
endif ()
include_directories(
        ../../../mysql-client/include
        # OpenSSL库的头文件路径
        ${OPENSSL_HOME}/include
)

aux_source_directory(. SRCS)
add_executable(${PROJECT_NAME} ${SRCS} ./../../mysql/util/util.cpp)
target_link_directories(${PROJECT_NAME}
        # OpenSSL库文件
        PRIVATE ${OPENSSL_HOME}/lib
)
target_link_libraries(${PROJECT_NAME}
        # OpenSSl的库libssl.a
        PRIVATE ssl
        PRIVATE crypto
)

add_test(NAME ${PROJECT_NAME}
        COMMAND "./${PROJECT_NAME}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})