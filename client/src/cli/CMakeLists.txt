set(HDRS 
      chessCli.h
      )
 
set(SRCS
      chessCli.cpp
      generateMoves.cpp
      removeCastle.cpp
      check.cpp
)

add_library(ChessCli ${HDRS} ${SRCS})
target_link_libraries(ChessGui)
