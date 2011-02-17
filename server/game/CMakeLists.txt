set(HDRS 
      chessGame.h
      )
 
set(SRCS
      chessGame.cpp
      processMessageServer.cpp
)

add_library(ChessGame ${HDRS} ${SRCS})
target_link_libraries(ChessGame ChessEngine)
