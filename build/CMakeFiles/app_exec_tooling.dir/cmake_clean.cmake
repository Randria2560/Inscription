file(REMOVE_RECURSE
  "monapp/main.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/app_exec_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
