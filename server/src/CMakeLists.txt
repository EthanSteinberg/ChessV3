#CMakeLists file for server

set(CMAKE_BUILD_TYPE Debug)

set(LIBS  "-L/usr/local/lib -lclan22GL -lclan22Display -lpng -ljpeg -lfreetype -lz -lfontconfig -lX11 -lclan22Core -lclan22CSSLayout -lpthread -lCEGUIOpenGLRenderer -lCEGUIBase")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -march=native -O2 ${LIBS}")

set(HDRS 
      )
 
set(SRCS
      main.cpp
)

add_executable(App ${HDRS} ${SRCS})
target_link_libraries(App ${ClanLib_LIBRARIES})

