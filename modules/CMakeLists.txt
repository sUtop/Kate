

message("~~~I try to find some modules!")

file(GLOB modules ${CMAKE_CURRENT_SOURCE_DIR} "*/CMakeLists.txt")

# Парсер поддиректорий (с) http://nctusdk.blogspot.co.uk/2011/10/add-all-subdirectories-in-cmake.html

foreach(dir ${modules})
    message("~~~ Find dir  ${dir}")

#    if(${dir} MATCHES "^([^/]*)//CMakeLists.txt")
    if(${dir} MATCHES "^[*]//CMakeLists.txt")
#    if(${dir} MATCHES "^[*]//CM[*]")
        message("               ! Hay !         ")
        string(REGEX REPLACE "^([^/]*)//CMakeLists.txt" "\\1" dir_trimmed ${dir})
#        string(REGEX REPLACE "*//CMakeLists.txt" "" dir_trimmed ${dir})
        add_subdirectory(${dir_trimmed})

        message("Find module ${dir_trimmed}")
    endif()
endforeach(dir)


