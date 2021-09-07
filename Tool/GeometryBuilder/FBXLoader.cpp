#include <fbxsdk.h>

#include <Math/Util.h>
#include <Math/Matrix.h>

#include "FBXLoader.h"

namespace FBXLoader
{
	namespace
	{
		FbxManager* lSdkManager;
		FbxScene* lScene;
		FbxNode* lRootNode;
	}

	namespace
	{		
		int numTabs = 0;

		struct BlendingWeight
		{
			int   index;
			float weight;
		};

		std::multimap<int, BlendingWeight> WeightMap;
	}

	bool Init(const char* i_filepath)
	{
		// Change the following filename to a suitable filename value.
		const char* lFilename = i_filepath;

		// Initialize the SDK manager. This object handles memory management.
		lSdkManager = FbxManager::Create();

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
		lScene = FbxScene::Create(lSdkManager, "myScene");

		// Import the contents of the file into the scene.
		lImporter->Import(lScene);

		// The file is imported, so get rid of the importer.
		lImporter->Destroy();


		lRootNode = lScene->GetRootNode();

		FbxGeometryConverter geometryConverter(lSdkManager);
		geometryConverter.Triangulate(lScene, true);
		//geometryConverter.SplitMeshesPerMaterial(Importer::lScene, true);

		return true;
	}

	bool LoadMesh(Array<Resource::MeshPoint>& mesh, Array<int>& index)
	{
		//Get mesh in the scene
		int meshCount = lScene->GetSrcObjectCount<FbxMesh>();

		for (int i = 0; i < meshCount; ++i)
		{
			FbxMesh* pMesh = lScene->GetSrcObject<FbxMesh>(i);

			FbxNode* pNode = pMesh->GetNode();
			FbxAMatrix geometryTransform = GetGeometryTransformation(pNode);

			Mat4f model_matrix;

			// Get translation rotation scale
			Vec3f translation((float)pNode->LclTranslation.Get().mData[0], (float)pNode->LclTranslation.Get().mData[1], (float)pNode->LclTranslation.Get().mData[2]);
			Vec3f rotation((float)pNode->LclRotation.Get().mData[0], (float)pNode->LclRotation.Get().mData[1], (float)pNode->LclRotation.Get().mData[2]);
			Vec3f scaling((float)pNode->LclScaling.Get().mData[0], (float)pNode->LclScaling.Get().mData[1], (float)pNode->LclScaling.Get().mData[2]);

			// Make a model matrix
			Mat4f translation_mat = Mat4f::Translate(translation);
			Mat4f rotation_mat = Mat4f::EulerAngleZYX(Math::DegreeToRadian(rotation.x), Math::DegreeToRadian(rotation.y), Math::DegreeToRadian(rotation.z));
			Mat4f scaling_mat = Mat4f::Scale(scaling);
			model_matrix = translation_mat * rotation_mat * scaling_mat * model_matrix;
			Mat4f model_inverse_transpose_matrix = Mat4f::Transpose(Mat4f::Inverse(model_matrix));

			// Get index array
			int* index_array = pMesh->GetPolygonVertices();

			// Get vertex array
			FbxVector4* vertex_array = pMesh->GetControlPoints();

			// Get normal array
			FbxArray< FbxVector4 > normal_array;
			pMesh->GetPolygonVertexNormals(normal_array);

			// Get UV layer names
			FbxStringList uvsetName;
			pMesh->GetUVSetNames(uvsetName);

			// Store skin data
			unsigned int numOfDeformers = pMesh->GetDeformerCount();

			// A deformer is a FBX thing, which contains some clusters
			// A cluster contains a link, which is basically a joint
			// Normally, there is only one deformer in a mesh
			for (unsigned int deformerIndex = 0; deformerIndex < numOfDeformers; ++deformerIndex)
			{
				// There are many types of deformers in Maya,
				// We are using only skins, so we see if this is a skin
				FbxSkin* currSkin = reinterpret_cast<FbxSkin*>(pMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));
				if (!currSkin)
				{
					continue;
				}
			}

			// Current index count
			int n = 0 + (int)index.Size();

			// The reason we can assume each polygon has 3 vertices is because we called triangulate function before
			int polygonIndexCount = pMesh->GetPolygonCount();
			for (int j = 0; j < polygonIndexCount; j++)
			{
				index.PushBack(n + 3 * j + 0);
				index.PushBack(n + 3 * j + 1);
				index.PushBack(n + 3 * j + 2);

				Resource::MeshPoint p1, p2, p3;

				p1.vertex.x = (float)vertex_array[index_array[3 * j + 0]].mData[0];
				p1.vertex.y = (float)vertex_array[index_array[3 * j + 0]].mData[1];
				p1.vertex.z = (float)vertex_array[index_array[3 * j + 0]].mData[2];

				p2.vertex.x = (float)vertex_array[index_array[3 * j + 1]].mData[0];
				p2.vertex.y = (float)vertex_array[index_array[3 * j + 1]].mData[1];
				p2.vertex.z = (float)vertex_array[index_array[3 * j + 1]].mData[2];

				p3.vertex.x = (float)vertex_array[index_array[3 * j + 2]].mData[0];
				p3.vertex.y = (float)vertex_array[index_array[3 * j + 2]].mData[1];
				p3.vertex.z = (float)vertex_array[index_array[3 * j + 2]].mData[2];

				p1.normal.x = (float)normal_array[3 * j + 0].mData[0];
				p1.normal.y = (float)normal_array[3 * j + 0].mData[1];
				p1.normal.z = (float)normal_array[3 * j + 0].mData[2];

				p2.normal.x = (float)normal_array[3 * j + 1].mData[0];
				p2.normal.y = (float)normal_array[3 * j + 1].mData[1];
				p2.normal.z = (float)normal_array[3 * j + 1].mData[2];

				p3.normal.x = (float)normal_array[3 * j + 2].mData[0];
				p3.normal.y = (float)normal_array[3 * j + 2].mData[1];
				p3.normal.z = (float)normal_array[3 * j + 2].mData[2];

				p1.vertex = Vec3f(model_matrix * Vec4f(p1.vertex.x, p1.vertex.y, p1.vertex.z, 1.0));
				p2.vertex = Vec3f(model_matrix * Vec4f(p2.vertex.x, p2.vertex.y, p2.vertex.z, 1.0));
				p3.vertex = Vec3f(model_matrix * Vec4f(p3.vertex.x, p3.vertex.y, p3.vertex.z, 1.0));

				p1.normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p1.normal.x, p1.normal.y, p1.normal.z, 1.0));
				p2.normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p2.normal.x, p2.normal.y, p2.normal.z, 1.0));
				p3.normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p3.normal.x, p3.normal.y, p3.normal.z, 1.0));

				// Get the first UV sets
				if (uvsetName.GetCount() > 0)
				{
					FbxVector2 uv1, uv2, uv3;
					bool flag1, flag2, flag3;

					pMesh->GetPolygonVertexUV(j, 0, uvsetName.GetStringAt(0), uv1, flag1);
					pMesh->GetPolygonVertexUV(j, 1, uvsetName.GetStringAt(0), uv2, flag2);
					pMesh->GetPolygonVertexUV(j, 2, uvsetName.GetStringAt(0), uv3, flag3);

					p1.uv.x = (float)uv1.mData[0];
					p1.uv.y = (float)uv1.mData[1];

					p2.uv.x = (float)uv2.mData[0];
					p2.uv.y = (float)uv2.mData[1];

					p3.uv.x = (float)uv3.mData[0];
					p3.uv.y = (float)uv3.mData[1];
				}

				mesh.PushBack(p1);
				mesh.PushBack(p2);
				mesh.PushBack(p3);
			}
		}

		return true;
	}

	bool LoadSkeletonMesh(Array<Resource::SkeletonMeshPoint>& mesh, Array<int>& index, const std::map<String, int>& i_joint_map)
	{
		// Get mesh in the scene
		int meshCount = lScene->GetSrcObjectCount<FbxMesh>();

		for (int i = 0; i < meshCount; ++i)
		{
			FbxMesh* pMesh = lScene->GetSrcObject<FbxMesh>(i);

			FbxNode* pNode = pMesh->GetNode();
			FbxAMatrix geometryTransform = GetGeometryTransformation(pNode);

			Mat4f model_matrix;

			// Get translation rotation scale
			Vec3f translation((float)pNode->LclTranslation.Get().mData[0], (float)pNode->LclTranslation.Get().mData[1], (float)pNode->LclTranslation.Get().mData[2]);
			Vec3f rotation((float)pNode->LclRotation.Get().mData[0], (float)pNode->LclRotation.Get().mData[1], (float)pNode->LclRotation.Get().mData[2]);
			Vec3f scaling((float)pNode->LclScaling.Get().mData[0], (float)pNode->LclScaling.Get().mData[1], (float)pNode->LclScaling.Get().mData[2]);

			// Make a model matrix
			Mat4f translation_mat = Mat4f::Translate(translation);
			Mat4f rotation_mat = Mat4f::EulerAngleZYX(Math::DegreeToRadian(rotation.x), Math::DegreeToRadian(rotation.y), Math::DegreeToRadian(rotation.z));
			Mat4f scaling_mat = Mat4f::Scale(scaling);
			model_matrix = translation_mat * rotation_mat * scaling_mat * model_matrix;
			Mat4f model_inverse_transpose_matrix = Mat4f::Transpose(Mat4f::Inverse(model_matrix));

			// Get index array
			int* index_array = pMesh->GetPolygonVertices();

			// Get vertex array
			FbxVector4* vertex_array = pMesh->GetControlPoints();

			// Get normal array
			FbxArray< FbxVector4 > normal_array;
			pMesh->GetPolygonVertexNormals(normal_array);

			// Get UV layer names
			FbxStringList uvsetName;
			pMesh->GetUVSetNames(uvsetName);

			// Store skin data
			unsigned int numOfDeformers = pMesh->GetDeformerCount();

			// A deformer is a FBX thing, which contains some clusters
			// A cluster contains a link, which is basically a joint
			// Normally, there is only one deformer in a mesh
			for (unsigned int deformerIndex = 0; deformerIndex < numOfDeformers; ++deformerIndex)
			{
				// There are many types of deformers in Maya,
				// We are using only skins, so we see if this is a skin
				FbxSkin* currSkin = reinterpret_cast<FbxSkin*>(pMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));
				if (!currSkin)
				{
					continue;
				}

				unsigned int numOfClusters = currSkin->GetClusterCount();
				for (unsigned int clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
				{
					FbxCluster* currCluster = currSkin->GetCluster(clusterIndex);
					std::string currJointName = currCluster->GetLink()->GetName();
					int currJointIndex = FindJointIndexUsingName(currJointName, i_joint_map);

					//Associate each joint with the control points it affects
					unsigned int numOfIndices = currCluster->GetControlPointIndicesCount();
					for (unsigned int j = 0; j < numOfIndices; ++j)
					{
						BlendingWeight currBlending;
						currBlending.index = currJointIndex;
						currBlending.weight = currCluster->GetControlPointWeights()[j];

						int controlpointindex = currCluster->GetControlPointIndices()[j];

						WeightMap.insert(std::make_pair(controlpointindex, currBlending));
					}
				}
			}

			// Current index count
			int n = 0 + (int)index.Size();

			// The reason we can assume each polygon has 3 vertices is because we called triangulate function before
			int polygonIndexCount = pMesh->GetPolygonCount();
			for (int j = 0; j < polygonIndexCount; j++)
			{
				index.PushBack(n + 3 * j + 0);
				index.PushBack(n + 3 * j + 1);
				index.PushBack(n + 3 * j + 2);

				Resource::SkeletonMeshPoint p1, p2, p3;

				p1.vertex.x = (float)vertex_array[index_array[3 * j + 0]].mData[0];
				p1.vertex.y = (float)vertex_array[index_array[3 * j + 0]].mData[1];
				p1.vertex.z = (float)vertex_array[index_array[3 * j + 0]].mData[2];

				p2.vertex.x = (float)vertex_array[index_array[3 * j + 1]].mData[0];
				p2.vertex.y = (float)vertex_array[index_array[3 * j + 1]].mData[1];
				p2.vertex.z = (float)vertex_array[index_array[3 * j + 1]].mData[2];

				p3.vertex.x = (float)vertex_array[index_array[3 * j + 2]].mData[0];
				p3.vertex.y = (float)vertex_array[index_array[3 * j + 2]].mData[1];
				p3.vertex.z = (float)vertex_array[index_array[3 * j + 2]].mData[2];

				p1.normal.x = (float)normal_array[3 * j + 0].mData[0];
				p1.normal.y = (float)normal_array[3 * j + 0].mData[1];
				p1.normal.z = (float)normal_array[3 * j + 0].mData[2];

				p2.normal.x = (float)normal_array[3 * j + 1].mData[0];
				p2.normal.y = (float)normal_array[3 * j + 1].mData[1];
				p2.normal.z = (float)normal_array[3 * j + 1].mData[2];

				p3.normal.x = (float)normal_array[3 * j + 2].mData[0];
				p3.normal.y = (float)normal_array[3 * j + 2].mData[1];
				p3.normal.z = (float)normal_array[3 * j + 2].mData[2];

				p1.vertex = Vec3f(model_matrix * Vec4f(p1.vertex.x, p1.vertex.y, p1.vertex.z, 1.0));
				p2.vertex = Vec3f(model_matrix * Vec4f(p2.vertex.x, p2.vertex.y, p2.vertex.z, 1.0));
				p3.vertex = Vec3f(model_matrix * Vec4f(p3.vertex.x, p3.vertex.y, p3.vertex.z, 1.0));

				p1.normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p1.normal.x, p1.normal.y, p1.normal.z, 1.0));
				p2.normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p2.normal.x, p2.normal.y, p2.normal.z, 1.0));
				p3.normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p3.normal.x, p3.normal.y, p3.normal.z, 1.0));

				// Get the first UV sets
				if (uvsetName.GetCount() > 0)
				{
					FbxVector2 uv1, uv2, uv3;
					bool flag1, flag2, flag3;

					pMesh->GetPolygonVertexUV(j, 0, uvsetName.GetStringAt(0), uv1, flag1);
					pMesh->GetPolygonVertexUV(j, 1, uvsetName.GetStringAt(0), uv2, flag2);
					pMesh->GetPolygonVertexUV(j, 2, uvsetName.GetStringAt(0), uv3, flag3);

					p1.uv.x = (float)uv1.mData[0];
					p1.uv.y = (float)uv1.mData[1];

					p2.uv.x = (float)uv2.mData[0];
					p2.uv.y = (float)uv2.mData[1];

					p3.uv.x = (float)uv3.mData[0];
					p3.uv.y = (float)uv3.mData[1];
				}

				// Get skin info from WidhtMap
				typedef std::multimap<int, BlendingWeight>::iterator iter;
				int this_index = index_array[3 * j + 0];
				for (std::pair<iter, iter> range(WeightMap.equal_range(this_index)); range.first != range.second; ++range.first)
				{
					if (p1.index.x == NUM_MAX_BONES - 1)
					{
						p1.index.x = range.first->second.index;
						p1.weight.x = range.first->second.weight;
					}
					else if (p1.index.y == NUM_MAX_BONES - 1)
					{
						p1.index.y = range.first->second.index;
						p1.weight.y = range.first->second.weight;
					}
					else if (p1.index.z == NUM_MAX_BONES - 1)
					{
						p1.index.z = range.first->second.index;
						p1.weight.z = range.first->second.weight;
					}
					else
					{
						p1.index.w = range.first->second.index;
						p1.weight.w = range.first->second.weight;
					}
				}

				this_index = index_array[3 * j + 1];
				for (std::pair<iter, iter> range(WeightMap.equal_range(this_index)); range.first != range.second; ++range.first)
				{
					if (p2.index.x == NUM_MAX_BONES - 1)
					{
						p2.index.x = range.first->second.index;
						p2.weight.x = range.first->second.weight;
					}
					else if (p2.index.y == NUM_MAX_BONES - 1)
					{
						p2.index.y = range.first->second.index;
						p2.weight.y = range.first->second.weight;
					}
					else if (p2.index.z == NUM_MAX_BONES - 1)
					{
						p2.index.z = range.first->second.index;
						p2.weight.z = range.first->second.weight;
					}
					else
					{
						p2.index.w = range.first->second.index;
						p2.weight.w = range.first->second.weight;
					}
				}

				this_index = index_array[3 * j + 2];
				for (std::pair<iter, iter> range(WeightMap.equal_range(this_index)); range.first != range.second; ++range.first)
				{
					if (p3.index.x == NUM_MAX_BONES - 1)
					{
						p3.index.x = range.first->second.index;
						p3.weight.x = range.first->second.weight;
					}
					else if (p3.index.y == NUM_MAX_BONES - 1)
					{
						p3.index.y = range.first->second.index;
						p3.weight.y = range.first->second.weight;
					}
					else if (p3.index.z == NUM_MAX_BONES - 1)
					{
						p3.index.z = range.first->second.index;
						p3.weight.z = range.first->second.weight;
					}
					else
					{
						p3.index.w = range.first->second.index;
						p3.weight.w = range.first->second.weight;
					}
				}

				mesh.PushBack(p1);
				mesh.PushBack(p2);
				mesh.PushBack(p3);
			}

			WeightMap.clear();
		}

		return true;
	}

	bool LoadSkeleton(Resource::Skeleton& o_skeleton, std::map<String, int>& o_joint_map)
	{
		for (int childIndex = 0; childIndex < lRootNode->GetChildCount(); ++childIndex)
		{
			FbxNode* currNode = lRootNode->GetChild(childIndex);
			ProcessSkeletonHierarchyRecursively(currNode, 0, 0, NUM_MAX_BONES - 1, o_skeleton, o_joint_map);
		}

		return true;
	}

	bool LoadAnimationClip(AnimationClip& o_clip)
	{
		// Get animation information
		// Now only supports one take
		FbxAnimStack* currAnimStack = lScene->GetSrcObject<FbxAnimStack>(0);
		if (currAnimStack)
		{
			FbxString animStackName = currAnimStack->GetName();
			auto mAnimationName = animStackName.Buffer();
			FbxTakeInfo* takeInfo = lScene->GetTakeInfo(animStackName);
			FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
			FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
			FbxLongLong mAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;

			o_clip.frame_count = (int)mAnimationLength;


			for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
			{
				AnimationSample sample;

				FbxTime currTime;
				currTime.SetFrame(i, FbxTime::eFrames24);
				LoadAnimationSample(sample, currTime);
				o_clip.samples.PushBack(sample);
			}
		}
		return true;
	}

	void PrintData()
	{
		// Print the nodes of the scene and their attributes recursively.
		// Note that we are not printing the root node because it should
		// not contain any attributes.
		if (lRootNode)
		{
			for (int i = 0; i < lRootNode->GetChildCount(); i++)
				PrintNode(lRootNode->GetChild(i));
		}
	}

	bool CleanUp()
	{
		// Destroy the SDK manager and all the other objects it was handling.
		lSdkManager->Destroy();

		return true;
	}

	void PrintNode(FbxNode* pNode)
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

	void PrintTabs()
	{
		for (int i = 0; i < numTabs; i++)
			printf("\t");
	}
	
	void PrintAttribute(FbxNodeAttribute* pAttribute)
	{
		if (!pAttribute) return;

		FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
		FbxString attrName = pAttribute->GetName();
		PrintTabs();
		// Note: to retrieve the character array of a FbxString, use its Buffer() method.
		printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
	}

	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type)
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

	FbxAMatrix GetGeometryTransformation(FbxNode* inNode)
	{
		if (!inNode)
		{
			throw std::exception("Null for mesh geometry");
		}

		const FbxVector4 lT = inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = inNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = inNode->GetGeometricScaling(FbxNode::eSourcePivot);

		return FbxAMatrix(lT, lR, lS);
	}

	void ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex, Resource::Skeleton& o_skeleton, std::map<String, int>& o_joint_map)
	{
		if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			Resource::Joint currJoint;
			currJoint.parent_index = inParentIndex;
			//currJoint.name = inNode->GetName();

			FbxAMatrix global_mat = inNode->EvaluateGlobalTransform().Inverse();

			float elemetns[16] = {
				(float)global_mat.Get(0, 0), (float)global_mat.Get(0, 1), (float)global_mat.Get(0, 2), (float)global_mat.Get(0, 3),
				(float)global_mat.Get(1, 0), (float)global_mat.Get(1, 1), (float)global_mat.Get(1, 2), (float)global_mat.Get(1, 3),
				(float)global_mat.Get(2, 0), (float)global_mat.Get(2, 1), (float)global_mat.Get(2, 2), (float)global_mat.Get(2, 3),
				(float)global_mat.Get(3, 0), (float)global_mat.Get(3, 1), (float)global_mat.Get(3, 2), (float)global_mat.Get(3, 3),
			};
			currJoint.inversed = Mat4f(elemetns);

			Mat4f transformation = Mat4f::Inverse(currJoint.inversed);
			Vec3f scale;
			Quaternionf rotation;
			Vec3f translation;
			Vec3f skew;
			Vec4f perspective;
			Mat4f::Decompose(transformation, scale, rotation, translation, skew, perspective);
			currJoint.coord = translation;

			o_skeleton.joints.PushBack(currJoint);

			std::string tmp = inNode->GetName();
			o_joint_map.insert({ tmp,(int)o_skeleton.joints.Size() - 1});
		}
		for (int i = 0; i < inNode->GetChildCount(); i++)
		{
			ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), inDepth + 1, (int)o_skeleton.joints.Size(), myIndex, o_skeleton, o_joint_map);
		}
	}

	int FindJointIndexUsingName(std::string name, const std::map<String, int>& i_joint_map)
	{
		for (auto it = i_joint_map.begin(); it != i_joint_map.end(); ++it)
		{
			if (it->first.compare(name) == 0)
			{
				return it->second;
			}
		}

		return NUM_MAX_BONES - 1;
	}

	bool LoadAnimationSample(AnimationSample& o_sample, FbxTime time)
	{
		for (int childIndex = 0; childIndex < lRootNode->GetChildCount(); ++childIndex)
		{
			FbxNode* currNode = lRootNode->GetChild(childIndex);
			ProcessAnimationSampleRecursively(currNode, 0, 0, NUM_MAX_BONES - 1, o_sample, time);
		}

		return true;
	}

	void ProcessAnimationSampleRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex, AnimationSample& o_sample, FbxTime time)
	{
		if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			JointPose currPose;
			currPose.parent_index = inParentIndex;

			FbxAMatrix global_mat = inNode->EvaluateGlobalTransform(time);

			float elemetns[16] = {
				(float)global_mat.Get(0, 0), (float)global_mat.Get(0, 1), (float)global_mat.Get(0, 2), (float)global_mat.Get(0, 3),
				(float)global_mat.Get(1, 0), (float)global_mat.Get(1, 1), (float)global_mat.Get(1, 2), (float)global_mat.Get(1, 3),
				(float)global_mat.Get(2, 0), (float)global_mat.Get(2, 1), (float)global_mat.Get(2, 2), (float)global_mat.Get(2, 3),
				(float)global_mat.Get(3, 0), (float)global_mat.Get(3, 1), (float)global_mat.Get(3, 2), (float)global_mat.Get(3, 3),
			};
			currPose.global_inversed_matrix = Mat4f(elemetns);

			Mat4f transformation = currPose.global_inversed_matrix;
			Vec3f scale;
			Quaternionf rotation;
			Vec3f translation;
			Vec3f skew;
			Vec4f perspective;
			Mat4f::Decompose(transformation, scale, rotation, translation, skew, perspective);

			currPose.trans = Vec4f(translation, 1.0);
			currPose.rot = rotation;
			currPose.scale = scale;

			o_sample.jointposes.PushBack(currPose);
		}

		for (int i = 0; i < inNode->GetChildCount(); i++)
		{
			ProcessAnimationSampleRecursively(inNode->GetChild(i), inDepth + 1, o_sample.jointposes.Size(), myIndex, o_sample, time);
		}
	}

}