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

				Resource::MeshPoint p[3];

				FbxVector2 uv[3];
				bool flag[3];

				// Get the first UV sets
				if (uvsetName.GetCount() > 0)
				{
					pMesh->GetPolygonVertexUV(j, 0, uvsetName.GetStringAt(0), uv[0], flag[0]);
					pMesh->GetPolygonVertexUV(j, 1, uvsetName.GetStringAt(0), uv[1], flag[1]);
					pMesh->GetPolygonVertexUV(j, 2, uvsetName.GetStringAt(0), uv[2], flag[2]);
				}

				for (int k = 0; k < 3; k++)
				{
					p[k].vertex.x = (float)vertex_array[index_array[3 * j + k]].mData[0];
					p[k].vertex.y = (float)vertex_array[index_array[3 * j + k]].mData[1];
					p[k].vertex.z = (float)vertex_array[index_array[3 * j + k]].mData[2];					

					p[k].normal.x = (float)normal_array[3 * j + k].mData[0];
					p[k].normal.y = (float)normal_array[3 * j + k].mData[1];
					p[k].normal.z = (float)normal_array[3 * j + k].mData[2];					

					p[k].vertex = Vec3f(model_matrix * Vec4f(p[k].vertex.x, p[k].vertex.y, p[k].vertex.z, 1.0));
					p[k].normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p[k].normal.x, p[k].normal.y, p[k].normal.z, 1.0));

					p[k].uv.x = (float)uv[k].mData[0];
					p[k].uv.y = (float)uv[k].mData[1];
				}

				{
					Vec3f edge[2];
					edge[0] = p[1].vertex - p[0].vertex;
					edge[1] = p[2].vertex - p[0].vertex;

					Vec2f deltauv[2];
					deltauv[0] = p[1].uv - p[0].uv;
					deltauv[1] = p[2].uv - p[0].uv;

					float f = 1.0f / (deltauv[0].x * deltauv[1].y - deltauv[1].x * deltauv[0].y);

					Vec3f tangent;
					tangent.x = f * (deltauv[1].y * edge[0].x - deltauv[0].y * edge[1].x);
					tangent.y = f * (deltauv[1].y * edge[0].y - deltauv[0].y * edge[1].y);
					tangent.z = f * (deltauv[1].y * edge[0].z - deltauv[0].y * edge[1].z);
					tangent.Normalize();

					Vec3f bitangent;
					bitangent.x = f * (-deltauv[1].x * edge[0].x + deltauv[0].x * edge[1].x);
					bitangent.y = f * (-deltauv[1].x * edge[0].y + deltauv[0].x * edge[1].y);
					bitangent.z = f * (-deltauv[1].x * edge[0].z + deltauv[0].x * edge[1].z);
					bitangent.Normalize();

					p[0].tangent = tangent;
					p[0].bitangent = bitangent;

					p[1].tangent = tangent;
					p[1].bitangent = bitangent;

					p[2].tangent = tangent;
					p[2].bitangent = bitangent;
				}

				mesh.PushBack(p[0]);
				mesh.PushBack(p[1]);
				mesh.PushBack(p[2]);
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
						currBlending.weight = (float)currCluster->GetControlPointWeights()[j];

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

				Resource::SkeletonMeshPoint p[3];

				FbxVector2 uv[3];
				bool flag[3];

				// Get the first UV sets
				if (uvsetName.GetCount() > 0)
				{
					pMesh->GetPolygonVertexUV(j, 0, uvsetName.GetStringAt(0), uv[0], flag[0]);
					pMesh->GetPolygonVertexUV(j, 1, uvsetName.GetStringAt(0), uv[1], flag[1]);
					pMesh->GetPolygonVertexUV(j, 2, uvsetName.GetStringAt(0), uv[2], flag[2]);
				}

				for (int k = 0; k < 3; k++)
				{
					p[k].vertex.x = (float)vertex_array[index_array[3 * j + k]].mData[0];
					p[k].vertex.y = (float)vertex_array[index_array[3 * j + k]].mData[1];
					p[k].vertex.z = (float)vertex_array[index_array[3 * j + k]].mData[2];

					p[k].normal.x = (float)normal_array[3 * j + k].mData[0];
					p[k].normal.y = (float)normal_array[3 * j + k].mData[1];
					p[k].normal.z = (float)normal_array[3 * j + k].mData[2];

					p[k].vertex = Vec3f(model_matrix * Vec4f(p[k].vertex.x, p[k].vertex.y, p[k].vertex.z, 1.0));
					p[k].normal = Vec3f(model_inverse_transpose_matrix * Vec4f(p[k].normal.x, p[k].normal.y, p[k].normal.z, 1.0));

					p[k].uv.x = (float)uv[k].mData[0];
					p[k].uv.y = (float)uv[k].mData[1];					
				}

				// Get skin info from WidhtMap
				typedef std::multimap<int, BlendingWeight>::iterator iter;

				for (int k = 0; k < 3; k++)
				{
					int current_index = index_array[3 * j + k];
					for (std::pair<iter, iter> range(WeightMap.equal_range(current_index)); range.first != range.second; ++range.first)
					{
						if (p[k].index.x == NUM_MAX_BONES - 1)
						{
							p[k].index.x = range.first->second.index;
							p[k].weight.x = range.first->second.weight;
						}
						else if (p[k].index.y == NUM_MAX_BONES - 1)
						{
							p[k].index.y = range.first->second.index;
							p[k].weight.y = range.first->second.weight;
						}
						else if (p[k].index.z == NUM_MAX_BONES - 1)
						{
							p[k].index.z = range.first->second.index;
							p[k].weight.z = range.first->second.weight;
						}
						else
						{
							p[k].index.w = range.first->second.index;
							p[k].weight.w = range.first->second.weight;
						}
					}
				}
				
				{
					Vec3f edge[2];
					edge[0] = p[1].vertex - p[0].vertex;
					edge[1] = p[2].vertex - p[0].vertex;

					Vec2f deltauv[2];
					deltauv[0] = p[1].uv - p[0].uv;
					deltauv[1] = p[2].uv - p[0].uv;

					float f = 1.0f / (deltauv[0].x * deltauv[1].y - deltauv[1].x * deltauv[0].y);

					Vec3f tangent;
					tangent.x = f * (deltauv[1].y * edge[0].x - deltauv[0].y * edge[1].x);
					tangent.y = f * (deltauv[1].y * edge[0].y - deltauv[0].y * edge[1].y);
					tangent.z = f * (deltauv[1].y * edge[0].z - deltauv[0].y * edge[1].z);
					tangent.Normalize();

					Vec3f bitangent;
					bitangent.x = f * (-deltauv[1].x * edge[0].x + deltauv[0].x * edge[1].x);
					bitangent.y = f * (-deltauv[1].x * edge[0].y + deltauv[0].x * edge[1].y);
					bitangent.z = f * (-deltauv[1].x * edge[0].z + deltauv[0].x * edge[1].z);
					bitangent.Normalize();

					p[0].tangent = tangent;
					p[0].bitangent = bitangent;

					p[1].tangent = tangent;
					p[1].bitangent = bitangent;

					p[2].tangent = tangent;
					p[2].bitangent = bitangent;
				}

				mesh.PushBack(p[0]);
				mesh.PushBack(p[1]);
				mesh.PushBack(p[2]);
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
		//int num_stacks = lScene->GetSrcObjectCount(FBX_TYPE(FbxAnimStack));
		FbxAnimStack* current_anim_stack = lScene->GetSrcObject<FbxAnimStack>(0);		
		if (current_anim_stack)
		{
			FbxString animStackName = current_anim_stack->GetName();
			auto mAnimationName = animStackName.Buffer();
			FbxTakeInfo* takeInfo = lScene->GetTakeInfo(animStackName);
			FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
			FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
			FbxTime duration = takeInfo->mLocalTimeSpan.GetDuration();
			FbxLongLong long_duration = duration.Get();
			FbxLongLong mAnimationLength = duration.GetFrameCount(FbxTime::eFrames30);

			o_clip.frame_count = (int)mAnimationLength;

			for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames30); i <= end.GetFrameCount(FbxTime::eFrames30); ++i)
			{
				AnimationSample sample;

				FbxTime currTime;
				currTime.SetFrame(i, FbxTime::eFrames30);				
				for (int childIndex = 0; childIndex < lRootNode->GetChildCount(); ++childIndex)
				{
					FbxNode* currNode = lRootNode->GetChild(childIndex);
					ProcessAnimationSampleRecursively(currNode, 0, 0, NUM_MAX_BONES - 1, sample, currTime);
				}
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
			Joint currJoint;
			currJoint.parent_index = inParentIndex;			

			double* elements_double = inNode->EvaluateGlobalTransform().Inverse();
			float elements_float[16];
			for (int i = 0; i < 16; i++)
				elements_float[i] = elements_double[i];

			currJoint.inversed = Mat4f(elements_float);

			Mat4f transformation = Mat4f::Inverse(currJoint.inversed);
			Vec3f scale;
			Quaternionf rotation;
			Vec3f translation;
			Vec3f skew;
			Vec4f perspective;
			Mat4f::Decompose(transformation, scale, rotation, translation, skew, perspective);
			currJoint.coord = translation;

			o_skeleton.joints.PushBack(currJoint);

			std::string name = inNode->GetName();
			o_joint_map.insert({ name,(int)o_skeleton.joints.Size() - 1});
		}



		for (int i = 0; i < inNode->GetChildCount(); i++)
		{
			ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), inDepth + 1, (int)o_skeleton.joints.Size(), myIndex, o_skeleton, o_joint_map);
		}
	}

	void ProcessAnimationSampleRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex, AnimationSample& o_sample, FbxTime time)
	{
		if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			JointPose currPose;
			currPose.parent_index = inParentIndex;

			String name = inNode->GetName();
			double* elements_double = inNode->EvaluateGlobalTransform(time);
			float elements_float[16];
			for (int i = 0; i < 16; i++)
				elements_float[i] = elements_double[i];

			currPose.global_inversed_matrix = Mat4f(elements_float);

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
			ProcessAnimationSampleRecursively(inNode->GetChild(i), inDepth + 1, (int)o_sample.jointposes.Size(), myIndex, o_sample, time);
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
}