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
      processMessageSingle.cpp
      processMessageConnected.cpp
      boardClickedSingle.cpp
      chessMoves.cpp
)

add_library(ChessCli ${HDRS} ${SRCS})
target_link_libraries(ChessCli ChessEngine)
