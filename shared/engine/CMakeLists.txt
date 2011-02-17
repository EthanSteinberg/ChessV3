set(HDRS 
      chessEngine.h
      )
 
set(SRCS
      chessEngine.cpp
      generateMoves.cpp
      removeCastle.cpp
      check.cpp
      checkMate.cpp
      addPieceMoves.cpp
      boardClickedSingle.cpp
      chessMoves.cpp
)

add_library(ChessEngine ${HDRS} ${SRCS})
