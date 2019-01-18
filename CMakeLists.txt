project(PETemplate)
cmake_minimum_required(VERSION 3.10)
link_directories(${PETemplate_BINARY_DIR}/deps/lib)
include(ExternalProject)
set(ImplementationFiles Source/Implementation.cpp)
add_executable(Benchmark Benchmark/Benchmarks.cpp ${ImplementationFiles})
set_property(TARGET Benchmark PROPERTY CXX_STANDARD 17)
ExternalProject_Add(googlebenchmark
	URL "https://github.com/google/benchmark/archive/v1.4.1.tar.gz"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PETemplate_BINARY_DIR}/deps -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release
  )
add_dependencies(Benchmark googlebenchmark)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Benchmark Threads::Threads)
target_link_libraries(Benchmark ${PETemplate_BINARY_DIR}/deps/lib/${CMAKE_SHARED_LIBRARY_PREFIX}benchmark.a)
target_link_libraries(Benchmark ${PETemplate_BINARY_DIR}/deps/lib/${CMAKE_SHARED_LIBRARY_PREFIX}benchmark_main.a)
if(LINUX)
target_link_libraries(Benchmark ${PETemplate_SOURCE_DIR}/libittnotify.a)
target_link_libraries(Benchmark dl)
endif(LINUX)
target_include_directories(Benchmark SYSTEM PUBLIC ${PETemplate_BINARY_DIR}/deps/include)
target_include_directories(Benchmark PUBLIC ${PETemplate_SOURCE_DIR}/Source)


# * Catch2
ExternalProject_Add(catch2
	URL https://github.com/catchorg/Catch2/archive/v2.9.2.tar.gz
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PETemplate_BINARY_DIR}/deps
)


add_executable(Tests Test/Tests.cpp ${ImplementationFiles})
set_property(TARGET Tests PROPERTY CXX_STANDARD 17)
add_dependencies(Tests catch2)
target_include_directories(Tests SYSTEM PUBLIC ${PETemplate_BINARY_DIR}/deps/include)
target_include_directories(Tests PUBLIC ${PETemplate_SOURCE_DIR}/Source)
