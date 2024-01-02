#include "pch.h"

#include"MultiPatch.h"
#include"WriteObj.h"
#include "MeshConvert.h"
#include "ReadObj.h"

TEST(HEdgeBased_ControlVectorAccess, ChangeOfCoordinates)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	mltp.CreateControleVector();

	for (int face=1;face <= mltp.Splines.size();face++)
	{
		
		int he = mltp.HalfEdge_Mesh.faces[face - 1].HEdge;
		
		//second Hedge
		int NxtHEdge_index = mltp.HalfEdge_Mesh.HalfeEdges[he - 1].next;
		HEdge NxtHedge = mltp.HalfEdge_Mesh.HalfeEdges[NxtHEdge_index - 1];
		for (int iIndex = 0;iIndex< mltp.Splines[face - 1].tensor2[0].size();iIndex++)
			for(int jIndex = 1;jIndex< mltp.Splines[face - 1].tensor2.size();jIndex++)
		{
			
			point pt = mltp.AccessControleVector(NxtHedge, iIndex, jIndex);
			int FirstAxeSize = mltp.Splines[face - 1].tensor2.size();
			point pt2 = mltp.
				Splines[face - 1].
				tensor2[FirstAxeSize - jIndex - 1]
				[iIndex];

			EXPECT_EQ(pt.getNorm(), pt2.getNorm());
		}

		//Third HEdge
		NxtHEdge_index = mltp.HalfEdge_Mesh.HalfeEdges[NxtHEdge_index - 1].next;
		NxtHedge = mltp.HalfEdge_Mesh.HalfeEdges[NxtHEdge_index - 1];
		for (int iIndex = 0;iIndex < mltp.Splines[face - 1].tensor2[0].size();iIndex++)
			for (int jIndex = 1;jIndex < mltp.Splines[face - 1].tensor2.size();jIndex++)
			{

				point pt = mltp.AccessControleVector(NxtHedge, iIndex, jIndex);
				int FirstAxeSize = mltp.Splines[face - 1].tensor2.size();
				int SecondAxeSize = mltp.Splines[face - 1].tensor2[0].size();
				point pt2 = mltp.
					Splines[face - 1].
					tensor2[FirstAxeSize - iIndex - 1]
					[SecondAxeSize - jIndex - 1];

				EXPECT_EQ(pt.getNorm(), pt2.getNorm());
			}

		//Fourth HEdge
		NxtHEdge_index = mltp.HalfEdge_Mesh.HalfeEdges[NxtHEdge_index - 1].next;
		NxtHedge = mltp.HalfEdge_Mesh.HalfeEdges[NxtHEdge_index - 1];
		for (int iIndex = 0;iIndex < mltp.Splines[face - 1].tensor2[0].size();iIndex++)
			for (int jIndex = 1;jIndex < mltp.Splines[face - 1].tensor2.size();jIndex++)
			{

				point pt = mltp.AccessControleVector(NxtHedge, iIndex, jIndex);
				int FirstAxeSize = mltp.Splines[face - 1].tensor2.size();
				int SecondAxeSize = mltp.Splines[face - 1].tensor2[0].size();
				point pt2 = mltp.
					Splines[face - 1].
					tensor2[jIndex]
					[SecondAxeSize - iIndex - 1];

				EXPECT_EQ(pt.getNorm(), pt2.getNorm());
			}
	}
}