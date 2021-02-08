//#include "FBXImporter.h"
//
//#define FBXSDK_SHARED
//
///* Tab character ("\t") counter */
//int numTabs = 0;
//
//bool FBXImporter::Import(const char* filepath)
//{
//	// Change the following filename to a suitable filename value.
//	const char* lFilename = filepath;
//
//	// Initialize the SDK manager. This object handles memory management.
//	FbxManager* lSdkManager = FbxManager::Create();
//
//	// Create the IO settings object.
//	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
//	lSdkManager->SetIOSettings(ios);
//
//	// Create an importer using the SDK manager.
//	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
//
//	// Use the first argument as the filename for the importer.
//	if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings()))
//	{
//		printf("Call to FbxImporter::Initialize() failed.\n");
//		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
//		exit(-1);
//	}
//
//	// Create a new scene so that it can be populated by the imported file.
//	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
//
//	// Import the contents of the file into the scene.
//	lImporter->Import(lScene);
//
//	// The file is imported, so get rid of the importer.
//	lImporter->Destroy();
//
//	//FbxGeometryConverter geometryConverter(lSdkManager);
//	//geometryConverter.SplitMeshesPerMaterial(lScene, true);
//
//	// Print the nodes of the scene and their attributes recursively.
//	// Note that we are not printing the root node because it should
//	// not contain any attributes.
//	FbxNode* lRootNode = lScene->GetRootNode();
//	if (lRootNode)
//	{
//		for (int i = 0; i < lRootNode->GetChildCount(); i++)
//			PrintNode(lRootNode->GetChild(i));
//	}
//
//	// Destroy the SDK manager and all the other objects it was handling.
//	lSdkManager->Destroy();
//
//	return true;
//}
//
///**
// * Print a node, its attributes, and all its children recursively.
// */
//void FBXImporter::PrintNode(FbxNode* pNode)
//{
//	PrintTabs();
//	const char* nodeName = pNode->GetName();
//	FbxDouble3 translation = pNode->LclTranslation.Get();
//	FbxDouble3 rotation = pNode->LclRotation.Get();
//	FbxDouble3 scaling = pNode->LclScaling.Get();
//
//	// Print the contents of the node.
//	printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
//		nodeName,
//		translation[0], translation[1], translation[2],
//		rotation[0], rotation[1], rotation[2],
//		scaling[0], scaling[1], scaling[2]
//	);
//	numTabs++;
//
//	// Print the node's attributes.
//	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
//	{
//		PrintAttribute(pNode->GetNodeAttributeByIndex(i));
//	}
//
//	// Recursively print the children.
//	for (int j = 0; j < pNode->GetChildCount(); j++)
//		PrintNode(pNode->GetChild(j));
//
//	numTabs--;
//	PrintTabs();
//	printf("</node>\n");
//}
//
//void FBXImporter::ImportNode(FbxNode* pNode)
//{
//
//	// Recursively print the children.
//	for (int j = 0; j < pNode->GetChildCount(); j++)
//		PrintNode(pNode->GetChild(j));
//}
//
///**
// * Print an attribute.
// */
//void FBXImporter::PrintAttribute(FbxNodeAttribute* pAttribute)
//{
//	if (!pAttribute) return;
//
//	FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
//	FbxString attrName = pAttribute->GetName();
//	PrintTabs();
//	// Note: to retrieve the character array of a FbxString, use its Buffer() method.
//	printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
//}
//
///**
// * Return a string-based representation based on the attribute type.
// */
//FbxString FBXImporter::GetAttributeTypeName(FbxNodeAttribute::EType type)
//{
//	switch (type)
//	{
//	case FbxNodeAttribute::eUnknown: return "unidentified";
//	case FbxNodeAttribute::eNull: return "null";
//	case FbxNodeAttribute::eMarker: return "marker";
//	case FbxNodeAttribute::eSkeleton: return "skeleton";
//	case FbxNodeAttribute::eMesh: return "mesh";
//	case FbxNodeAttribute::eNurbs: return "nurbs";
//	case FbxNodeAttribute::ePatch: return "patch";
//	case FbxNodeAttribute::eCamera: return "camera";
//	case FbxNodeAttribute::eCameraStereo: return "stereo";
//	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
//	case FbxNodeAttribute::eLight: return "light";
//	case FbxNodeAttribute::eOpticalReference: return "optical reference";
//	case FbxNodeAttribute::eOpticalMarker: return "marker";
//	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
//	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
//	case FbxNodeAttribute::eBoundary: return "boundary";
//	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
//	case FbxNodeAttribute::eShape: return "shape";
//	case FbxNodeAttribute::eLODGroup: return "lodgroup";
//	case FbxNodeAttribute::eSubDiv: return "subdiv";
//	default: return "unknown";
//	}
//}
//
///**
// * Print the required number of tabs.
// */
//void FBXImporter::PrintTabs()
//{
//	for (int i = 0; i < numTabs; i++)
//		printf("\t");
//}
//
//////////////////////////////////////////////////////////////////////////////
//
//bool FBXImporter::LoadMesh(const char* filename, std::vector<MeshData>& data, std::vector<int>& index)
//{
//	// Change the following filename to a suitable filename value.
//	const char* lFilename = filename;
//
//	// Initialize the SDK manager. This object handles memory management.
//	FbxManager* lSdkManager = FbxManager::Create();
//
//	// Create the IO settings object.
//	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
//	lSdkManager->SetIOSettings(ios);
//
//	// Create an importer using the SDK manager.
//	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
//
//	// Use the first argument as the filename for the importer.
//	if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings()))
//	{
//		printf("Call to FbxImporter::Initialize() failed.\n");
//		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
//		exit(-1);
//	}
//
//	// Create a new scene so that it can be populated by the imported file.
//	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
//
//	// Import the contents of the file into the scene.
//	lImporter->Import(lScene);
//
//	// The file is imported, so get rid of the importer.
//	lImporter->Destroy();
//
//	// Triangulate the meshes
//	FbxGeometryConverter geometryConverter(lSdkManager);
//	DEBUG_ASSERT(geometryConverter.Triangulate(lScene, true));
//	geometryConverter.RemoveBadPolygonsFromMeshes(lScene);
//
//	// Split mesh per material
//	geometryConverter.SplitMeshesPerMaterial(lScene, true);
//
//	// Get the root node
//	FbxNode* lRootNode = lScene->GetRootNode();
//	if (lRootNode)
//	{
//		for (int i = 0; i < lRootNode->GetChildCount(); i++)
//			ImportMesh(lRootNode->GetChild(i), data, index, Mat4f());
//	}
//
//	{
//		// Get mesh in the scene
//		//int meshCount = lScene->GetSrcObjectCount<FbxMesh>();
//
//		//for (int i = 0; i < meshCount; ++i)
//		{
//			//auto* mesh = lScene->GetSrcObject<FbxMesh>(i);
//			//std::string name = mesh->GetName();
//
//		}
//	}
//
//	{
//		// Get materials in the scene
//		auto materialCount = lScene->GetMaterialCount();
//
//		for (int i = 0; i < materialCount; ++i)
//		{
//			FbxSurfaceMaterial* material = lScene->GetMaterial(i);
//			std::string name = material->GetName();
//			//printf(name.c_str());
//			//printf("\n");
//		}
//	}
//
//	// Destroy the SDK manager and all the other objects it was handling.
//	lSdkManager->Destroy();
//
//	return true;
//}
//
//bool FBXImporter::ImportMesh(FbxNode* pNode, std::vector<MeshData>& data, std::vector<int>& index, Mat4f model_matrix)
//{
//	// Get translation rotation scale
//	Vec3f translation((float)pNode->LclTranslation.Get().mData[0], (float)pNode->LclTranslation.Get().mData[1], (float)pNode->LclTranslation.Get().mData[2]);
//	Vec3f rotation((float)pNode->LclRotation.Get().mData[0], (float)pNode->LclRotation.Get().mData[1], (float)pNode->LclRotation.Get().mData[2]);
//	Vec3f scaling((float)pNode->LclScaling.Get().mData[0], (float)pNode->LclScaling.Get().mData[1], (float)pNode->LclScaling.Get().mData[2]);
//
//	// Make a model matrix
//	Mat4f translation_mat = Mat4f::Translate(translation);
//	Mat4f rotation_mat_x = Mat4f::Roll(rotation.x);
//	Mat4f rotation_mat_y = Mat4f::Pitch(rotation.y);
//	Mat4f rotation_mat_z = Mat4f::Yaw(rotation.z);
//	Mat4f scaling_mat = Mat4f::Scale(scaling);
//	model_matrix = translation_mat * rotation_mat_z * rotation_mat_y * rotation_mat_x * scaling_mat * model_matrix;
//	Mat4f model_inverse_transpose_matrix = Mat4f::Transpose(Mat4f::Inverse(model_matrix));
//
//	FbxDouble3 geo_translation = pNode->GeometricTranslation.Get();
//	FbxDouble3 geo_rotation = pNode->GeometricRotation.Get();
//	FbxDouble3 get_scaling = pNode->GeometricScaling.Get();
//
//	// Search the node's attributes.
//	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
//	{
//		if (pNode->GetNodeAttributeByIndex(i)->GetAttributeType() == FbxNodeAttribute::eMesh)
//		{
//			// Get the mesh pointer
//			FbxMesh* pMesh = (FbxMesh*)pNode->GetNodeAttributeByIndex(i);
//
//			// Get index array and the size
//			int  index_count = pMesh->GetPolygonVertexCount();
//			int* index_array = pMesh->GetPolygonVertices();
//
//			// Get vertex array
//			FbxVector4* vertex_array = pMesh->GetControlPoints();
//
//			// Get normal array
//			FbxArray< FbxVector4 > normal_array;
//			pMesh->GetPolygonVertexNormals(normal_array);
//
//			// Get UV layer names
//			FbxStringList uvsetName;
//			pMesh->GetUVSetNames(uvsetName);
//
//			// Current index count
//			int n = 0 + (int)index.size();
//			
//			// The reason we can assume each polygon has 3 vertices is because we called triangulate function before
//			for (int j = 0; j < pMesh->GetPolygonCount(); j++)
//			{
//				index.push_back(n + 3 * j + 0);
//				index.push_back(n + 3 * j + 1);
//				index.push_back(n + 3 * j + 2);
//
//				MeshData p1, p2, p3;
//
//				p1.vertex.x = (float)vertex_array[index_array[3 * j + 0]].mData[0];
//				p1.vertex.y = (float)vertex_array[index_array[3 * j + 0]].mData[1];
//				p1.vertex.z = (float)vertex_array[index_array[3 * j + 0]].mData[2];
//							
//				p2.vertex.x = (float)vertex_array[index_array[3 * j + 1]].mData[0];
//				p2.vertex.y = (float)vertex_array[index_array[3 * j + 1]].mData[1];
//				p2.vertex.z = (float)vertex_array[index_array[3 * j + 1]].mData[2];
//					
//				p3.vertex.x = (float)vertex_array[index_array[3 * j + 2]].mData[0];
//				p3.vertex.y = (float)vertex_array[index_array[3 * j + 2]].mData[1];
//				p3.vertex.z = (float)vertex_array[index_array[3 * j + 2]].mData[2];
//
//				p1.normal.x = (float)normal_array[3 * j + 0].mData[0];
//				p1.normal.y = (float)normal_array[3 * j + 0].mData[1];
//				p1.normal.z = (float)normal_array[3 * j + 0].mData[2];
//								   
//				p2.normal.x = (float)normal_array[3 * j + 1].mData[0];
//				p2.normal.y = (float)normal_array[3 * j + 1].mData[1];
//				p2.normal.z = (float)normal_array[3 * j + 1].mData[2];
//							
//				p3.normal.x = (float)normal_array[3 * j + 2].mData[0];
//				p3.normal.y = (float)normal_array[3 * j + 2].mData[1];
//				p3.normal.z = (float)normal_array[3 * j + 2].mData[2];
//
//				p1.vertex = model_matrix * p1.vertex;
//				p2.vertex = model_matrix * p2.vertex;
//				p3.vertex = model_matrix * p3.vertex;
//
//				p1.normal = model_inverse_transpose_matrix * p1.normal;
//				p2.normal = model_inverse_transpose_matrix * p2.normal;
//				p3.normal = model_inverse_transpose_matrix * p3.normal;
//
//				// Get the first UV sets
//				if (uvsetName.GetCount() > 0)
//				{
//					FbxVector2 uv1, uv2, uv3;
//					bool flag1, flag2, flag3;
//
//					pMesh->GetPolygonVertexUV(j, 0, uvsetName.GetStringAt(0), uv1, flag1);
//					pMesh->GetPolygonVertexUV(j, 1, uvsetName.GetStringAt(0), uv2, flag2);
//					pMesh->GetPolygonVertexUV(j, 2, uvsetName.GetStringAt(0), uv3, flag3);
//
//					p1.uv.x = (float)uv1.mData[0];
//					p1.uv.y = (float)uv1.mData[1];
//							  
//					p2.uv.x = (float)uv2.mData[0];
//					p2.uv.y = (float)uv2.mData[1];
//							  
//					p2.uv.x = (float)uv3.mData[0];
//					p2.uv.y = (float)uv3.mData[1];
//				}
//
//				data.push_back(p1);
//				data.push_back(p2);
//				data.push_back(p3);
//			}
//
//			//// Index
//			//printf("The index is\n");
//			//for (int i = 0; i < pMesh->GetPolygonVertexCount(); i++)
//			//{
//			//	printf("%d, ", index_array[i]);
//			//}
//			//printf("\n\n");
//			//
//			//// Vertices 
//			//printf("The vertices are\n");
//			////Get vertices
//			//FbxVector4* pVertices = pMesh->GetControlPoints();
//			//for (int i = 0; i < pMesh->GetControlPointsCount(); i++)
//			//{
//			//	printf("%f, %f, %f, %f\n", pVertices[i].mData[0], pVertices[i].mData[1], pVertices[i].mData[2], pVertices[i].mData[3]);
//			//}
//			//printf("\n");
//
//			//// Normals
//			//printf("The normals are\n");
//			//FbxArray< FbxVector4 > normals;
//			//pMesh->GetPolygonVertexNormals(normals);
//			//for (int i = 0; i < normals.Size(); i++)
//			//{
//			//	printf("%f, %f, %f\n", normals[i].mData[0], normals[i].mData[1], normals[i].mData[2]);
//			//}
//			//printf("\n");
//
//		}
//	}
//
//	// Recursively print the children.
//	for (int j = 0; j < pNode->GetChildCount(); j++)
//	{
//		//ImportMesh(pNode->GetChild(j), data, index, model_matrix);
//	}
//
//	return true;
//}
//
//bool FBXImporter::ImportMaterial(FbxSurfaceMaterial* material, MaterialData& mat)
//{
//	//Vec3f ambient(0, 0, 0);
//	//Vec3f diffuse(1, 1, 1);
//	//Vec3f emissive(0, 0, 0);
//	//Vec3f specular(0, 0, 0);
//	//float shininess = 80.0;
//
//	//// Get material information
//	//{
//	//	FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
//	//	if (prop.IsValid())
//	//	{
//	//		const auto& color = prop.Get<FbxDouble3>();
//	//		ambient = Vec3f(color[0], color[1], color[2]);
//	//	}
//	//}
//	//{
//	//	FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
//	//	if (prop.IsValid())
//	//	{
//	//		const auto& color = prop.Get<FbxDouble3>();
//	//		diffuse = Vec3f(color[0], color[1], color[2]);
//	//	}
//	//}
//	//{
//	//	FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sEmissive);
//	//	if (prop.IsValid())
//	//	{
//	//		const auto& color = prop.Get<FbxDouble3>();
//	//		emissive = Vec3f(color[0], color[1], color[2]);
//	//	}
//	//}
//	//{
//	//	FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
//	//	if (prop.IsValid())
//	//	{
//	//		const auto& color = prop.Get<FbxDouble3>();
//	//		specular = Vec3f(color[0], color[1], color[2]);
//	//	}
//	//}
//	//{
//	//	FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sShininess);
//	//	if (prop.IsValid())
//	//	{
//	//		shininess = prop.Get<FbxDouble>();
//	//	}
//	//}
//
//	//mat.ambient   = ambient;
//	//mat.diffuse   = diffuse;
//	//mat.emissive = emissive;
//	//mat.specular  = specular;
//	//mat.shininess = shininess;
//
//	//{
//	//	// Get the texture that is attached to diffuse
//	//	FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
//	//	if (prop.GetSrcObjectCount<FbxFileTexture>() > 0)
//	//	{
//	//		// Get the first texture only
//	//		FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(0);
//	//		if (texture)
//	//		{
//	//			// Get the file path
//	//			const char * name = (const char*)(FbxPathUtils::GetFileName(texture->GetFileName()));
//
//	//			//// Read the texture and flip it
//	//			// Had to implement a loading function here
//	//		}
//	//	}
//	//}
//
//	return true;
//}
//
//
//void FBXImporter::ProcessSkeletonHierarchy(FbxNode* inRootNode, Skeleton skeleton)
//{
//
//	for (int childIndex = 0; childIndex < inRootNode->GetChildCount(); ++childIndex)
//	{
//		FbxNode* currNode = inRootNode->GetChild(childIndex);
//		ProcessSkeletonHierarchyRecursively(currNode, 0, 0, -1, skeleton);
//	}
//}
//
//void FBXImporter::ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex, Skeleton skeleton)
//{
//	if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
//	{
//		Joint currJoint;
//		currJoint.parent_index = inParentIndex;
//		currJoint.name = inNode->GetName();
//		skeleton.joints.push_back(currJoint);
//	}
//	for (int i = 0; i < inNode->GetChildCount(); i++)
//	{
//		ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), inDepth + 1, skeleton.joints.size(), myIndex, skeleton);
//	}
//}
//
//void FBXImporter::ProcessJointsAndAnimations(FbxNode* inNode, Skeleton skeleton)
//{
//	FbxMesh* currMesh = inNode->GetMesh();
//	unsigned int numOfDeformers = currMesh->GetDeformerCount();
//	// This geometry transform is something I cannot understand
//	// I think it is from MotionBuilder
//	// If you are using Maya for your models, 99% this is just an
//	// identity matrix
//	// But I am taking it into account anyways......
//	FbxAMatrix geometryTransform = GetGeometryTransformation(inNode);
//
//	// A deformer is a FBX thing, which contains some clusters
//	// A cluster contains a link, which is basically a joint
//	// Normally, there is only one deformer in a mesh
//	for (unsigned int deformerIndex = 0; deformerIndex < numOfDeformers; ++deformerIndex)
//	{
//		// There are many types of deformers in Maya,
//		// We are using only skins, so we see if this is a skin
//		FbxSkin* currSkin = reinterpret_cast<FbxSkin*>(currMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));
//		if (!currSkin)
//		{
//			continue;
//		}
//
//		unsigned int numOfClusters = currSkin->GetClusterCount();
//		for (unsigned int clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
//		{
//			FbxCluster* currCluster = currSkin->GetCluster(clusterIndex);
//			std::string currJointName = currCluster->GetLink()->GetName();
//			unsigned int currJointIndex = FindJointIndexUsingName(currJointName.c_str(), skeleton);
//			FbxAMatrix transformMatrix;
//			FbxAMatrix transformLinkMatrix;
//			FbxAMatrix globalBindposeInverseMatrix;
//
//			currCluster->GetTransformMatrix(transformMatrix);	// The transformation of the mesh at binding time
//			currCluster->GetTransformLinkMatrix(transformLinkMatrix);	// The transformation of the cluster(joint) at binding time from joint space to world space
//			globalBindposeInverseMatrix = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;
//
//			// Update the information in mSkeleton 
//			skeleton.joints[currJointIndex].inversed = convertFBXMatrix(globalBindposeInverseMatrix);
//			//skeleton.joints[currJointIndex].mNode = currCluster->GetLink();
//
//			// Associate each joint with the control points it affects
//			unsigned int numOfIndices = currCluster->GetControlPointIndicesCount();
//			for (unsigned int i = 0; i < numOfIndices; ++i)
//			{
//				BlendingWeight currBlendingIndexWeightPair;
//				currBlendingIndexWeightPair.index = currJointIndex;
//				currBlendingIndexWeightPair.weight = currCluster->GetControlPointWeights()[i];
//				//mControlPoints[currCluster->GetControlPointIndices()[i]]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
//			}
//
//			// Get animation information
//			// Now only supports one take
//			//FbxAnimStack* currAnimStack = mFBXScene->GetSrcObject<FbxAnimStack>(0);
//			//FbxString animStackName = currAnimStack->GetName();
//			//mAnimationName = animStackName.Buffer();
//			//FbxTakeInfo* takeInfo = mFBXScene->GetTakeInfo(animStackName);
//			//FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
//			//FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
//			//mAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
//			//Keyframe** currAnim = &mSkeleton.mJoints[currJointIndex].mAnimation;
//
//			//for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
//			//{
//			//	FbxTime currTime;
//			//	currTime.SetFrame(i, FbxTime::eFrames24);
//			//	*currAnim = new Keyframe();
//			//	(*currAnim)->mFrameNum = i;
//			//	FbxAMatrix currentTransformOffset = inNode->EvaluateGlobalTransform(currTime) * geometryTransform;
//			//	(*currAnim)->mGlobalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(currTime);
//			//	currAnim = &((*currAnim)->mNext);
//			//}
//		}
//	}
//
//	// Some of the control points only have less than 4 joints
//	// affecting them.
//	// For a normal renderer, there are usually 4 joints
//	// I am adding more dummy joints if there isn't enough
//	//BlendingIndexWeightPair currBlendingIndexWeightPair;
//	//currBlendingIndexWeightPair.mBlendingIndex = 0;
//	//currBlendingIndexWeightPair.mBlendingWeight = 0;
//	//for (auto itr = mControlPoints.begin(); itr != mControlPoints.end(); ++itr)
//	//{
//	//	for (unsigned int i = itr->second->mBlendingInfo.size(); i <= 4; ++i)
//	//	{
//	//		itr->second->mBlendingInfo.push_back(currBlendingIndexWeightPair);
//	//	}
//	//}
//}
//
//FbxAMatrix FBXImporter::GetGeometryTransformation(FbxNode* inNode)
//{
//	if (!inNode)
//	{
//		throw std::exception("Null for mesh geometry");
//	}
//
//	const FbxVector4 lT = inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
//	const FbxVector4 lR = inNode->GetGeometricRotation(FbxNode::eSourcePivot);
//	const FbxVector4 lS = inNode->GetGeometricScaling(FbxNode::eSourcePivot);
//
//	return FbxAMatrix(lT, lR, lS);
//}
//
//int FBXImporter::FindJointIndexUsingName(const char* name, Skeleton skeleton)
//{
//	for (int i = 0; skeleton.joints.size(); i++)
//	{
//		if (skeleton.joints[i].name == name)
//		{
//			return i;
//		}
//	}
//	return -1;
//}
//
//Mat4f FBXImporter::convertFBXMatrix(FbxAMatrix)
//{
//	return Mat4f();
//}
//
