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
			Iterator() : p(nullptr)
			{
			}
			Iterator(const T* t) : p(t)
			{
			}
			Iterator& operator=(T* t)
			{

			}
			Iterator& operator++()
			{
			}
			Iterator& operator++(int t)
			{
			}

			bool      operator!=(const Iterator& iterator)
			{

			}
			T& operator*()
			{
				return *p;
			}
		private:
			T* p;
		};

		Array() = default;		
		~Array() = default;
		
		Array& operator=(Array);

		Iterator	Begin	 () const {return Iterator(data); }
		Iterator	End		 () const {return Iterator(*this[size - 1]); }

		size_t		Size     () const {return this->size; }
		size_t		MaxSize  () const {return this->max_size; }
		void		Resize   (size_t);
		size_t		Capacity () {return this->capacity; }
		bool		Empty    ();
		//void		Reserve(size_t);
		//void		ShrinkToFit();

		T&	operator[](size_t);
		T&	At(size_t);
		//T&     Front();
		//T&     Back();
		T*     Data();
		
		//void		Assign();
		void		PushBack(const T&);
		void        PopBack();
		Iterator	Insert(const Iterator, const T&);
		Iterator	Erase(const Iterator);
		void		Swap(Array&);
		void        Clear();
		//Iterator	Emplace();
		//Iterator	EmplaceBack();

	private:
		size_t max_size;
		size_t capcity;
		size_t size;
		T*     data;
	};

	template <typename T>
	inline Array<T>& Array<T>::operator= (Array<T> i_array)
	{
		if (!this->Empty())
		{
			this->Clear();
		}
		this->max_size = i_array.MaxSize();
		this->capacity = i_array.capcity();
		this->size     = i_array.Size();
		this->data     = i_array.Data();
	}

#endif
}

