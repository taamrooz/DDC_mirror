cmake_minimum_required(VERSION 3.14)

project(SWA)

add_executable(SWA 
	SWA/main.cpp
	SWA/EntityManager.cpp
	SWA/MainMenu.cpp
	SWA/SceneManager.cpp
	SWA/Core.cpp
	SWA/BaseSystem.cpp
	SWA/MoveSystem.cpp
	SWA/Component.cpp
	)


if(CMAKE_TOOLCHAIN_FILE)
    message("Using SDL2 toolchain file")
	set(VCPKG_TARGET_TRIPLET x64-windows)
    message(${CMAKE_TOOLCHAIN_FILE})
    find_package(SDL2 CONFIG REQUIRED)
	find_package(SDL2-image CONFIG REQUIRED)
	find_package(libpng CONFIG REQUIRED)
	find_package(SDL2-mixer CONFIG REQUIRED)
	find_package(ZLIB REQUIRED)
	find_package(sdl2-ttf CONFIG REQUIRED)
	
    target_link_libraries(SWA 
        PRIVATE
        SDL2
        SDL2main
		SDL2_image
		png
		SDL2_mixer
		ZLIB::ZLIB
		SDL2_ttf
    )
else()
    message("Finding SDL2")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
    find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	find_package(SDL2_mixer REQUIRED)
	find_package(SDL2_TTF REQUIRED)
    target_include_directories(SWA
        PRIVATE
        "${SDL2_INCLUDE_DIR}"
		"${SDL2_IMAGE_INCLUDE_DIRS}"
		"${SDL2_MIXER_INCLUDE_DIRS}"
		"${SDL2_TTF_INCLUDE_DIRS}"
    )
    target_link_libraries(SWA
        PRIVATE
        "${SDL2_LIBRARY}"
		"${SDL2_IMAGE_LIBRARIES}"
		"${SDL2_MIXER_LIBRARIES}"
		"${SDL2TTF_LIBRARY}"
    )
endif()
#include(FindBoost)
#message(${CMAKE_MODULE_PATH})
#find_package(Boost REQUIRED)
#if(Boost_FOUND)
#	include_directories(${Boost_INCLUDE_DIRS})
#endif()