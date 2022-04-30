cmake_minimum_required(VERSION 3.16)

set(SOURCES                                                                                                             
  test.cpp
) 

#
# Build a test with logging ON for all severities at build time
#
set(PERF_TARGET papi_client.tsk)
add_executable(${PERF_TARGET} ${SOURCES})
target_compile_options(${PERF_TARGET} PUBLIC -g)
target_include_directories(${PERF_TARGET} PUBLIC /root/local/include)
find_library(PAPI_LIB papi HINTS /root/local/lib)
target_link_libraries(${PERF_TARGET} ${PAPI_LIB})
