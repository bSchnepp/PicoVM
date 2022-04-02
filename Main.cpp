#include <iostream>

#include "Binary/Loader.hpp"

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cerr << "Missing filename" << std::endl;
		return -1;
	}

	const char *File = argv[1];
	picovm::Loader::ContentFile Content = picovm::Loader::Load(File);
	picovm::Loader::Unload(Content);


	return 0;
}