#Top level CMakeLists.txt file for DNetLib

cmake_minimum_required(VERSION 3.2)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("DNetLib" VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-format-style='file'")
# Include sub-projects.
add_subdirectory("DNetLib")

if(CMAKE_CXX_MTEST STREQUAL "ON")
	add_subdirectory("cTest")
else()
	add_subdirectory("server")
	add_subdirectory("client")
#run all executable after build project
add_custom_target(run_all ALL
	DEPENDS server client
	COMMAND ${CMAKE_COMMAND} -E echo "Running all"
	COMMAND ${CMAKE_COMMAND} -E echo "Running server"
	COMMAND start $<TARGET_FILE:server>
	COMMAND ${CMAKE_COMMAND} -E echo "Running client"
	COMMAND start $<TARGET_FILE:client>
	)
#add_custom_target(run_server 
#	DEPENDS server
#	COMMAND ${CMAKE_COMMAND} -E echo "Running server"
#	COMMAND start $<TARGET_FILE:server>
#)
endif()

#add_custom_target(
#    copy-compile-commands ALL
#    ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_BINARY_DIR}/compile_commands.json
#        ${CMAKE_CURRENT_LIST_DIR}
#    )
