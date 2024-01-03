#include "pch.h"



void main(int argc, char* argv[])
{
	

	::testing::GTEST_FLAG(filter) = "FunctionApproximation.XtimesSinusFunctionG1";
	
	
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}