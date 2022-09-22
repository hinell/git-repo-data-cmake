## GITRepoDataTarget()
`GITRepoDataTarge()` is a CMake function that constructs a library target named `<targetname>` in the current `CMakeLists.txt` directory. This library target can further be included as a dependency into other targets by a standard CMake [`target_link_library(...)`][target_link_library] function and tweaked further by others.

This target makes your project context aware and rebuilds it every time git changes its state therefore it's said to be a *built-time*.

> *Square brackes denote an optional entry*

[library target]: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#introduction
[target_link_library]: https://cmake.org/cmake/help/latest/command/target_link_libraries.html


```cmake
# Alias to GITRepoDataTarget
add_library_gitrepodata

GITRepoData_Target(

	# Assigned to global GITREPODATA_TARGETNAME variable
	<TARGET_NAME>

	# Supported languages
	[ LANG "CXX" | "C" ]

	# Path is relative to the current CMAKE_CURRENT_BINARY_DIR
	# and depends on the target name
	[ OUTPUT_PATH "include/${TARGET_NAME}.hh" ]

	# DPRCT: [September 12, 2022] Remove this?
	# Headers to be `#include`d into OUTPUT_PATH header
	# Use this to to provide a type for
	# SYMBOL_STRING_TYPE (below)
	[ INCLUDE "<headerName>" ]


	# Symbols to export to ${HEADER_FILENAME}
	# Every symbol is prefixed by ${PREFIX}
	[ SYMBOL_PREFIX "GIT" | "<user provided>" ]
	[ SYMBOLS
		[BRANCH] # "master"
		# Last tag
		[VERSION]
		[VERSION_MAJOR] # uint
		[VERSION_MINOR] # uint
		[VERSION_PATCH] # uint
		[VERSION_TWEAK] # char*

		[VERSION_DIRTY]
		[VERSION_DIST]

		# Commit
		[COMMIT_BODY]
		[COMMIT_HASH]
		[COMMIT_DATE_RELATIVE]
		[COMMIT_DATE_UNIX_STAMP]	# time_t / signed long
		[COMMIT_DATE_ISO8601]		# 2022-09-12T10:24:54+00:00
		[COMMIT_DATE] 				# 2022-09-12
		[COMMIT_SUBJECT]
		[COMMIT_AUTHOR]
		[COMMIT_EMAIL]

		# Git 'origin' repo link
		# https://... OR git@.../repo.git
		[REPO_LINK]
		...
	]

	# DPRCT: [September 12, 2022] Remove this?
	# Specify a type of exported values
	# default: char*
	[ SYMBOL_STRING_TYPE
		  "char*"
		| "std::string[u8|u16|u32]"
		| "std::string_view"
		| "<user provided>" ]

	# default: uint
	[ SYMBOL_NUMBER_TYPE "uint" | "int" | "<user provided>" ]

	# Export attribute, default: <unset>
	[ SYMBOL_EXPORT_ATTR "<user provided>" ]

)

```

## Configuration

<!-- 	# DPRCT: [September 12, 2022] Remove this? -->
You can configure symbol types and namespace of the `gitrepodata.hh` further by standard CMake commands for targets:

```cmake
target_compile_features("gitrepodata" PUBLIC <...>)
```


