#pragma once
#include <yaml-cpp/yaml.h>
#include <Utility/File.h>

namespace Tempest
{
	class Serializer
	{
	public:
		void Serialize(Tempest::String);
		void Deserialize();
	};
}

