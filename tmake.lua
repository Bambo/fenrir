RequireVersion("2.0")

Project("fenrir", "C++")
AddPackage("luajit")
AddPackage("physfs")
AddDefinition("__DEBUG") -- Remove when not debugging
AddCFlag("-Wall")

AddSource("fenrir.cpp", "LuaResource.cpp", "LuaState.cpp", "LuaValue.cpp")

CreateExecutable("fenrir")
