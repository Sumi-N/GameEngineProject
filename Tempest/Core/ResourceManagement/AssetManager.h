#pragma once
#include "Define.h"
#include "ResourceData.h"

namespace Tempest
{

	template<typename T, typename U = String>
	class AssetManager
	{				
	public:
		static OwningPointer<T> Get(U i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				return it->second;
			}
			return OwningPointer<Resource::Mesh>();
		}

		static OwningPointer<T> Load(U i_filename) {};
	private:
		static std::map<U, OwningPointer<T>> table;				
	};

	template <>
	class AssetManager<Resource::Mesh, String>
	{
	public:
		static OwningPointer<Resource::Mesh>  Get(String i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				return it->second;
			}
			return OwningPointer<Resource::Mesh>();
		}

		static OwningPointer<Resource::Mesh> Load(String i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				DEBUG_PRINT("%s is already loaded", i_filename.c_str());

				return it->second;
			}
			else
			{				
				OwningPointer<Resource::Mesh> mesh = OwningPointer<Resource::Mesh>::Create(mesh);
				if (Resource::Mesh::Load(i_filename.c_str(), mesh->data, mesh->index))
				{
					table.insert({ i_filename, mesh });

					DEBUG_PRINT("Mesh data %s is loaded", i_filename.c_str());

					return mesh;
				}
				else
				{
					return OwningPointer<Resource::Mesh>();
				}
			}			
		}
	private:
		static std::map<String, OwningPointer<Resource::Mesh>> table;
	};

	template <typename T, typename U>
	std::map<U, OwningPointer<T>> AssetManager<T, U>::table;

	std::map<String, OwningPointer<Resource::Mesh>> AssetManager<Resource::Mesh, String>::table;
}

