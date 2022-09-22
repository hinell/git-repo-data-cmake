#include <iostream>
#include "include/example-git-version.hh"

using std::cout;
int main(int argc, char* argv[], char* env[])
{
	cout
		<< "The following git data is fetched by using cmake:\n"
		<< "\t" << "GIT_HASH\t\t= " 			 << GIT_HASH 					<< "\n\n"
		<< "\t" << "GIT_VERSION\t\t= " 		 << GIT_VERSION 			<< "\n"
		<< "\t" << "GIT_VERSION_MAJOR\t= " << GIT_VERSION_MAJOR << "\n"
		<< "\t" << "GIT_VERSION_MINOR\t= " << GIT_VERSION_MINOR << "\n"
		<< "\t" << "GIT_VERSION_PATCH\t= " << GIT_VERSION_PATCH << "\n"
		<< "\t" << "GIT_VERSION_TWEAK\t= " << GIT_VERSION_TWEAK << "\n";

	return 0;
}
