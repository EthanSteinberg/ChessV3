set(HDRS 
      chessCli.h
      )
 
set(SRCS
      chessCli.cpp
      generateMoves.cpp
      removeCastle.cpp
      check.cpp
      checkMate.cpp
      addPieceMoves.cpp
)

add_library(ChessCli2 ${HDRS} ${SRCS})
target_link_libraries(ChessNetwork)
