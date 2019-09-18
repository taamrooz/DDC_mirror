cmake_minimum_required(VERSION 3.14)

project(SWA)

add_executable(SWA 
	SWA/main.cpp
	SWA/Core.cpp
	SWA/System.cpp
	SWA/Entity.cpp
	SWA/Component.cpp
	)


if(CMAKE_TOOLCHAIN_FILE)
    message("Using SDL2 toolchain file")
    message(${CMAKE_TOOLCHAIN_FILE})
    find_package(SDL2 CONFIG REQUIRED)
    target_link_libraries(SWA 
        PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
    )
else()
    message("Finding SDL2")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
    find_package(SDL2 REQUIRED)

    target_include_directories(SWA
        PRIVATE
        "${SDL2_INCLUDE_DIR}"
    )
    target_link_libraries(SWA
        PRIVATE
        "${SDL2_LIBRARY}"
    )
endif()


