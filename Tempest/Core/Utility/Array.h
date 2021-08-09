#pragma once

#include "Define.h"

namespace Tempest
{
#ifdef USE_STANDARD_ARRAY
	template <typename T>
	class Array
	{
	public:
		auto Begin() {return vector.begin(); }
		auto End()   {return vector.end(); }

		T*   Data(){return vector.data(); }
		bool Empty(){return vector.empty();}
		void Resize(size_t i_size){vector.resize(i_size); }
		void PushBack(const T& i_t){vector.push_back(i_t); }
		void Clear() {vector.clear(); }
		size_t Size(){return vector.size(); }

		T& operator[](size_t i_size){ return vector[i_size];};
	public:
		std::vector<T> vector;
	};
#else
	template <typename T>
	class Array
	{
	public:		

		class Iterator
		{
		public:
			Iterator() : p(nullptr) {}
			Iterator(const T* t) : p(t) {}

			Iterator& operator=(T* t) {}
			Iterator& operator++() {}
			Iterator& operator++(int t) {}

			bool      operator!=(const Iterator& iterator) {}
			T& operator*() { return *p;}
		private:
			T* p;
		};

		Array();
		~Array();
		
		Array& operator=(Array);

		Iterator	Begin	 () const {return Iterator(data); }
		Iterator	End		 () const {return Iterator(*this[size - 1]); }

		size_t		Size     () const {return this->size; }
		size_t		MaxSize  () const {return this->max_size; }
		//size_t	Capacity () const {return this->capacity; }
		T*          Data     () const {return this->data };

		void		Resize   (size_t);		
		bool		Empty    ();
		//void		Reserve(size_t);
		//void		ShrinkToFit();

		T&	operator[](size_t);
		T&	At(size_t);
		T&  UnsafeAt(size_t);
		//T&     Front();
		//T&     Back();		
		
		//void		Assign();
		void		PushBack(const T&);
		//void      PopBack();
		//Iterator	Insert(const Iterator, const T&);
		//Iterator	Erase(const Iterator);
		//void		Swap(Array&);
		void        Clear();
		//Iterator	Emplace();
		//Iterator	EmplaceBack();

	private:		
		size_t max_size;
		//size_t capcity;
		size_t size;
		size_t granularity;
		T*     data;		
	};

	template <typename T>
	inline Array<T>::Array<T>()
		: max_size(0), granularity(10), size(0), data(nullptr) {}

	template <typename T>
	inline Array<T>::~Array<T>()
	{
		FreeMemory(data);
	}

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
		this->data = AllocMemory(max_size);
		memcpy(this->data, i_array.Data(), max_size * sizeof(T));
	}

	template <typename T>
	inline void Array<T>::Resize(size_t i_size)
	{
		if (i_size > max_size)
		{
			data = ReallocMemory(data, i_size * sizeof(T));
			max_size = i_size;
		}
		else if (i_size < max_size)
		{
			data = ReallocMemory(data, i_size * sizeof(T));
			max_size = i_size;
			if (size > i_size)
			{
				size = i_size;
			}
		}		
	}

	template <typename T>
	inline bool Array<T>::Empty()
	{
		if (max_size == 0 || size == 0)		
			return true;		
		return false;
	}

	template <typename T>
	inline T& Array<T>::operator[](size_t i_size)
	{
		if (i_size >= size)	
			DEBUG_ASSERT(true);		
		return data[i_size];
	}

	template <typename T>
	inline T& Array<T>::At(size_t i_size)
	{
		if (i_size >= size)		
			DEBUG_ASSERT(true);		
		return data[i_size];
	}

	template <typename T>
	inline T& Array<T>::UnsafeAt(size_t i_size)
	{
		if (i_size >= max_size)
			DEBUG_ASSERT(true);
		return data[i_size];
	}

	template <typename T>
	inline void Array<T>::PushBack(const T& i_data)
	{
		if (size >= max_size)
		{
			data = ReallocMemory(data, (max_size + granularity) * sizeof(T));
			max_size += granularity;
		}
		T& tmp = UnsafeAt(size);
		tmp = i_data;
		size++;
	}

	template <typename T>
	inline void Array<T>::Clear()
	{
		FreeMemory(data);
		max_size = 0;
		size = 0;
		data = nullptr;
	}

#endif
}

