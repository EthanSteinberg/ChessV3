#CMakeLists file for client

set(HDRS 
      )
 
set(SRCS
      main.cpp
)


add_executable(ChessServer ${HDRS} ${SRCS})
target_link_libraries(ChessServer ChessNetwork ChessCli2 ${Boost_LIBRARIES})

add_subdirectory(cli)
add_subdirectory(network)
