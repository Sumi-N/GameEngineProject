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
			return OwningPointer<Mesh>();
		}

		static OwningPointer<T> Load(U i_filename) {};
	private:
		static std::map<U, OwningPointer<T>> table;
	};

	template <>
	class AssetManager<Mesh, String>
	{
	public:
		static OwningPointer<Mesh>  Get(String i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				return it->second;
			}
			return OwningPointer<Mesh>();
		}

		static OwningPointer<Mesh> Load(String i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				DEBUG_PRINT("%s is already loaded", i_filename.c_str());

				return it->second;
			}
			else
			{
				OwningPointer<Mesh> mesh = OwningPointer<Mesh>::Create(mesh);
				if (Mesh::Load(i_filename.c_str(), *mesh))
				{
					table.insert({ i_filename, mesh });

					DEBUG_PRINT("Mesh data %s is loaded", i_filename.c_str());

					return mesh;
				}
				else
				{
					return OwningPointer<Mesh>();
				}
			}
		}
	private:
		static std::map<String, OwningPointer<Mesh>> table;
	};

	template <>
	class AssetManager<SkeletonMesh, String>
	{
	public:
		static OwningPointer<SkeletonMesh>  Get(String i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				return it->second;
			}
			return OwningPointer<SkeletonMesh>();
		}

		static OwningPointer<SkeletonMesh> Load(String i_filename)
		{
			auto it = table.find(i_filename);
			if (it != table.end())
			{
				DEBUG_PRINT("%s is already loaded", i_filename.c_str());

				return it->second;
			}
			else
			{
				OwningPointer<SkeletonMesh> smesh = OwningPointer<SkeletonMesh>::Create(smesh);
				if (SkeletonMesh::Load(i_filename.c_str(), *smesh))
				{
					table.insert({ i_filename, smesh });

					DEBUG_PRINT("Mesh data %s is loaded", i_filename.c_str());

					return smesh;
				}
				else
				{
					return OwningPointer<SkeletonMesh>();
				}
			}
		}
	private:
		static std::map<String, OwningPointer<SkeletonMesh>> table;
	};

	template <typename T, typename U>
	std::map<U, OwningPointer<T>> AssetManager<T, U>::table;

	std::map<String, OwningPointer<Mesh>> AssetManager<Mesh, String>::table;
	std::map<String, OwningPointer<SkeletonMesh>> AssetManager<SkeletonMesh, String>::table;
}

