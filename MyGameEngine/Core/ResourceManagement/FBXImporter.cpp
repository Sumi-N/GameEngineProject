#include "FBXImporter.h"

/* Tab character ("\t") counter */
int numTabs = 0;

bool FBXImporter::Import(const char* filepath)
{
	// Change the following filename to a suitable filename value.
	const char* lFilename = filepath;

	// Initialize the SDK manager. This object handles memory management.
	FbxManager* lSdkManager = FbxManager::Create();

	// Create the IO settings object.
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	// Use the first argument as the filename for the importer.
	if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings()))
	{
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
		exit(-1);
	}

	// Create a new scene so that it can be populated by the imported file.
	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	// The file is imported, so get rid of the importer.
	lImporter->Destroy();

	// Print the nodes of the scene and their attributes recursively.
// Note that we are not printing the root node because it should
// not contain any attributes.
	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode)
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
			PrintNode(lRootNode->GetChild(i));
	}

	// Destroy the SDK manager and all the other objects it was handling.
	lSdkManager->Destroy();

	return true;
}

/**
 * Print a node, its attributes, and all its children recursively.
 */
void FBXImporter::PrintNode(FbxNode* pNode)
{
	PrintTabs();
	const char* nodeName = pNode->GetName();
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	// Print the contents of the node.
	printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
		nodeName,
		translation[0], translation[1], translation[2],
		rotation[0], rotation[1], rotation[2],
		scaling[0], scaling[1], scaling[2]
	);
	numTabs++;

	// Print the node's attributes.
	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
	{
		PrintAttribute(pNode->GetNodeAttributeByIndex(i));
	}

	// Recursively print the children.
	for (int j = 0; j < pNode->GetChildCount(); j++)
		PrintNode(pNode->GetChild(j));

	numTabs--;
	PrintTabs();
	printf("</node>\n");
}

void FBXImporter::ImportNode(FbxNode* pNode)
{

	// Recursively print the children.
	for (int j = 0; j < pNode->GetChildCount(); j++)
		PrintNode(pNode->GetChild(j));
}

/**
 * Print an attribute.
 */
void FBXImporter::PrintAttribute(FbxNodeAttribute* pAttribute)
{
	if (!pAttribute) return;

	FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
	FbxString attrName = pAttribute->GetName();
	PrintTabs();
	// Note: to retrieve the character array of a FbxString, use its Buffer() method.
	printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
}

/**
 * Return a string-based representation based on the attribute type.
 */
FbxString FBXImporter::GetAttributeTypeName(FbxNodeAttribute::EType type)
{
	switch (type)
	{
	case FbxNodeAttribute::eUnknown: return "unidentified";
	case FbxNodeAttribute::eNull: return "null";
	case FbxNodeAttribute::eMarker: return "marker";
	case FbxNodeAttribute::eSkeleton: return "skeleton";
	case FbxNodeAttribute::eMesh: return "mesh";
	case FbxNodeAttribute::eNurbs: return "nurbs";
	case FbxNodeAttribute::ePatch: return "patch";
	case FbxNodeAttribute::eCamera: return "camera";
	case FbxNodeAttribute::eCameraStereo: return "stereo";
	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
	case FbxNodeAttribute::eLight: return "light";
	case FbxNodeAttribute::eOpticalReference: return "optical reference";
	case FbxNodeAttribute::eOpticalMarker: return "marker";
	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
	case FbxNodeAttribute::eBoundary: return "boundary";
	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
	case FbxNodeAttribute::eShape: return "shape";
	case FbxNodeAttribute::eLODGroup: return "lodgroup";
	case FbxNodeAttribute::eSubDiv: return "subdiv";
	default: return "unknown";
	}
}

/**
 * Print the required number of tabs.
 */
void FBXImporter::PrintTabs()
{
	for (int i = 0; i < numTabs; i++)
		printf("\t");
}

////////////////////////////////////////////////////////////////////////////

bool FBXImporter::LoadMesh(const char* filename, std::vector<MeshData>& data, std::vector<int>& index)
{
	// Change the following filename to a suitable filename value.
	const char* lFilename = filename;

	// Initialize the SDK manager. This object handles memory management.
	FbxManager* lSdkManager = FbxManager::Create();

	// Create the IO settings object.
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	// Use the first argument as the filename for the importer.
	if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings()))
	{
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
		exit(-1);
	}

	// Create a new scene so that it can be populated by the imported file.
	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	// The file is imported, so get rid of the importer.
	lImporter->Destroy();

	// Print the nodes of the scene and their attributes recursively.
// Note that we are not printing the root node because it should
// not contain any attributes.
	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode)
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
			ImportMesh(lRootNode->GetChild(i), data, index);
	}

	// Destroy the SDK manager and all the other objects it was handling.
	lSdkManager->Destroy();

	return true;
}

void FBXImporter::ImportMesh(FbxNode* pNode, std::vector<MeshData>& data, std::vector<int>& index)
{
	// Print the node's attributes.
	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
	{
		if (pNode->GetNodeAttributeByIndex(i)->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			// Get the mesh pointer
			FbxMesh* pMesh = (FbxMesh*)pNode->GetNodeAttribute();

			// Get index array and the size
			int  index_count = pMesh->GetPolygonVertexCount();
			int* index_array = pMesh->GetPolygonVertices();

			// Process Index Data
			{
				// The actual number of index is 1.5 time more than GetPolygonVertexCount() since GetPolygonSize() is 4
				// Let's say when the index is {0, 1, 2, 3} then the triangles are {0, 1, 2} and {1, 2, 3}
				int actual_index_count = index_count * 3 / 2;

				// Copy index data to std::vector<int>& index
				for (int i = 0; i < actual_index_count; i++)
				{
					index.push_back(i);
				}
			}

			// Get vertex array
			FbxVector4* vertex_array = pMesh->GetControlPoints();

			// Get normal array
			FbxArray< FbxVector4 > normal_array;
			pMesh->GetPolygonVertexNormals(normal_array);
			
			// Make sure to check the polygon size, otherwise, the conversion below doesn't work correctly.
			// Currently we only support polygon size 4
			for (int i = 0; i < pMesh->GetPolygonCount(); i++)
			{
				if (pMesh->GetPolygonSize(0) != 4)
				{
					DEBUG_PRINT("There is an erroer loading mesh in fbx file");
					DEBUG_ASSERT(false);
				}

				// Process Mesh Data
				{
					MeshData p1, p2, p3, p4, p5, p6;

					p1.vertex.x = vertex_array[index_array[i * 4 + 0]].mData[0];
					p1.vertex.y = vertex_array[index_array[i * 4 + 0]].mData[1];
					p1.vertex.z = vertex_array[index_array[i * 4 + 0]].mData[2];

					p1.normal.x = normal_array[index_array[i * 4 + 0]].mData[0];
					p1.normal.y = normal_array[index_array[i * 4 + 0]].mData[1];
					p1.normal.z = normal_array[index_array[i * 4 + 0]].mData[2];

					p2.vertex.x = vertex_array[index_array[i * 4 + 1]].mData[0];
					p2.vertex.y = vertex_array[index_array[i * 4 + 1]].mData[1];
					p2.vertex.z = vertex_array[index_array[i * 4 + 1]].mData[2];

					p2.normal.x = normal_array[index_array[i * 4 + 1]].mData[0];
					p2.normal.y = normal_array[index_array[i * 4 + 1]].mData[1];
					p2.normal.z = normal_array[index_array[i * 4 + 1]].mData[2];

					p3.vertex.x = vertex_array[index_array[i * 4 + 2]].mData[0];
					p3.vertex.y = vertex_array[index_array[i * 4 + 2]].mData[1];
					p3.vertex.z = vertex_array[index_array[i * 4 + 2]].mData[2];

					p3.normal.x = normal_array[index_array[i * 4 + 2]].mData[0];
					p3.normal.y = normal_array[index_array[i * 4 + 2]].mData[1];
					p3.normal.z = normal_array[index_array[i * 4 + 2]].mData[2];

					p4.vertex.x = vertex_array[index_array[i * 4 + 0]].mData[0];
					p4.vertex.y = vertex_array[index_array[i * 4 + 0]].mData[1];
					p4.vertex.z = vertex_array[index_array[i * 4 + 0]].mData[2];

					p4.normal.x = normal_array[index_array[i * 4 + 0]].mData[0];
					p4.normal.y = normal_array[index_array[i * 4 + 0]].mData[1];
					p4.normal.z = normal_array[index_array[i * 4 + 0]].mData[2];

					p5.vertex.x = vertex_array[index_array[i * 4 + 2]].mData[0];
					p5.vertex.y = vertex_array[index_array[i * 4 + 2]].mData[1];
					p5.vertex.z = vertex_array[index_array[i * 4 + 2]].mData[2];

					p5.normal.x = normal_array[index_array[i * 4 + 2]].mData[0];
					p5.normal.y = normal_array[index_array[i * 4 + 2]].mData[1];
					p5.normal.z = normal_array[index_array[i * 4 + 2]].mData[2];

					p6.vertex.x = vertex_array[index_array[i * 4 + 3]].mData[0];
					p6.vertex.y = vertex_array[index_array[i * 4 + 3]].mData[1];
					p6.vertex.z = vertex_array[index_array[i * 4 + 3]].mData[2];

					p6.normal.x = normal_array[index_array[i * 4 + 3]].mData[0];
					p6.normal.y = normal_array[index_array[i * 4 + 3]].mData[1];
					p6.normal.z = normal_array[index_array[i * 4 + 3]].mData[2];

					// UVs
					if (pMesh->GetUVLayerCount() != 0)
					{
						DEBUG_PRINT("I haven't implement uv layer");
						//FbxStringList UVNames;
						//pMesh->GetUVSetNames(UVNames);
					}

					data.push_back(p1);
					data.push_back(p2);
					data.push_back(p3);
					data.push_back(p4);
					data.push_back(p5);
					data.push_back(p6);
				}
			}

			// Index
			printf("The index is\n");
			for (int i = 0; i < pMesh->GetPolygonVertexCount(); i++)
			{
				printf("%d, ", index_array[i]);
			}
			printf("\n\n");
			
			// Vertices 
			printf("The vertices are\n");
			//Get vertices
			FbxVector4* pVertices = pMesh->GetControlPoints();
			for (int i = 0; i < pMesh->GetControlPointsCount(); i++)
			{
				printf("%f, %f, %f, %f\n", pVertices[i].mData[0], pVertices[i].mData[1], pVertices[i].mData[2], pVertices[i].mData[3]);
			}
			printf("\n");

			// Normals
			printf("The normals are\n");
			FbxArray< FbxVector4 > normals;
			pMesh->GetPolygonVertexNormals(normals);
			for (int i = 0; i < normals.Size(); i++)
			{
				printf("%f, %f, %f\n", normals[i].mData[0], normals[i].mData[1], normals[i].mData[2]);
			}
			printf("\n");

		}
	}

	// Recursively print the children.
	for (int j = 0; j < pNode->GetChildCount(); j++)
	{
		//ImportMesh(pNode->GetChild(j), data, index);
	}
}
