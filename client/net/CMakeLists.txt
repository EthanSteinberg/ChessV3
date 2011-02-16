set(HDRS 
      chessNet.h
      )
 
set(SRCS
      chessNet.cpp
      connected.cpp
)

add_library(ChessNet ${HDRS} ${SRCS})
target_link_libraries(ChessNet)
