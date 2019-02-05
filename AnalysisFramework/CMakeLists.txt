cmake_minimum_required(VERSION 2.8.9)

project (hhbbyy)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "-std=c++1y")

#file(GLOB SOURCES "src/main.cxx")
add_executable(hhbbyy src/main.cxx src/YieldIterator.cxx src/JSONParser.cxx src/Controller.cxx)
target_link_libraries(hhbbyy ${ROOT_LIBRARIES} )

#add_executable(hhbbyy_data src/main_data.cxx)
#target_link_libraries(hhbbyy_data ${ROOT_LIBRARIES} )

set(hhbbyy_SCRIPTS
#	samples.js
#        data_sample.js
        computeYieldsEffs.js
   )
foreach(_script ${hhbbyy_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/json/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
