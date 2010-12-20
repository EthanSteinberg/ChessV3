#CMakeLists file for server

set(HDRS 
      )
 
set(SRCS
      src/main.cpp
)


add_executable(ChessServer ${HDRS} ${SRCS})
target_link_libraries(ChessServer ChessNetwork)

add_subdirectory(src)
