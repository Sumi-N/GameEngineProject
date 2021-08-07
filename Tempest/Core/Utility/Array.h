#pragma once

#include "Define.h"

namespace Tempest
{
#ifdef USE_STANDARD_ARRAY
	template <typename T>
	using Array = std::vector<T>;
#else
	template <typename T>
	class Array
	{
	public:		

		class Iterator
		{
		public:
			Iterator() : p(nullptr){}
			
		private:
			T* p;
		}

		Array() = default;		
		~Array() = default;

		size_t Size();
		size_t MaxSize();
		void   Resize(size_t);
		//size_t Capacity();
		bool   Empty();
		//void   Reserve(size_t);
		//void   ShrinkToFit();

		T&     operator[](size_t);
		T&     At(size_t);
		//T&     Front();
		//T&     Back();
		T*     Data();
		
		//void   Assign();
		void   PushBack(const T&);
		void   PopBack();
		void   Insert();
		void   Erase();
		void   Swap();
		void   Clear();
		void   Emplace();
		void   EmplaceBack();

	private:
		size_t max_size;
		size_t size;
		T*     data;
	};

#endif

}

