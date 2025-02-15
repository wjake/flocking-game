cmake_minimum_required(VERSION 3.12)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(FlockingGameBuild)
set(TargetName FlockingGame)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(SOURCES
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/Game.cpp
	${PROJECT_SOURCE_DIR}/src/Entity.cpp
	${PROJECT_SOURCE_DIR}/src/Animation.cpp
	${PROJECT_SOURCE_DIR}/src/Flocking.cpp
	${PROJECT_SOURCE_DIR}/src/Sprite.cpp
	${PROJECT_SOURCE_DIR}/src/Arena.cpp
	${PROJECT_SOURCE_DIR}/src/Prop.cpp
	${PROJECT_SOURCE_DIR}/include/Game.h
	${PROJECT_SOURCE_DIR}/include/Entity.h
	${PROJECT_SOURCE_DIR}/include/Consumable.h
	${PROJECT_SOURCE_DIR}/include/Animation.h
	${PROJECT_SOURCE_DIR}/include/Flocking.h
	${PROJECT_SOURCE_DIR}/include/Sprite.h
	${PROJECT_SOURCE_DIR}/include/Arena.h
	${PROJECT_SOURCE_DIR}/include/Prop.h)

add_executable(${TargetName})
include_directories(include)

target_sources(${TargetName} PRIVATE ${SOURCES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DGL_SILENCE_DEPRECATION)
	target_link_libraries(${TargetName} PRIVATE "-framework Metal")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set ( PROJECT_LINK_LIBS -lGL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_compile_definitions(_USE_MATH_DEFINES)
	add_compile_definitions(NOMINMAX)
	target_compile_definitions(${TargetName} PRIVATE /wd4251)
endif()

target_link_libraries(${TargetName} PRIVATE SDL2::SDL2-static)
target_link_libraries(${TargetName} PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(${TargetName} PRIVATE rapidjson)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(${TargetName}Tests)
target_include_directories(${TargetName}Tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(${TargetName}Tests PRIVATE UNIT_TEST)

target_sources(${TargetName}Tests PRIVATE ${SOURCES}
	${CMAKE_SOURCE_DIR}/tests/PropTests.cpp
	${CMAKE_SOURCE_DIR}/tests/FlockingTests.cpp
	${CMAKE_SOURCE_DIR}/tests/AnimationTests.cpp
	${CMAKE_SOURCE_DIR}/tests/ConsumableTests.cpp
	${CMAKE_SOURCE_DIR}/tests/EntityTests.cpp
	${CMAKE_SOURCE_DIR}/tests/GameTests.cpp)

target_link_libraries(${TargetName}Tests PRIVATE GTest::gtest GTest::gtest_main SDL2::SDL2-static)
target_link_libraries(${TargetName}Tests PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

gtest_discover_tests(${TargetName}Tests)

add_custom_target(${TargetName}CopyAssets ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/assets
	$<TARGET_FILE_DIR:${TargetName}>/assets
)
