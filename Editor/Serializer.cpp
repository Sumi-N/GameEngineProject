#include "Serializer.h"
#include <yaml-cpp/yaml.h>

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

	void SerializeScene(YAML::Emitter& io_emitter)
	{
		for (auto obj_itr = Entity::ObjectList.Begin(); obj_itr != Entity::ObjectList.End(); obj_itr++)
		{
			auto obj = (*obj_itr);
			
			io_emitter << YAML::Key << "Object";
			io_emitter << YAML::BeginMap;
			io_emitter << YAML::Key << "Name" << YAML::Value << obj->name;
			io_emitter << YAML::Key << "Position" << YAML::Value << obj->pos;
			io_emitter << YAML::Key << "Rotation" << YAML::Value << obj->rot;
			io_emitter << YAML::Key << "Scale" << YAML::Value << obj->scale;			

			for (auto it = Entity::MeshComponentList.Begin(); it != Entity::MeshComponentList.End(); it++)
			{
				if ((*it) = obj)
				{
					io_emitter << YAML::Key << "Mesh Component";
					io_emitter << YAML::BeginMap;
					io_emitter << YAML::Key << "Name" << YAML::Value << (*it)->mesh;
					io_emitter << YAML::EndMap;
				}
			}

			io_emitter << YAML::EndMap;
		}
	}

	void Serializer::Serialize(const Tempest::String i_path)
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

	void Serializer::Deserialize()
	{

	}
}
