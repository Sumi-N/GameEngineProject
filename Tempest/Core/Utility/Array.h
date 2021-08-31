#pragma once

#include "Define.h"

namespace Tempest
{
#ifdef USE_STANDARD_ARRAY
	template <typename T>
	class Array
	{
	public:
		
		typename std::vector<T>::iterator Begin()   {return vector.begin(); }
		typename std::vector<T>::iterator End  ()   {return vector.end(); }

		T*     Data    ()              {return vector.data(); }
		bool   Empty   ()              {return vector.empty();}
		void   Resize  (size_t i_size) {vector.resize(i_size); }
		void   PushBack(const T& i_t)  {vector.push_back(i_t); }
		void   Clear   ()              {vector.clear(); }
		size_t Size    ()              {return vector.size(); }

		T& operator[](size_t i_size){ return vector[i_size];};
						
	public:
		std::vector<T> vector;
	};

	namespace Utility
	{
		template <typename T>
		inline auto Distance(typename std::vector<T>::iterator i_first, typename std::vector<T>::iterator i_last)
		{
			return  std::distance(i_first, i_last);
		}
	}

#else
	template <typename T>
	class Array
	{
	public:		

		class Iterator
		{
		public:		
			Iterator()                                     : array(nullptr), index(0)       {}
			Iterator(const Array* i_array, size_t i_index) : array(i_array), index(i_index) {}

			Iterator& operator= (Iterator i_iterator) {this->array = i_iterator->array; this->index = i_iterator->index; return this;}
			Iterator& operator++()                    
			{
				index++; return *this;
			}
			Iterator  operator++(int t)               {Iterator iterator = *this; index++; return iterator;}
			T*        operator->()                    {return &(array->At(index));}
			T&        operator* ()                    {return array->At(index);}

			size_t       GetIndex() const {return index; }
			const Array* GetArray() const {return array; }

			//bool      operator==(const Iterator& i_iterator)
			//{
			//	if (i_iterator.GetArray() == nullptr)
			//	{
			//		if (array == nullptr)
			//		{
			//			return true;
			//		}
			//		else
			//		{
			//			return false;
			//		}
			//	}
			//	if (index == i_iterator.GetIndex() && array == i_iterator.GetArray())
			//	{
			//		return true;
			//	}
			//	return false;
			//}

			bool      operator!=(const Iterator& i_iterator) 
			{	
				if (i_iterator.GetArray() == nullptr)
				{
					if (index >= array->Size())
					{
						return false;
					}
					else
					{
						return true;
					}
				}

				if (index != i_iterator.GetIndex() && array != i_iterator.GetArray())
				{
					return true;
				}
				return false;
			}			

		private:
			const Array* array;
			size_t index;
		};

		friend class Iterator;

		Array();
		Array(const Array& i_array);
		~Array();		
		
		Array& operator=(Array);		 
		Array& Convert(std::initializer_list<T>);

		Iterator	Begin()
		{
			return Iterator(this, 0);
		}
		Iterator	End		 () {return Iterator(); }

		size_t		Size     () const {return this->size; }
		size_t		MaxSize  () const {return this->max_size; }
		size_t		Capacity () const {return this->capacity; }
		T*          Data     () const {return this->data; };

		void		Resize   (size_t);		
		bool		Empty    ();
		//void		Reserve(size_t);
		//void		ShrinkToFit();

		T&	operator[](size_t) const;
		T&	At        (size_t) const;
		T&  UnsafeAt  (size_t);
		//T&     Front();
		//T&     Back();		
		
		//void		Assign();
		void		PushBack(const T&);
		void        PushBack(T&&);
		//void      PopBack();
		//Iterator	Insert(const Iterator, const T&);
		//Iterator	Erase(const Iterator);
		//void		Swap(Array&);
		void        Clear();
		//Iterator	Emplace();
		//Iterator	EmplaceBack();

	private:		
		size_t max_size    = 0;
		size_t capacity    = 0;
		size_t size        = 0;
		size_t granularity = 10;
		T*     data        = nullptr;		
	};

	template <typename T>
	inline Array<T>::Array()
		: max_size(0), capacity(0), size(0), granularity(10), data(nullptr) {}

	template <typename T>
	inline Array<T>::Array(const Array<T>& i_array)
	{
		if (!this->Empty())
		{
			this->Clear();
		}
		this->max_size = i_array.MaxSize();
		this->capacity = i_array.Capacity();
		this->size     = i_array.Size();
		this->data     = reinterpret_cast<T*>(AllocMemory(max_size * sizeof(T)));
		for (size_t i = 0; i < size; i++)
		{
			this->At(i) = i_array.At(i);
		}
	}

	template <typename T>
	inline Array<T>::~Array()
	{	
		for (auto it = this->Begin(); it != this->End(); ++it)
		{
			(*it).~T();
		}
		if(data)
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
		this->capacity = i_array.Capacity();
		this->size     = i_array.Size();
		this->data = reinterpret_cast<T*>(AllocMemory(max_size * sizeof(T)));
		for (size_t i = 0; i < size; i++)
		{
			this->At(i) = i_array.At(i);
		}		

		return *this;
	}

	template <typename T>
	inline Array<T>& Array<T>::Convert(std::initializer_list<T> i_list)
	{
		for (auto it = i_list.begin(); it != i_list.end(); ++it)
		{
			this->PushBack(*it);
		}

		return *this;
	}

	template <typename T>
	inline void Array<T>::Resize(size_t i_resize)
	{
		if (max_size == 0 || !data)
		{
			data = reinterpret_cast<T*>(AllocMemory(i_resize * sizeof(T)));
			max_size = i_resize;
			memset(static_cast<void*>(&data[size]), 0, (i_resize - size) * sizeof(T));				
			size = i_resize;
			return;
		}
		
		if (i_resize > max_size)
		{
			data = reinterpret_cast<T*>(ReallocMemory(reinterpret_cast<void*>(data), i_resize * sizeof(T)));
			max_size = i_resize;
			memset(static_cast<void*>(&data[size]), 0, (i_resize - size) * sizeof(T));
		}

		for (size_t i = size; i < i_resize; i++)
		{			
			data[i] = T();
		}
		size = i_resize;
	}

	template <typename T>
	inline bool Array<T>::Empty()
	{
		if (max_size == 0 || size == 0)		
			return true;		
		return false;
	}

	template <typename T>
	inline T& Array<T>::operator[](size_t i_size) const
	{
		if (i_size >= size || !data)	
			DEBUG_ASSERT(false);
		return data[i_size];
	}

	template <typename T>
	inline T& Array<T>::At(size_t i_size) const
	{
		if (i_size >= size || !data)		
			DEBUG_ASSERT(false);		
		return data[i_size];
	}

	template <typename T>
	inline T& Array<T>::UnsafeAt(size_t i_size)
	{
		if (i_size >= max_size || !data)
			DEBUG_ASSERT(false);
		return data[i_size];
	}

	template <typename T>
	inline void Array<T>::PushBack(const T& i_data)
	{		
		if (max_size == 0 || !data)
		{			
			data = reinterpret_cast<T*>(AllocMemory(granularity * sizeof(T)));			
			max_size += granularity;			
			data[size] = T();
			data[size] = i_data;
			size++;

			return;
		}

		if (size >= max_size)
		{
			data = reinterpret_cast<T*>(ReallocMemory(reinterpret_cast<void*>(data), (max_size + granularity) * sizeof(T)));
			max_size += granularity;						
			data[size] = T();
			data[size] = i_data;
			size++;

			return;
		}
		
		data[size] = T();
		data[size] = i_data;
		size++;
	}

	template <typename T>
	inline void Array<T>::PushBack(T&& i_data)
	{
		if (max_size == 0 || !data)
		{
			data = reinterpret_cast<T*>(AllocMemory(granularity * sizeof(T)));
			max_size += granularity;						
			data[size] = std::move(i_data);
			size++;

			return;
		}

		if (size >= max_size)
		{
			data = reinterpret_cast<T*>(ReallocMemory(reinterpret_cast<void*>(data), (max_size + granularity) * sizeof(T)));
			max_size += granularity;						
			data[size] = std::move(i_data);
			size++;

			return;
		}
		
		data[size] = std::move(i_data);		
		size++;
	}

	template <typename T>
	inline void Array<T>::Clear()
	{
		if (!data)		
			return;
		
		for (auto it = this->Begin(); it != this->End(); ++it)
		{
			(*it).~T();
		}

		FreeMemory(data);
		max_size = 0;
		size = 0;
		data = nullptr;		
	}

	namespace Utility
	{
		template <typename T>
		inline size_t Distance(typename Array<T>::Iterator i_first, typename Array<T>::Iterator i_last)
		{
			int distance = static_cast<int>(i_last.GetIndex() - i_first.GetIndex());
			return (i_last.GetIndex() - i_first.GetIndex() >= 0) ? distance : -distance;			
		}
	}

#endif
}

