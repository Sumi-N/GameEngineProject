
namespace Tempest
{
#ifndef USE_STANDARD_ARRAY

	template <typename T>
	inline bool Array<T>::Iterator::operator==(const Array<T>::Iterator& i_iterator)
	{
		if (!i_iterator.GetArray())
		{
			return !array ? true : false;
		}

		if (index == i_iterator.GetIndex() && array == i_iterator.GetArray())
		{
			return true;
		}

		return false;
	}

	template <typename T>
	inline bool Array<T>::Iterator::operator!=(const Array<T>::Iterator& i_iterator)
	{
		if (!i_iterator.GetArray())
		{
			return index >= array->Size() ? false : true;
		}

		if (index != i_iterator.GetIndex() && array != i_iterator.GetArray())
		{
			return true;
		}

		return false;
	}

	template <typename T>
	inline Array<T>::Array()
		: capacity(0), size(0), granularity(InitialGranularity), data(nullptr)
	{}

	template <typename T>
	inline Array<T>::Array(const int i_size)
		: capacity(0), size(0), granularity(InitialGranularity), data(nullptr)
	{
		Resize(i_size);
	}

	template <typename T>
	inline Array<T>::Array(const Array<T>& i_array)
	{
		if (!Empty())
		{
			Clear();
		}
		capacity = i_array.Capacity();
		granularity = i_array.Granularity();
		size = i_array.Size();
		data = reinterpret_cast<T*>(AllocMemory(capacity * sizeof(T)));
		memset(static_cast<void*>(&data[0]), 0, (capacity) * sizeof(T));
		for (size_t i = 0; i < size; i++)
		{
			At(i) = std::move(T());
			At(i) = i_array.At(i);
		}
	}

	template <typename T>
	inline Array<T>::~Array()
	{
		for (auto it = Begin(); it != End(); ++it)
		{
			(*it).~T();
		}
		if (data)
			FreeMemory(data);
	}

	template <typename T>
	inline Array<T>& Array<T>::operator= (const Array<T>& i_array)
	{
		if (!Empty())
		{
			Clear();
		}
		capacity = i_array.Capacity();
		granularity = i_array.Granularity();
		size = i_array.Size();
		data = reinterpret_cast<T*>(AllocMemory(capacity * sizeof(T)));
		memset(static_cast<void*>(&data[0]), 0, (capacity) * sizeof(T));
		for (size_t i = 0; i < size; i++)
		{
			At(i) = std::move(T());
			At(i) = i_array.At(i);
		}

		return *this;
	}

	template <typename T>
	inline Array<T>& Array<T>::Convert(std::initializer_list<T> i_list)
	{
		for (auto it = i_list.begin(); it != i_list.end(); ++it)
		{
			PushBack(*it);
		}

		return *this;
	}

	template <typename T>
	inline void Array<T>::Resize(size_t i_resize)
	{
		if (capacity == 0 || !data)
		{
			data = reinterpret_cast<T*>(AllocMemory(i_resize * sizeof(T)));
			capacity = i_resize;
			memset(static_cast<void*>(&data[size]), 0, (i_resize - size) * sizeof(T));

			for (size_t i = 0; i < i_resize; i++)
			{
				data[i] = std::move(T());
			}
			size = i_resize;

			return;
		}

		if (i_resize > capacity)
		{
			data = reinterpret_cast<T*>(ReallocMemory(reinterpret_cast<void*>(data), i_resize * sizeof(T)));
			capacity = i_resize;
			memset(static_cast<void*>(&data[size]), 0, (i_resize - size) * sizeof(T));
		}

		for (size_t i = size; i < i_resize; i++)
		{
			data[i] = std::move(T());
		}
		size = i_resize;
	}

	template <typename T>
	inline bool Array<T>::Empty()
	{
		if (capacity == 0 || size == 0)
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
		if (i_size >= capacity || !data)
			DEBUG_ASSERT(false);
		return data[i_size];
	}

	template <typename T>
	inline void Array<T>::PushBack(const T& i_data)
	{
		if (capacity == 0 || !data)
		{
			data = reinterpret_cast<T*>(AllocMemory(granularity * sizeof(T)));
			capacity += granularity;
			memset(static_cast<void*>(&data[size]), 0, (capacity) * sizeof(T));
			data[size] = std::move(T());
			data[size] = i_data;
			size++;

			return;
		}

		if (size >= capacity)
		{
			data = reinterpret_cast<T*>(ReallocMemory(reinterpret_cast<void*>(data), (capacity + granularity) * sizeof(T)));
			capacity += granularity;
			memset(static_cast<void*>(&data[size]), 0, (capacity - size) * sizeof(T));
			data[size] = std::move(T());
			data[size] = i_data;
			size++;

			return;
		}

		data[size] = std::move(T());
		data[size] = i_data;
		size++;
	}

	template <typename T>
	inline void Array<T>::PushBack(T&& i_data)
	{
		if (capacity == 0 || !data)
		{
			data = reinterpret_cast<T*>(AllocMemory(granularity * sizeof(T)));
			capacity += granularity;
			data[size] = std::move(i_data);
			size++;

			return;
		}

		if (size >= capacity)
		{
			data = reinterpret_cast<T*>(ReallocMemory(reinterpret_cast<void*>(data), (capacity + granularity) * sizeof(T)));
			capacity += granularity;
			data[size] = std::move(i_data);
			size++;

			return;
		}

		data[size] = std::move(i_data);
		size++;
	}

	template <typename T>
	inline void Array<T>::PopBack()
	{
		if (size <= 0)
		{
			DEBUG_ASSERT(false);
		}
		size--;
	}

	template <typename T>
	inline typename Array<T>::Iterator Array<T>::Insert(typename const Array<T>::Iterator i_iterator, const T& i_data)
	{
		if (i_iterator.GetArray() != this)
		{
			DEBUG_ASSERT(false);
		}

		if (capacity == size)
		{
			PushBack(T{});
			memmove(static_cast<void*>(&data[i_iterator.GetIndex() + 1]), static_cast<void*>(&data[i_iterator.GetIndex()]), sizeof(T) * (this->size - i_iterator.GetIndex()));
			T& new_inserted = At(i_iterator.GetIndex());
			new_inserted = i_data;
			size++;
		}
		else
		{
			memmove(static_cast<void*>(&data[i_iterator.GetIndex() + 1]), static_cast<void*>(&data[i_iterator.GetIndex()]), sizeof(T) * (this->size - i_iterator.GetIndex()));
			T& new_inserted = At(i_iterator.GetIndex());
			new_inserted = i_data;
			size++;
		}

		return i_iterator;
	}

	template <typename T>
	inline void Array<T>::Clear()
	{
		if (!data)
			return;

		for (auto it = Begin(); it != End(); ++it)
		{
			(*it).~T();
		}

		FreeMemory(data);
		capacity = 0;
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

#endif // !USE_STANDARD_ARRAY

}