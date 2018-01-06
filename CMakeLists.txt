cmake_minimum_required(VERSION 3.9)
project(signaldata)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "/home/max/lib/boost/boost_1_66_0/build")
find_package(Boost 1.66 COMPONENTS unit_test_framework regex thread)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(/home/max/miniconda3/pkgs/xsimd-3.1.1-0/include)
include_directories(/home/max/miniconda3/pkgs/xtl-0.3.8-0/include)
include_directories(/home/max/miniconda3/pkgs/xtensor-0.14.1-0/include)


add_executable(signaldata test/auto_test.cpp)

target_link_libraries(signaldata -lpthread ${Boost_LIBRARIES} -lboost_system -lssl -lcrypto)