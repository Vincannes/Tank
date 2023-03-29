# =============================================================================
# JSON
# =============================================================================

add_library(
	rapidjson
)
target_include_directories(cxxurl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/rapidjson")
