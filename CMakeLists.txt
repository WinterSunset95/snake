cmake_minimum_required(VERSION 3.14)
project(Snake VERSION 1.0 DESCRIPTION "A snake game in c++" LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# SDL
if (WIN32)
	set(SDL_DIR "./SDL3-3.2.10/x86_64-w64-mingw32")
	set(IMG_DIR "./SDL3_image-3.2.4/x86_64-w64-mingw32")
	set(TTF_DIR "./SDL3_ttf-3.2.2/x86_64-w64-mingw32")
else ()
	set(SDL_DIR "/usr")
	set(IMG_DIR "/usr")
	set(TTF_DIR "/usr")
endif()

# Include SDL headers
include_directories(${SDL_DIR}/include ${IMG_DIR}/include ${TTF_DIR}/include)
include_directories(src/include)

# Source files
file(GLOB SOURCES "src/*.c")
message(STATUS "Sources: ${SOURCES}")

# Platform-Specific linking 
if (WIN32)
	message(STATUS "Windows")
	link_directories(${SDL_DIR}/lib ${IMG_DIR}/lib ${TTF_DIR}/lib)
	add_executable(snake ${SOURCES})
	target_link_libraries(snake SDL3 SDL3_image SDL3_ttf)
else ()
	message(STATUS "Linux")
	add_executable(snake ${SOURCES})
	find_package(SDL3 REQUIRED CONFIG)
	target_link_libraries(snake SDL3 SDL3_image SDL3_ttf)
endif()

