
project(modules)

file(GLOB modules ${CMAKE_CURRENT_SOURCE_DIR} "*/CMakeLists.txt")

foreach(dir ${modules})
    
    if(${dir} MATCHES "^(.*)//CMakeLists.txt")
        string(REGEX REPLACE "^(.*)//CMakeLists.txt" "\\1" dir_trimmed ${dir})

        string(REGEX REPLACE "^(.*)/([^/]*$)" "\\2" name_module ${dir_trimmed})
        message("~~~ Found module \"${name_module}\" try add it")
        add_subdirectory(${dir_trimmed})
    endif()
endforeach(dir)


