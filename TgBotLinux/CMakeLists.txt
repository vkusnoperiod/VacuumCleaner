cmake_minimum_required(VERSION 3.10.2)
project(TgBotLinux)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)
set(JSONCPP_LIB_PATH "/usr/lib/x86_64-linux-gnu/libjsoncpp.so")

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

include_directories("/usr/include/jsoncpp/json")

include_directories("~/TgBotLinux")

include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(TgBotLinux src/main.cpp src/methods.cpp)
target_link_libraries(TgBotLinux /usr/local/lib/libTgBot.a
        ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${JSONCPP_LIB_PATH})