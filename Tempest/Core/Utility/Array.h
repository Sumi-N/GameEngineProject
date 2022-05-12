#pragma once

#include "Define.h"

namespace Tempest
{
#ifndef USE_STANDARD_ARRAY
	template <typename T>
	class Array
	{
	public:	

		class Iterator
		{
		public:
			Iterator()                                     : array(nullptr), index(0)       {}
			Iterator(const Array* i_array, size_t i_index) : array(i_array), index(i_index) {}

			Iterator  operator+ (int t)               {Iterator iterator = *this; iterator.index += t; return iterator; }
			Iterator  operator- (int t)               {Iterator iterator = *this; iterator.index -= t; return iterator; }
			Iterator& operator= (Iterator i_iterator) {this->array = i_iterator->array; this->index = i_iterator->index; return this; }
			Iterator& operator++()                    {index++; return *this; }
			Iterator  operator++(int t)               {Iterator iterator = *this; index++; return iterator; }
			T*        operator->()                    {return &(array->At(index)); }
			T&        operator* ()                    {return array->At(index); }

			size_t       GetIndex() const {return index; }
			const Array* GetArray() const {return array; }
			T*           Get()      const {return &(array->At(index)); }

			bool operator==(const Iterator& i_iterator);
			bool operator!=(const Iterator& i_iterator);

		private:
			const Array* array;
			size_t index;
		};

		friend class Iterator;

		Array();
		explicit Array(const int i_size);
		Array(const Array& i_array);
		~Array();		
		
		Array& operator=(Array);
		Array& Convert(std::initializer_list<T>);

		// This function is for ranged loop
		// Lowercase begin and end is required for ranged loop
		Iterator Begin () {return Iterator(this, 0); }		
		Iterator begin () {return Iterator(this, 0); }
		Iterator End   () {return Iterator(); }
		Iterator end   () {return Iterator(); }

		size_t		Size       () const {return this->size; }		
		size_t		Capacity   () const {return this->capacity; }
		size_t      Granularity() const {return this->granularity; }
		T*          Data       () const {return this->data; };

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
		void        PopBack();
		Iterator	Insert(const Iterator, const T&);
		//Iterator	Erase(const Iterator);
		//void		Swap(Array&);
		void        Clear();
		//Iterator	Emplace();
		//Iterator	EmplaceBack();

	private:

		static constexpr size_t InitialGranularity = 4;

		size_t capacity   { 0 };
		size_t size       { 0 };
		size_t granularity{ InitialGranularity };
		T*     data       {nullptr};
	};
#else
	template <typename T>
	class Array
	{
	public:
		Array() = default;
		~Array() = default;

		typename std::vector<T>::iterator Begin ()   {return vector.begin(); }
		typename std::vector<T>::iterator End   ()   {return vector.end(); }
		typename std::vector<T>::iterator Insert(typename std::vector<T>::iterator i_itr, T& i_t){return vector.insert(i_itr, i_t); }

		const T& operator[] (const size_t i_size) const {return vector.at(i_size); };
		      T& operator[] (size_t i_size)             {return vector.at(i_size); };

		T*     Data  ()       {return vector.data(); }
		bool   Empty () const {return vector.empty(); }		
		size_t Size  () const {return vector.size(); }

		void   Resize  (size_t i_size) {vector.resize(i_size); }
		void   PushBack(const T& i_t)  {vector.push_back(i_t); }
		void   Clear   ()              {vector.clear(); }

		void   Convert(std::initializer_list<T> i_list) {vector = i_list; }

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
#endif
}

#include "Array.inl"