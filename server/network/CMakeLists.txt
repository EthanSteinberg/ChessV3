set(HDRS 
      chessNetwork.h
      chessConnection.h
      )
 
set(SRCS
      chessNetwork.cpp
      chessConnection.cpp
)

add_library(ChessNetwork ${HDRS} ${SRCS})
target_link_libraries(ChessNetwork)
