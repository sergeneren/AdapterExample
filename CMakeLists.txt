cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(AdapterTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(Houdini_DIR ${HOUDINI_BASE}/toolkit/cmake)
find_package( Houdini REQUIRED )

add_library(UsdInterface INTERFACE)
add_library(usd_ms ALIAS UsdInterface)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindHoudiniUsd.cmake")
include("${HOUDINI_BASE}/toolkit/cmake/HoudiniConfigVersion.cmake")


file( GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file( GLOB SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(SOURCE_FILES
	${HEADERS}
	${SOURCE}
	)
	
add_library(AdapterExample SHARED ${SOURCE_FILES})

target_link_libraries(AdapterExample PRIVATE usd_ms Houdini)

include_directories(${CMAKE_SOURCE_DIR})

install(TARGETS AdapterExample 
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX} #For unix 
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} #For windows
)