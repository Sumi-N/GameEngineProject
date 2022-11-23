#include "Serializer.h"

#include <EntitySystem/Entity.h>
#include "../MyGame/MyCameraObject.h"

namespace YAML
{
	template<>
	struct convert<Vec3f>
	{
		static Node encode(const Vec3f& i_vec)
		{
			Node node;
			node.push_back(i_vec.x);
			node.push_back(i_vec.y);
			node.push_back(i_vec.z);
			return node;
		}

		static bool decode(const Node& node, Vec3f& io_vec)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			io_vec.x = node[0].as<float>();
			io_vec.y = node[1].as<float>();
			io_vec.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Vec4f>
	{
		static Node encode(const Vec4f& i_vec)
		{
			Node node;
			node.push_back(i_vec.x);
			node.push_back(i_vec.y);
			node.push_back(i_vec.z);
			node.push_back(i_vec.w);
			return node;
		}

		static bool decode(const Node& node, Vec4f& io_vec)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			io_vec.x = node[0].as<float>();
			io_vec.y = node[1].as<float>();
			io_vec.z = node[2].as<float>();
			io_vec.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Tempest::LightType>
	{
		static Node encode(const Tempest::LightType& i_res)
		{
			Node node;
			node.push_back(i_res);
			return node;
		}

		static bool decode(const Node& node, Tempest::LightType& io_res)
		{
			auto data = node.as<Tempest::String>();
			if (data == "AmbientLight")
			{
				io_res = Tempest::LightType::AmbientLight;
			}
			else if (data == "PointLight")
			{
				io_res = Tempest::LightType::PointLight;
			}
			else if (data == "DirectionalLight")
			{
				io_res = Tempest::LightType::DirectionalLight;
			}

			return true;
		}
	};

	template<>
	struct convert<Tempest::MeshType>
	{
		static Node encode(const Tempest::MeshType& i_res)
		{
			Node node;
			node.push_back(i_res);
			return node;
		}

		static bool decode(const Node& node, Tempest::MeshType& io_res)
		{
			auto data = node.as<Tempest::String>();
			if (data == "Mesh")
			{
				io_res = Tempest::MeshType::Mesh;
			}
			else if (data == "SkeletonMesh")
			{
				io_res = Tempest::MeshType::SkeletonMesh;
			}

			return true;
		}
	};
}

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

	YAML::Emitter& operator<<(YAML::Emitter& io_emitter, const LightType& type)
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

	YAML::Emitter& operator<<(YAML::Emitter& io_emitter, const MeshType& type)
	{
		io_emitter << YAML::Flow;

		switch (type)
		{
		case MeshType::Mesh:
			io_emitter << "Mesh";
			break;
		case MeshType::SkeletonMesh:
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

			for (auto it = Entity::BackgroundComponentList.Begin(); it != Entity::BackgroundComponentList.End(); it++)
			{
				if ((*it)->owner == obj)
				{
					io_emitter << YAML::Key << "BackgroundComponent";
					io_emitter << YAML::BeginMap;
					io_emitter << YAML::Key << "MeshPath" << YAML::Value << (*it)->mesh_path;
					io_emitter << YAML::Key << "VertexShader" << YAML::Value << (*it)->shader_paths[0];
					io_emitter << YAML::Key << "FragmentShader" << YAML::Value << (*it)->shader_paths[4];
					io_emitter << YAML::Key << "TexturePath" << YAML::Value << (*it)->texture_path;
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
						if ((*it)->shaderpaths[0].c_str())
							io_emitter << YAML::Key << "VertexShader" << YAML::Value << (*it)->shaderpaths[0];
						if ((*it)->shaderpaths[1].c_str())
							io_emitter << YAML::Key << "ControlShader" << YAML::Value << (*it)->shaderpaths[1];
						if ((*it)->shaderpaths[2].c_str())
							io_emitter << YAML::Key << "EvaluationShader" << YAML::Value << (*it)->shaderpaths[2];
						if ((*it)->shaderpaths[3].c_str())
							io_emitter << YAML::Key << "GeometryShader" << YAML::Value << (*it)->shaderpaths[3];
						if ((*it)->shaderpaths[4].c_str())
							io_emitter << YAML::Key << "FragmentShader" << YAML::Value << (*it)->shaderpaths[4];
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
						if ((*it)->texture_paths[0].c_str())
							io_emitter << YAML::Key << "Albedo" << YAML::Value << (*it)->texture_paths[0];
						if ((*it)->texture_paths[1].c_str())
							io_emitter << YAML::Key << "Normal" << YAML::Value << (*it)->texture_paths[1];
						if ((*it)->texture_paths[2].c_str())
							io_emitter << YAML::Key << "Roughness" << YAML::Value << (*it)->texture_paths[2];
						if ((*it)->texture_paths[3].c_str())
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

			for (auto it = Entity::Animation.Begin(); it != Entity::Animation.End(); it++)
			{
				if ((*it)->owner == obj)
				{
					io_emitter << YAML::Key << "AnimationComponent";
					io_emitter << YAML::BeginMap;
					io_emitter << YAML::Key << "Skeleton" << YAML::Value << (*it)->skeleton_path;
					io_emitter << YAML::Key << "AnimationClip" << YAML::Value << (*it)->animation_clip_path;
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
		std::ifstream fin(i_path);
		std::stringstream string_stream;
		string_stream << fin.rdbuf();

		YAML::Node data = YAML::Load(string_stream.str());

		auto objects_data = data["Scene"];
		if (objects_data)
		{
			for (auto object_data : objects_data)
			{
				Owner<Object> object;
				if (object_data["CameraComponent"])
				{
					object = Create<MyCameraObject>();
				}
				else
				{
					object = Create<Object>();
				}
				Entity::Register(object);
				object->name = object_data["Object"].as<String>();
				object->pos = object_data["Position"].as<Vec3f>();
				object->scale = object_data["Scale"].as<Vec3f>();
				object->rot = object_data["Rotation"].as<Vec3f>();

				auto background_data = object_data["BackgroundComponent"];

				if (background_data)
				{
					Owner<BackgroundComponent> background_component = Create<BackgroundComponent>();
					background_component->owner = object;
					Entity::RegisterBackgroundComponent(background_component);
					background_component->mesh_path = background_data["MeshPath"].as<String>();
					background_component->shader_paths[0] = background_data["VertexShader"].as<String>();
					background_component->shader_paths[4] = background_data["FragmentShader"].as<String>();
					background_component->texture_path = background_data["TexturePath"].as<String>();
					background_component->texture_type = TextureType::SkyBox;
				}

				auto light_data = object_data["LightComponent"];

				if (light_data)
				{
					Owner<LightComponent> light_component = Create<LightComponent>();
					light_component->owner = object;
					Entity::RegisterLightComponent(light_component);
					light_component->light_type = light_data["LightType"].as<LightType>();
					light_component->intensity = light_data["LightIntensity"].as<Vec3f>();
					light_component->attenuation = light_data["LightAttenuation"].as<Vec3f>();
					light_component->direction = light_data["LightDirection"].as<Vec3f>();
				}

				auto effect_data = object_data["EffectComponent"];

				if (effect_data)
				{
					Owner<EffectComponent> effect_component = Create<EffectComponent>();
					effect_component->owner = object;
					Entity::RegisterEffectComponent(effect_component);

					auto shader_data = effect_data["Shader"];

					if (shader_data["VertexShader"])
						effect_component->shaderpaths[0] = shader_data["VertexShader"].as<String>();

					if (shader_data["ControlShader"])
						effect_component->shaderpaths[1] = shader_data["ControlShader"].as<String>();

					if (shader_data["EvaluationShader"])
						effect_component->shaderpaths[2] = shader_data["EvaluationShader"].as<String>();

					if (shader_data["GeometryShader"])
						effect_component->shaderpaths[3] = shader_data["GeometryShader"].as<String>();

					if (shader_data["FragmentShader"])
						effect_component->shaderpaths[4] = shader_data["FragmentShader"].as<String>();

					auto material_data = effect_data["Material"];

					if (material_data)
					{
						effect_component->material.albedo = material_data["Albedo"].as<Vec4f>();
						effect_component->material.roughness = material_data["Roughness"].as<float>();
						effect_component->material.metalic = material_data["Metalic"].as<float>();
					}

					auto texture_data = effect_data["Texture"];

					if (texture_data)
					{
						if (texture_data["Albedo"])
						{
							effect_component->texture_paths[0] = texture_data["Albedo"].as<String>();
							effect_component->texture_types[0] = TextureType::Albedo;
						}

						if (texture_data["Normal"])
						{
							effect_component->texture_paths[1] = texture_data["Normal"].as<String>();
							effect_component->texture_types[1] = TextureType::Normal;
						}

						if (texture_data["Roughness"])
						{
							effect_component->texture_paths[2] = texture_data["Roughness"].as<String>();
							effect_component->texture_types[2] = TextureType::Roughness;
						}

						if (texture_data["Metalic"])
						{
							effect_component->texture_paths[3] = texture_data["Metalic"].as<String>();
							effect_component->texture_types[3] = TextureType::Metalic;
						}
					}
				}

				auto mesh_data = object_data["MeshComponent"];

				if (mesh_data)
				{
					Owner<MeshComponent> mesh_component = Create<MeshComponent>();
					mesh_component->owner = object;
					Entity::RegisterMeshComponent(mesh_component);
					mesh_component->mesh_type = mesh_data["MeshType"].as<MeshType>();
					mesh_component->mesh_path = mesh_data["MeshPath"].as<String>();
				}

				auto animation_data = object_data["AnimationComponent"];

				if (animation_data)
				{
					Owner<AnimationComponent> animation_component = Create<AnimationComponent>();
					animation_component->owner = object;
					Entity::RegisterAnimationComponent(animation_component);
					animation_component->skeleton_path = animation_data["Skeleton"].as<String>();
					animation_component->animation_clip_path = animation_data["AnimationClip"].as<String>();
				}
			}
		}
	}
}
