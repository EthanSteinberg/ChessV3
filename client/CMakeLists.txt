#CMakeLists file for server

set(HDRS 
      )
 
set(SRCS
      src/main.cpp
)


add_executable(ChessClient ${HDRS} ${SRCS})
target_link_libraries(ChessClient ChessCli ChessGui ChessNet)

add_subdirectory(src)
