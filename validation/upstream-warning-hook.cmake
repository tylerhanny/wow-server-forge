# OWNER-AUTHORIZED BASELINE EXCEPTION. No dependency file is rewritten.
# Loaded by the judge through CMAKE_PROJECT_AzerothCore_INCLUDE.
if(NOT PROJECT_NAME STREQUAL "AzerothCore")
  message(FATAL_ERROR "Forge baseline hook requires the AzerothCore project")
endif()
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(FATAL_ERROR "Forge baseline diagnostic is validated with Clang")
endif()
get_property(_forge_already_scheduled GLOBAL PROPERTY FORGE_BASELINE_SCHEDULED)
if(_forge_already_scheduled)
  message(FATAL_ERROR "Forge baseline hook must run exactly once")
endif()
file(READ "${CMAKE_CURRENT_LIST_DIR}/upstream-warning-allowlist.json" _forge_policy)
string(JSON _forge_relative GET "${_forge_policy}" path)
string(JSON _forge_sha256 GET "${_forge_policy}" sha256)
set_property(GLOBAL PROPERTY FORGE_BASELINE_SCHEDULED TRUE)
set_property(GLOBAL PROPERTY FORGE_BASELINE_SOURCE "${CMAKE_SOURCE_DIR}/modules/mod-playerbots/${_forge_relative}")
set_property(GLOBAL PROPERTY FORGE_BASELINE_SHA256 "${_forge_sha256}")

function(forge_apply_exact_upstream_warning_exception)
  get_property(_source GLOBAL PROPERTY FORGE_BASELINE_SOURCE)
  get_property(_expected GLOBAL PROPERTY FORGE_BASELINE_SHA256)
  if(NOT TARGET modules OR NOT EXISTS "${_source}" OR IS_SYMLINK "${_source}")
    message(FATAL_ERROR "Forge baseline source/modules target is missing or invalid")
  endif()
  file(SHA256 "${_source}" _actual)
  if(NOT _actual STREQUAL _expected)
    message(FATAL_ERROR "Forge baseline source identity changed before generation")
  endif()
  # Source properties must be applied in the directory that creates modules.
  set_property(SOURCE "${_source}" DIRECTORY "${CMAKE_SOURCE_DIR}/modules"
    APPEND PROPERTY COMPILE_OPTIONS "-Wno-error=unused-parameter")
  message(STATUS "OWNER-AUTHORIZED BASELINE EXCEPTION: one immutable upstream source; full log verification required")
endfunction()

# Run after add_subdirectory(modules), before compile-command generation.
cmake_language(DEFER CALL forge_apply_exact_upstream_warning_exception)
