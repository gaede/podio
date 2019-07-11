# This is needed for older ROOTs which do not understand
# target usage requirements
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources *.cc)
file(GLOB headers ${CMAKE_SOURCE_DIR}/include/podio/*.h)

# --- rm SIO stuff from library if not needed - fixme should go to sub dir ...
if(NOT SIO_FOUND)
  list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/SIOWriter.cc)
  list(REMOVE_ITEM headers ${CMAKE_SOURCE_DIR}/include/podio/SIOWriter.h)
  list(REMOVE_ITEM headers ${CMAKE_SOURCE_DIR}/include/podio/SIOBlock.h)
endif()

MESSAGE( STATUS " sources: ${sources}" )
MESSAGE( STATUS " sources: ${headers}" )

# Main Library
add_library(podio SHARED ${headers} ${sources})
target_include_directories(podio PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(podio PUBLIC ROOT::RIO ROOT::Tree)

# Add alias target to ease "subproject" usage
add_library(podio::podio ALIAS podio)

# Dict Library
REFLEX_GENERATE_DICTIONARY(podio ${headers} SELECTION selection.xml)
add_library(podioDict SHARED podio.cxx)
add_dependencies(podioDict podio-dictgen)
target_link_libraries(podioDict podio ROOT::Core)

if(SIO_FOUND)
  target_link_libraries(podio     ${SIO_LIBRARIES})
  target_link_libraries(podioDict ${SIO_LIBRARIES})
endif()


# Install the Targets and Headers
install(TARGETS podio podioDict
  EXPORT podioTargets
  DESTINATION "${CMAKE_INSTALL_LIBDIR}")


install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/podio DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/podioDict.rootmap
  ${CMAKE_CURRENT_BINARY_DIR}/podio_rdict.pcm
  DESTINATION "${CMAKE_INSTALL_LIBDIR}")

