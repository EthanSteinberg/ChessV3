#CMakeLists file for client

set(HDRS 
      )
 
set(SRCS
      main.cpp
)


add_executable(ChessServer ${HDRS} ${SRCS})
#target_link_libraries(ChessServer ChessNetwork ChessGame ${Boost_LIBRARIES} ${GTK2_LIBRARIES})
target_link_libraries(ChessServer ChessNetwork ChessGame ${Boost_LIBRARIES})

add_subdirectory(game)
add_subdirectory(network)
