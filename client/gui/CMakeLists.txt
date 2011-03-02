
set(HDRS 
      chessGui.h
      )
 
set(SRCS
      chessGui.cpp
      chessServer.cpp
      chessGtkmm.cpp
      chessSfml.cpp
)


add_library(ChessGui ${HDRS} ${SRCS})
target_link_libraries(ChessGui ${GTK2_LIBRARIES} ${SFML_LIBRARY} ${Boost_LIBRARIES})
