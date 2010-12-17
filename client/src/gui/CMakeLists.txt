set(HDRS 
      chessGui.h
      )
 
set(SRCS
      chessGui.cpp
)

add_library(ChessGui ${HDRS} ${SRCS})
target_link_libraries(ChessGui ${SFML_LIBRARY})
