add_definitions(-D__DEBUG)
add_executable(fenrir fenrir.cpp LuaState.cpp LuaValue.cpp)
target_link_libraries(fenrir ${LUA_LIBRARIES} ${PHYSFS_LIBRARY})