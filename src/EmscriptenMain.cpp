/**
 * TGen - Simple Tangent Generator
 *
 * 2016 by Max Limper, Fraunhofer IGD
 *
 * This code is public domain.
 *
 */

#include <emscripten/bind.h>
#include "tgen.h"

using namespace emscripten;

int add(int a, int b)
{
	return a + b;
}

EMSCRIPTEN_BINDINGS(tgen)
{
		function("computeCornerTSpace", &tgen::computeCornerTSpace);
		function("computeVertexTSpace", &tgen::computeVertexTSpace);
		function("orthogonalizeTSpace", &tgen::orthogonalizeTSpace);
		function("computeTangent4D", &tgen::computeTangent4D);
		function("add", &add);
}