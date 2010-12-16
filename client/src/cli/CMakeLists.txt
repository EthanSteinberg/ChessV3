set(HDRS 
      chessCli.h
      )
 
set(SRCS
      chessCli.cpp
)

add_library(ChessCli ${HDRS} ${SRCS})
#target_link_libraries(ChessGui)
