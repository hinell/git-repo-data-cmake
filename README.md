# GITRepoData for CMake
>Embed your git data into a CMake C/C++ project.</br>

>Provides a custom [CMake] build target producing a header file tracking current git repostiry version & hashes (etc.) & few utilities functions that inject the version into a current CMake cache during build-time.

### Features
* No redundant files, completly self-contained script / single header
* Built-time tracking of git changes (commit, branch, etc.)
* Support for [Semver 2.0.] specs for Version parsing
* Provides a global module for optimal reuse
* GNU/Linux & Windows support
* Auto-installing/packaging
* C/C++ support

# Install
> The following instructions assume knowledge of CMake ecosystem

## System-wide
### From .zip archive
You can either download a release `.zip` file, unzip it into an appropriate folder or clone entire repo into global `<path>` and run `cmake --*` instructions below.

### From Github repo

<!-- TODO: [September 11, 2022] Add repo link -->
```bash
	$ git clone --depth 1 --single-branch ... <path>
	$ pushd into <path>
```

## Install: Linux / Windows
In the folder, where you cloned this repo or unzipped release `.zip` file, run the following commands.

```bash
	$ cmake --preset common
	$ cmake --build --preset common
	$ cmake --install ./.build
```
> NOTE: This step is done only when updating the cloned repo. Usually once per machine.

# USAGE

```cmake
# CMakeLists.txt

# Uncomment this line if you have downloaded
# release .zip file
# This specifies the path to unpacked folder
# list(APPEND CMAKE_MODULE_PATH "/path/to/GITRepoData-folder/")

find_package(GITRepoData)

# This creates a "gitrepodata" library target in the current scope
# and provides a `gitrepodata.hh` header file
GITRepoData_Target("gitrepodata")
# OR
add_library_gitrepodata("gitrepodata")
# If you use many git submodules with project(...) calls
# you should create a uniquely named-target

# Link library into your application target
target_link_libraries(
	applib
	...
	PUBLIC gitrepodata # Export GITRepoData symbols
)
```

Then use it like so:

```cpp
// main.cc
// Include a header file produced by GITRepoData
#include "./gitrepodata.h"

// For a better compatibility strings
// are exported as char* by default
// See reference how to export std::strings
char*	version	= ${PREIFX}_GIT_VERSION;
char*	version	= GIT_VERSION;
uint 	major	= GIT_VERSION_MAJOR;
uint 	minor	= GIT_VERSION_MINOR;
uint 	patch	= GIT_VERSION_PATCH;
uint	dirty	= GIT_VERSION_DIRTY;

char*	hash	= GIT_COMMIT_HASH;
char*	email	= GIT_COMMIT_DATE;
char*	author	= GIT_COMMIT_AUTHOR;

// See reference for available variables

```

## DOCUMENTATION
1. [add_library_gitrepodata(...)](./cmake/GitRepoData.md)
2. [GITRepoData_Target(...)](./cmake/GitRepoData.md) - A custom library target constructs a header that contains a current git repo commit version, hash, and other data. Only [Semver 2.0.]  compatible versions are parsed.
3. [GITRepoData()](./cmake/git-repodata.md)
3. [GITRepoData( PROJECT_VERSION | &lt;target>)](./cmake/git-repodata.md)
	- Injects version info into either:
		- `PROJECT_VERSION` variable
		- `<target>`'s `VERSION` property.
		- or if no arguments given, global vars:
			- `GIT_VERSION`
			- `GIT_VERSION_MAJOR`
			- `GIT_VERSION_MINOR`
			- `GIT_VERSION_PATCH`
			- `GIT_VERSION_TWEAK`

## EXAMPLE
1. [Example Project](./example/README.md) - Usage example. <!-- TODO: [September 10, 2022] Add usage examples -->

## COMPATIBILITY
* CMake 3.16 >=
* GNU/Linux
 	* Debian based: Ubuntu and derivatives
	 	* clang/clang++ 14.0.0
		* gcc 11.2.0
* Windows 10

# AKNOWLEDGEMENTS
These projects didn't satisfy the said features above but have inspired me to create the new one.

<dl>
	<dt><a href="https://github.com/jahnf/CMake-GitVersion">CMake-GitVersion</a> by @jahnf (Summer 2020)</dt>
	<dd>
	A solid .cmake script, pretty inspirational, but has some drawbacks:
	<ol>
	<li>Respects Semver 2.0 spec only loosely</li>
	<li>Impossible to install system-wide</li>
	<li>Doesn't respect <code>git submodules</code></li>
	<li>Generates redundant <code>ArchiveVersionInfo.cmake</code>, duplicating functionality already provided by CMake by <a href="https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html#generating-a-package-version-file">write_basic_package_version_file()</a> </li>
	<li>Generates extra files, not self-contained</li>
	<li>Configuration-time only (doesn't update version upon rebuild or when git state changes)</li>
	<li>Hard to follow code</li>
	</ol>
	</dd>
	<dt><a href="https://github.com/andrew-hardin/cmake-git-version-tracking">Cmake-git-version-tracking</a> by @andrew-hardin (June 2020
)</dt>
	<dd>Good, lean code; it uses quite clever trick to run the main script obtaining metadata and creates a target to track git repo changes; still has many issues outlined above; more importantly - ignores Semver 2.0.; a bit undocumenented.</dd>
	<dt><a href="https://cmake.org/cmake/help/latest/module/FindBISON.html">FindBISON</a>/<a href="https://cmake.org/cmake/help/latest/module/FindFLEX.html">FindFLEX</a> modules by CMake</dt>
	<dd>Native modules provide built-time targets dependent on <code>custom_command</code>.</dd>
	<dt><a href="https://github.com/nunofachada/cmake-git-semver">GetVersionFromGitTag</a> by @nunofachada (2014)</dt>
	<dd>A small .cmake script that maps Semver 2.0 compatible version into cmake variables.</dd>
	<dt><a href="https://gitlab.com/kicad/code/kicad/-/blob/master/cmake/CreateGitVersionHeader.cmake">CreateGitVersionHeader</a> by @KiCad project (2019)</dt>
	<dd></dd>
	<dt><a href="https://gitlab.com/kicad/code/kicad/-/blob/master/cmake/BuildSteps/WriteVersionHeader.cmake">WriteVersionHeader</a> by @KiCad project (2019)</dt>
	<dd>These two modules served a good example of how to produce *.in files smartly.</dd>
	<dt><a href="https://github.com/ellio167/cmake-and-git-describe">Cmake-and-git-describe</a> by @ellio167 project (2019)</dt>
	<dd><i>See also this discussion: <a href="https://discourse.cmake.org/t/support-for-git-describe-output-in-a-semver-prerelease-string/1714">Support for `git describe` output in a SemVer prerelease string</a></i>. General tips.</dd>


</dl>


[CMake-GitVersion]: https://github.com/jahnf/CMake-GitVersion
[cmake-git-version-tracking]: https://github.com/andrew-hardin/cmake-git-version-tracking
[Semver 2.0.]: https://github.com/semver/semver
[CMake]: https://cmake.org/cmake/help/latest/

## See also
* [CMakePackageConfigHelpers](https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html)

----
> © September 10, 2022

![biteofpie@twitter](https://img.shields.io/badge/-biteofpie@twitter-100000?style=flat-square&logo=twitter)

```
	GITRepoDataTarget - CMake module for embedding GIT data
	See LICENSE file (or comment at the top of the files)
	Copyright (C) 2022- Alex A. Davronov <al.neodim@gmail.com>
	provided along with the source code for additional info
```