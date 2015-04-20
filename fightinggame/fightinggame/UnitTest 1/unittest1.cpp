#include "stdafx.h"
#include "CppUnitTest.h"
#include "Renderable.h"
#include "Texture.h"
#include "Shader.h"
#include "Component.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			SPC_Renderable r(new Renderable());
		}

	};
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestMethod2)
		{

		}
	};
}