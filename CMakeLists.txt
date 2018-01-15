cmake_minimum_required(VERSION 2.8)

project(MarginCrop)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
#find_package(Boost COMPONENTS system filesystem thread REQUIRED)
find_package(Boost COMPONENTS system filesystem chrono date_time thread program_options REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(MarginCrop main.cpp)

target_link_libraries(MarginCrop ${ITK_LIBRARIES} ${Boost_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})