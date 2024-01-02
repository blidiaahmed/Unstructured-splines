#include "pch.h"



void main(int argc, char* argv[])
{
	

	::testing::GTEST_FLAG(filter) = "MultipatcheDerivation.EdgeReferencedDerivationAxe2";
	
	
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}