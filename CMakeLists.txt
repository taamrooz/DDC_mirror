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
	set(VCPKG_TARGET_TRIPLET x64-windows)
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
	find_package(SDL2_image REQUIRED)
    target_include_directories(SWA
        PRIVATE
        "${SDL2_INCLUDE_DIR}"
		"${SDL2_IMAGE_INCLUDE_DIRS}"
    )
    target_link_libraries(SWA
        PRIVATE
        "${SDL2_LIBRARY}"
		"${SDL2_IMAGE_LIBRARIES}"
    )
endif()