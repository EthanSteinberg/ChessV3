set(HDRS 
      chessGui.h
      chessCegui.h
      )
 
set(SRCS
      chessCegui.cpp
      chessGui.cpp
)

add_library(ChessGui ${HDRS} ${SRCS})
target_link_libraries(ChessGui ${SFML_LIBRARY} ${CEGUI_LIBRARY} CEGUIOpenGLRenderer.so)
