set(APP_NAME ClientApp)

file(GLOB_RECURSE SOURCES "src/*.cpp"  "include/*.h")
add_executable(${APP_NAME} ${SOURCES})

target_include_directories(${APP_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_link_directories(${APP_NAME} PRIVATE ${Boost_LIBRARY_DIR})
target_link_libraries(${APP_NAME} PRIVATE Boost::system)