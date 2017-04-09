#include "tgen.h"
#include "tgen_debug.h"
#include <iostream>

int main(int argc, char ** argv)
{
	if(argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " input.gltf output.gltf\n";
		std::exit(EXIT_FAILURE);
	}
}