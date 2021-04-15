################################################################################
# Package: HHyybb
################################################################################

# Declare the package name:
atlas_subdir( HHyybb )

# Declare the package dependencies:
atlas_depends_on_subdirs( PUBLIC
                          HGamCore/HGamAnalysisFramework
    			  PhysicsAnalysis/Interfaces/PMGAnalysisInterfaces
    			  PhysicsAnalysis/AnalysisCommon/PMGTools
                        )

# Find the needed external(s):
#find_package( ROOT COMPONENTS Core RIO Hist Tree RooFitCore )
#find_package( ROOT COMPONENTS Core RIO Hist Tree RooFitCore Net )
find_package( ROOT COMPONENTS Core RIO Hist Tree RooFitCore Net LHAPDF )

# build a CINT dictionary for the library
atlas_add_root_dictionary ( HHyybbLib HHyybbCintDict
                            ROOT_HEADERS HHyybb/tool_Experimental_Systematics.h Root/LinkDef.h
                            EXTERNAL_PACKAGES ROOT
                            )


# build a shared library
atlas_add_library( HHyybbLib
                   HHyybb/*.h Root/*.cxx ${HHyybbCintDict}
                   PUBLIC_HEADERS HHyybb
                   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
                   LINK_LIBRARIES ${ROOT_LIBRARIES}
                   HGamAnalysisFrameworkLib
		   hhTruthWeightToolsLib
		   PMGAnalysisInterfacesLib
                   )

# Install files from the package:
atlas_install_data( data/* )

# Install scripts from the package:
# atlas_install_scripts( scripts/*.sh scripts/*.py )

atlas_add_executable( runtool_Experimental_Systematics util/runtool_Experimental_Systematics.cxx
                      INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
                      LINK_LIBRARIES ${ROOT_LIBRARIES} HHyybbLib )
