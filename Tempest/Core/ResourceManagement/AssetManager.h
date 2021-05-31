#pragma once
#include "ResourceData.h"

namespace Tempest
{

	template<class T, class U = std::string>
	class AssetManager
	{				

	public:

		template<T> 
		class Handler
		{			
		public:
			uint16_t GetID(){ return id;};
		private:
			static uint16_t global_num = 0;
			uint16_t id;			
		};

		static T* Get(Handler<T> i_handler)
		{			
			auto it = path_data_map.find(i_handler.GetID());
			if (it != path_data_map.end())
			{
				return 
			}
			return nullptr;
		}

		static Handler<T> Load(const U i_string)
		{
			
		}

	private:

		static std::map<uint16_t, T*> path_data_map;		
	};
	
	typedef AssetManager<Resource::Mesh> MeshManager;
}

