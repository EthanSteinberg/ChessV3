set(HDRS 
      chessGui.h
      chessComponent.h
      chessMenu.h
      chessServerSelect.h
      )
 
set(SRCS
      chessGui.cpp
      chessComponent.cpp
      chessMenu.cpp
      chessServerSelect.cpp
)

add_library(ChessGui ${HDRS} ${SRCS})
target_link_libraries(ChessGui ${ClanLib_LIBRARIES})
