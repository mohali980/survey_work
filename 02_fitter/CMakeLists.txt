set(FITTER_INPUT "")
if(XCODE)
  file(GLOB FITTER_INPUT *.txt *.mac)
  source_group("Other Files" FILES ${FITTER_INPUT})
endif()

add_executable(fitter fitter.cc surveymarker.cpp surveymarker.hpp  ${FITTER_INPUT})
add_executable(transformer transformer.cc surveymarker.cpp surveymarker.hpp  ${FITTER_INPUT})

add_definitions(${Geant4_DEFINITIONS})
target_link_libraries(fitter g4PSIlib ${LINKLIBS}  cminpack) 
target_link_libraries(transformer g4PSIlib ${LINKLIBS} ) 

if (isStandalone)
  INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/../external/cminpack")
else()
  INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/external/cminpack")
endif()