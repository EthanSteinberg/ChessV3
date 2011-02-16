#CMakeLists file for client

set(HDRS 
      )
 
set(SRCS
      main.cpp
)


add_executable(ChessClient ${HDRS} ${SRCS})
target_link_libraries(ChessClient ChessNet ChessCli ChessGui ${Boost_LIBRARIES})

add_subdirectory(gui)
add_subdirectory(cli)
add_subdirectory(net)

