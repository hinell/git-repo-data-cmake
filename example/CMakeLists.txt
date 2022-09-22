cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(
  ExampleProject
  DESCRIPTION  "Example on how to Use GitRepoData "
  HOMEPAGE_URL "htts://github.com/hinell/gitrepodata-cmake"
  # VERSION # IMPORTED FROM A TOP-LEVEL PROJECT, SEE BELOW
  LANGUAGES CXX
)

#-----------------------------------------------------------Project-wide modules
list(APPEND CMAKE_MODULE_PATH "cmake/")
include_guard(GLOBAL)
include(CMakeFindDependencyMacro)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(CMakePrintHelpers)
include(FeatureSummary)
if(UNIX)
  include(GNUInstallDirs)
endif()

# find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
# TODO: [September 19, 2022] Remove this when finished
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../.dist")
find_package(GitRepoData 1.0.0 QUIET REQUIRED)

#---------------------------------------------------------------------------Misc
# Enable GraphViz custom targets
file(WRITE
  "${CMAKE_CURRENT_BINARY_DIR}/CMakeGraphVizOptions.cmake"
  "set(GRAPHVIZ_CUSTOM_TARGETS TRUE)"
)

#------------------------------------------------------------------------Targets


# Git repository header file interface library
GITRepoData_Target(
	"example-git-version"
	OUTPUT_PATH "include/example-git-version.hh"
	PREFIX "GIT"

	SYMBOLS
		BRANCH

		# By default only version and commit hash is exported
		VERSION
		# Explicit
		VERSION_MAJOR
		VERSION_MINOR
		VERSION_PATCH
		VERSION_TWEAK

		VERSION_DIST

		COMMIT_BODY
		COMMIT_HASH
		COMMIT_DATE_RELATIVE
		COMMIT_DATE_UNIX_STAMP
		COMMIT_DATE_ISO8601

		COMMIT_DATE
		COMMIT_SUBJECT
		COMMIT_AUTHOR
		COMMIT_EMAIL

		COMMIT_REPOLINK

)
cmake_print_variables(GITREPODATA_TARGETNAME)

#------------------------------------------------------------------------example
add_executable(example "example.cc")
# DEPENDENCY is any of: target name, library name (e.g. zlib),
target_link_libraries(
	example
	PRIVATE ${GITREPODATA_TARGETNAME}
)
set_target_properties(
	example
	PROPERTIES
		WIN32_EXECUTABLE      $<IF:$<PLATFORM_ID:Windows>,TRUE,FALSE>
		MACOSX_BUNDLE         $<IF:$<PLATFORM_ID:Darwin>,TRUE,FALSE>
		CXX_COMPILER_LAUNCHER ccache
		C_COMPILER_LAUNCHER   ccache
		LINKER_LANGUAGE       CXX
		ENABLE_EXPORTS        FALSE
		#RESOURCE             "list;of;files"

		BUILD_WITH_INSTALL_RPATH  $<IF:$<INSTALL_INTERFACE>,TRUE,FALSE>
		INSTALL_RPATH_USE_LINK_PATH TRUE
		INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}/${PACKAGE_GROUP_NAME}-${PROJECT_VERSION_MAJOR}"
)

if(TARGET ${GITREPODATA_TARGETNAME})
	message(STATUS "+++=GitRepoData ${GITREPODATA_TARGETNAME} target successfully created in parent scope")
endif()

# Put this at the bottom of the CMakeLists.txt
feature_summary(
	WHAT PACKAGES_FOUND
	INCLUDE_QUIET_PACKAGES
	DESCRIPTION "Imported packages:"
)
