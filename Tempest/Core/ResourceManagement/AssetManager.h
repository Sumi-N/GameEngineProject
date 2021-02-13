#pragma once

namespace Tempest
{
	template<class T, class U = std::string>
	class AssetManager
	{
	public:

		//T* Get(const Handle<T> i_handle);

	private:

		std::map<U, T*> path_data_map;
	};

}

