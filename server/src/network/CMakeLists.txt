set(HDRS 
      chessNetwork.h
      )
 
set(SRCS
      chessNetwork.cpp
)

add_library(ChessNetwork ${HDRS} ${SRCS})
target_link_libraries(ChessNetwork)
