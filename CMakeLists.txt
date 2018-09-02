cmake_minimum_required (VERSION 2.8)

include_directories(SYSTEM
    ./
)

set(CMAKE_CXX_FLAGS 
"${CMAKE_CXX_FLAGS} -std=c++11 -O1 -fsanitize=address -Wall -Wextra -Wno-unused-command-line-argument -Wshadow -Wnon-virtual-dtor -pedantic"
)


# enum your files
add_executable(executable
  
)

target_link_libraries(executable -fsanitize=address)
