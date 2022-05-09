#include "Serializer.h"

#include <EntitySystem/Entity.h>

namespace Tempest
{
	YAML::Emitter& operator<<(YAML::Emitter& io_emitter, const Vec3f& vec3f)
	{
		io_emitter << YAML::Flow;
		io_emitter << YAML::BeginSeq << vec3f.x << vec3f.y << vec3f.z << YAML::EndSeq;
		return io_emitter;
	}

	YAML::Emitter& operator<<(YAML::Emitter& io_emitter, const Vec4f& vec4f)
	{
		io_emitter << YAML::Flow;
		io_emitter << YAML::BeginSeq << vec4f.x << vec4f.y << vec4f.z << vec4f.w << YAML::EndSeq;
		return io_emitter;
	}

	YAML::Emitter& operator<<(YAML::Emitter& io_emitter, const Resource::LightType& type)
	{
		io_emitter << YAML::Flow;

		switch (type)
		{
		case LightType::Uninitialized:
			DEBUG_ASSERT(false);
			break;
		case LightType::AmbientLight:
			io_emitter << "AmbientLight";
			break;
		case LightType::PointLight:
			io_emitter << "PointLight";
			break;
		case LightType::DirectionalLight:
			io_emitter << "DirectionalLight";
			break;
		}
		return io_emitter;
	}

	YAML::Emitter& operator<<(YAML::Emitter& io_emitter, const Resource::MeshType& type)
	{
		io_emitter << YAML::Flow;

		switch (type)
		{
		case Resource::MeshType::Mesh:
			io_emitter << "Mesh";
			break;
		case Resource::MeshType::SkeletonMesh:
			io_emitter << "SkeletonMesh";
			break;
		}		
		return io_emitter;
	}

	void SerializeScene(YAML::Emitter& io_emitter)
	{
		for (auto obj_itr = Entity::ObjectList.Begin(); obj_itr != Entity::ObjectList.End(); obj_itr++)
		{
			auto obj = (*obj_itr);
			
			//io_emitter << YAML::Key << "Object";
			io_emitter << YAML::BeginMap;
			io_emitter << YAML::Key << "Object" << YAML::Value << obj->name;			
			io_emitter << YAML::Key << "Position" << YAML::Value << obj->pos;
			io_emitter << YAML::Key << "Rotation" << YAML::Value << obj->rot;
			io_emitter << YAML::Key << "Scale" << YAML::Value << obj->scale;

			for (auto it = Entity::CameraComponentList.Begin(); it != Entity::CameraComponentList.End(); it++)
			{
				if ((*it)->owner == obj)
				{
					io_emitter << YAML::Key << "CameraComponent";
					io_emitter << YAML::BeginMap;
					io_emitter << YAML::Key << "Test" << YAML::Value << "Test";
					io_emitter << YAML::EndMap;
				}
			}

			for (auto it = Entity::LightComponentList.Begin(); it != Entity::LightComponentList.End(); it++)
			{
				if ((*it)->owner == obj)
				{
					io_emitter << YAML::Key << "LightComponent";
					io_emitter << YAML::BeginMap;
					io_emitter << YAML::Key << "LightType" << YAML::Value << (*it)->light_type;
					io_emitter << YAML::Key << "LightIntensity" << YAML::Value << (*it)->intensity;
					io_emitter << YAML::Key << "LightAttenuation" << YAML::Value << (*it)->attenuation;
					io_emitter << YAML::Key << "LightDirection" << YAML::Value << (*it)->direction;
					io_emitter << YAML::EndMap;
				}
			}

			for (auto it = Entity::EffectComponentList.Begin(); it != Entity::EffectComponentList.End(); it++)
			{
				if ((*it)->owner == obj)
				{
					io_emitter << YAML::Key << "EffectComponent";
					io_emitter << YAML::BeginMap;

					{
						io_emitter << YAML::Key << "Shader";
						io_emitter << YAML::BeginMap;
						if ((*it)->shaderpaths[0])
							io_emitter << YAML::Key << "Vertex Shader" << YAML::Value << (*it)->shaderpaths[0];
						if ((*it)->shaderpaths[1])
							io_emitter << YAML::Key << "Control Shader" << YAML::Value << (*it)->shaderpaths[1];
						if ((*it)->shaderpaths[2])
							io_emitter << YAML::Key << "Evaluation Shader" << YAML::Value << (*it)->shaderpaths[2];
						if ((*it)->shaderpaths[3])
							io_emitter << YAML::Key << "Geometry Shader" << YAML::Value << (*it)->shaderpaths[3];
						if ((*it)->shaderpaths[4])
							io_emitter << YAML::Key << "Fragment Shader" << YAML::Value << (*it)->shaderpaths[4];
						io_emitter << YAML::EndMap;
					}

					{
						io_emitter << YAML::Key << "Material";
						io_emitter << YAML::BeginMap;
						io_emitter << YAML::Key << "Albedo" << YAML::Value << (*it)->material.albedo;
						io_emitter << YAML::Key << "Roughness" << YAML::Value << (*it)->material.roughness;
						io_emitter << YAML::Key << "Metalic" << YAML::Value << (*it)->material.metalic;
						io_emitter << YAML::EndMap;
					}

					{
						io_emitter << YAML::Key << "Texture";
						io_emitter << YAML::BeginMap;
						if ((*it)->texture_paths[0])
							io_emitter << YAML::Key << "Albedo" << YAML::Value << (*it)->texture_paths[0];
						if ((*it)->texture_paths[1])
							io_emitter << YAML::Key << "Normal" << YAML::Value << (*it)->texture_paths[1];
						if ((*it)->texture_paths[2])
							io_emitter << YAML::Key << "Roughness" << YAML::Value << (*it)->texture_paths[2];
						if ((*it)->texture_paths[3])
							io_emitter << YAML::Key << "Metalic" << YAML::Value << (*it)->texture_paths[3];
						io_emitter << YAML::EndMap;
					}

					io_emitter << YAML::EndMap;
				}
			}

			for (auto it = Entity::MeshComponentList.Begin(); it != Entity::MeshComponentList.End(); it++)
			{
				if ((*it)->owner == obj)
				{
					io_emitter << YAML::Key << "MeshComponent";
					io_emitter << YAML::BeginMap;
					io_emitter << YAML::Key << "MeshType" << YAML::Value << (*it)->mesh_type;
					if ((*it)->mesh_path[0])
						io_emitter << YAML::Key << "MeshPath" << YAML::Value << (*it)->mesh_path;					
					io_emitter << YAML::EndMap;
				}
			}

			io_emitter << YAML::EndMap;
		}
	}

	void Serializer::Serialize(const Tempest::String& i_path)
	{
		YAML::Emitter emitter;
		emitter << YAML::BeginMap;
		emitter << YAML::Key << "Scene" << YAML::Value << YAML::BeginSeq;
		
		SerializeScene(emitter);

		emitter << YAML::EndSeq;
		emitter << YAML::EndMap;

		std::ofstream fout(i_path);
		fout << emitter.c_str();
	}

	void Serializer::Deserialize(const Tempest::String& i_path)
	{
		//std::ifstream fin(i_path);
		//std::stringstream string_stream;
		//string_stream << fin.rdbuf();

		//YAML::Node data = YAML::Load(string_stream.str());

		//auto objects_data = data["Object"];
		//if (objects_data)
		//{
		//	for (auto object_data : objects_data)
		//	{
		//		Owner<Object> object = Create<Owner<Object>>();
		//		object->pos = object_data["Position"].as<Vec3f>();
		//		object->scale = object_data["Scale"].as<Vec3f>();
		//		object->rot = object_data["Rotation"].as<Vec3f>();

		//		auto mesh_data = object_data["MeshComponent"];

		//		if (mesh_data)
		//		{
		//			Owner<MeshComponent> mesh_component = Create<Owner<MeshComponent>>();
		//			
		//		}
		//	}
		//}
	}
}
