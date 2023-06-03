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
			return OwningPointer<T>();
		}

		static OwningPointer<T> Load(U i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				DEBUG_PRINT("%s is already loaded", i_filename.c_str());

				return it->second;
			}
			else
			{
				OwningPointer<T> mesh = OwningPointer<T>::Create(mesh);
				if (T::Load(i_filename.c_str(), *mesh))
				{
					table.insert({ i_filename, mesh });

					DEBUG_PRINT("Mesh data %s is loaded", i_filename.c_str());

					return mesh;
				}
				else
				{
					return OwningPointer<T>();
				}
			}
		};
	private:
		static std::map<U, OwningPointer<T>> table;
	};

	template <typename T, typename U>
	std::map<U, OwningPointer<T>> AssetManager<T, U>::table;

	std::map<String, OwningPointer<Mesh>>         AssetManager<Mesh, String>::table;
	std::map<String, OwningPointer<SkeletonMesh>> AssetManager<SkeletonMesh, String>::table;
	std::map<String, OwningPointer<ShaderInfo>>   AssetManager<ShaderInfo, String>::table;
}

