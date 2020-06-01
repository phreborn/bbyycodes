#cmake_minimum_required(VERSION 2.8.9)
cmake_minimum_required(VERSION 3.1)

project (hhbbyy)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED)
#find_package(vdt REQUIRED)

#include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS} /cvmfs/sft.cern.ch/lcg/releases/LCG_97_ATLAS_1/vdt/0.4.3/x86_64-centos7-gcc8-opt/include)

include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSION OFF)
#SET(CMAKE_CXX_FLAGS "-std=c++1z")

#file(GLOB SOURCES "src/main.cxx")
add_executable(hhbbyy 
		src/main.cxx 
		src/JSONParser.cxx 
		src/YieldIterator.cxx
		src/ROOTHelper.cxx 
		src/DataAnalysis.cxx
		src/VariablePlotter.cxx 
		src/Controller.cxx
		src/Plotting.cxx
		src/PrettyPlotter.cxx
                src/NtupleDumper.cxx)
target_link_libraries(hhbbyy ${ROOT_LIBRARIES} )

#add_executable(hhbbyy_data src/main_data.cxx)
#target_link_libraries(hhbbyy_data ${ROOT_LIBRARIES} )

set(hhbbyy_SCRIPTS
#	samples.js
        dataAnalysis.js
        computeYieldsEffs.js
        computeYieldsEffs_allSelections.js
        computeYieldsEffs_allSelections_HHNLOBugFix.js
        computeYieldsEffs_photonJetBkg.js
        computeYieldsEffs_allSelections_resonantSignals.js
        computeYieldsEffs_allSelections_nonResonantSignals.js
   )

foreach(_script ${hhbbyy_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/json/${_script}
    ${PROJECT_BINARY_DIR}/../run/${_script}
    COPYONLY
    )
endforeach()

set_target_properties(hhbbyy PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/run/
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ln -sf -t ${PROJECT_SOURCE_DIR}/run/ ${PROJECT_SOURCE_DIR}/json/
    COMMAND ln -sf -t ${PROJECT_SOURCE_DIR}/run/ ${PROJECT_SOURCE_DIR}/utils/RunCondor.sh
    COMMAND ln -sf -t ${PROJECT_SOURCE_DIR}/run/ ${PROJECT_SOURCE_DIR}/utils/SubmitCondor.py
)

