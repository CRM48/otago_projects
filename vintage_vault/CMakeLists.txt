cmake_minimum_required(VERSION 3.8)
project("VintageVault" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # Changed from 20 to 17 for broader compatibility
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Code coverage flags (only for GCC/Clang)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Main application source files
set(MAIN_SOURCES
    main.cpp
    hangman.cpp
    newwordle.cpp
    secretNumber.cpp
    TicTacToe.cpp
    home.cpp
    startmusic.cpp
)

# Test source files
set(TEST_SOURCES
    ./tests/runAllTest.cpp
    ./tests/test_hangman.cpp
    ./tests/test_newwordle.cpp
    ./tests/test_tictactoe.cpp
    ./tests/test_secretNumber.cpp
)

# Add main executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

# Link Windows audio library
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()

# Add test executable
add_executable(${PROJECT_NAME}_test 
    ${TEST_SOURCES} 
    hangman.cpp 
    newwordle.cpp 
    TicTacToe.cpp 
    secretNumber.cpp)

# Common settings for both executables
foreach(TARGET ${PROJECT_NAME} ${PROJECT_NAME}_test)
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_definitions(${TARGET} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        UNIT_TESTING
    )
    set_target_properties(${TARGET} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()

# Copy game resources alongside the executable
foreach(FILE_TO_COPY dictionary.txt wordlength5.txt music.wav)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/${FILE_TO_COPY}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${FILE_TO_COPY}"
        VERBATIM
    )
endforeach()

# Enable testing
enable_testing()

# Add test
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)