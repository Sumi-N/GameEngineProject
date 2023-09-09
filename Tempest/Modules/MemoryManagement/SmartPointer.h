#pragma once
#include "Define.h"

namespace Tempest
{

	struct ReferenceCounters
	{
		uint8_t		OwnerReferences;
		uint8_t		ObserverReferences;

		ReferenceCounters(uint8_t i_InitialOwners, uint8_t i_InitialObservers)
			:OwnerReferences(i_InitialOwners), ObserverReferences(i_InitialObservers) {}
	};

	// forward declare Observing pointer as we'll refer to it in OwningPointer definition
	template<class T>
	class ObservingPointer;

	template<class T>
	class OwningPointer
	{
		template<class U>
		friend class ObservingPointer;

		template<class U>
		friend class OwningPointer;

	private:
		ReferenceCounters* ref;
		T* data;

	public:

		static OwningPointer<T>& Create(OwningPointer<T>& i_pointer)
		{
			DEBUG_ASSERT(i_pointer == nullptr);
			T* obj = new T();
			i_pointer = obj;
			return i_pointer;
		}

		// Default Constructor
		OwningPointer() : ref(nullptr), data(nullptr) {};

		// Standard Constructor
		explicit OwningPointer(T* i_ptr)
		{
			if (i_ptr == nullptr)
			{
				ref = nullptr;
				data = nullptr;
				return;
			}
			ref = new ReferenceCounters(1, 0);
			data = i_ptr;
		};

		// Copy Constructor
		OwningPointer(const OwningPointer& i_other)
		{
			// If the owning pointer didn't reference itself then increment reference
			if (i_other != *this)
			{
				ref = i_other.ref;
				data = i_other.data;
				i_other.ref->OwnerReferences++;
			}
		};

		// Copy Constructor between polymorphic types
		// OwningPointer<Base> BasePtr( new Base() );
		// OwningPointer<Default> DefaultPtr = BasePtr; <-- Used here
		template<class U>
		OwningPointer(const OwningPointer<U>& i_other)
		{
			if (i_other != *this)
			{
				ref = i_other.ref;
				data = reinterpret_cast<T*>(i_other.data);
				i_other.ref->OwnerReferences++;
			}
		};

		// Copy Constructor - For creating an Owning Pointer from an Observing Pointer
		// Will create a OwningPointer that points to nullptr if the referenced object has been destroyed yet (no more Owners left, just Observers)
		OwningPointer(const ObservingPointer<T>& i_other)
		{
			if (i_other.ref->OwnerReferences != 0)
			{
				ref = i_other.ref;
				data = i_other.data;
				ref->OwnerReferences++;
			}
		};

		// Copy Constructor - For creating an Owning Pointer of a polymorphic type from an Observing Pointer
		template<class U>
		OwningPointer(const ObservingPointer<U>& i_other)
		{
			if (i_other.ref->OwnerReferences != 0)
			{
				ref = i_other.ref;
				data = reinterpret_cast<T*>(i_other.data);
				ref->OwnerReferences++;
			}
		};

		// Move Constructor
		OwningPointer(OwningPointer<T>&& i_other)
		{
			if (i_other != *this)
			{
				ref = i_other.ref;
				data = i_other.data;
				i_other.ref = nullptr;
				i_other.data = nullptr;
			}
			return;
		}

		// Move Constructor
		template<class U>
		OwningPointer(OwningPointer<U>&& i_other)
		{
			if (i_other != *this)
			{
				ref = i_other.ref;
				data = reinterpret_cast<T*>(i_other.data);
				i_other.ref = nullptr;
				i_other.data = nullptr;
			}
			return;
		}

		// Assignment Operator
		OwningPointer& operator=(const OwningPointer& i_other)
		{
			if (*this == i_other)
			{
				return *this;
			}
			else if (i_other.ref == nullptr)
			{
				if (ref != nullptr)
				{
					ref->ObserverReferences--;
					if (ref->OwnerReferences == 0)
					{
						delete ref;
						delete data;
					}
				}
				ref = nullptr;
				data = nullptr;
				return *this;
			}
			else
			{
				if (ref != nullptr)
				{
					ref->OwnerReferences--;
					if (ref->OwnerReferences == 0)
					{
						delete ref;
						delete data;
					}
				}

				ref = i_other.ref;
				data = i_other.data;
				ref->OwnerReferences++;
				return *this;
			}
		};

		// Assignment Operator between polymorphic types
		template<class U>
		OwningPointer& operator=(const OwningPointer<U>& i_other)
		{
			if (*this == i_other)
				return *this;
			else
			{
				if (ref != nullptr)
				{
					ref->OwnerReferences--;
					if (ref->OwnerReferences == 0)
					{
						delete ref;
						delete data;
					}
				}
				ref = i_other.ref;
				data = reinterpret_cast<T*>(i_other.data);
				ref->OwnerReferences++;
				return *this;
			}
		};

		// Assignment Operator - Reassigns an existing Owning Pointer from an existing Observing Pointer
		OwningPointer& operator=(const ObservingPointer<T>& i_other)
		{
			if (ref)
			{
				ref->OwnerReferences--;
				if (ref->OwnerReferences == 0)
				{
					delete ref;
					delete data;
				}
			}
			this->ref = i_other.ref;
			this->data = i_other.data;
			ref->OwnerReferences++;
			return *this;
		};

		// Assignment Operator - Reassigns an existing Owning Pointer from an existing Observing Pointer of a polymorphic type
		template<class U>
		OwningPointer& operator=(const ObservingPointer<U>& i_other)
		{
			if (ref)
			{
				ref->OwnerReferences--;
				if (ref->OwnerReferences == 0)
				{
					delete ref;
					delete data;
				}
			}
			ref = i_other.ref;
			data = reinterpret_cast<T*>(i_other.data);
			ref->OwnerReferences++;
			return *this;
		};

		// Assignment Operator - null specific
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = nullptr;
		// Don't really need to implement this. If it's not here it'll go through OwningPointer & operator=( OwningPointer & i_other);
		OwningPointer& operator=(std::nullptr_t i_null)
		{
			if (ref != nullptr)
			{
				ref->ObserverReferences--;
				if (ref->OwnerReferences == 0)
				{
					delete ref;
					delete data;
				}
			}
			ref = nullptr;
			data = nullptr;
			return *this;
		};

		// Assignment Operator - Assigning directly from an existing pointer
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = new Base();
		OwningPointer& operator=(T* i_ptr)
		{
			if (ref)
			{
				ref->OwnerReferences--;
				if (ref->OwnerReferences == 0)
				{
					delete ref;
					delete data;
				}
			}
			ref = new ReferenceCounters(1, 0);
			data = i_ptr;
			return *this;
		};

		// Destructor
		~OwningPointer()
		{
			// Skip this process if this owning pointer is a global variable without initialization
			if (ref)
			{
				ref->OwnerReferences--;
				if (ref->OwnerReferences == 0)
				{
					delete ref;
					delete data;
					ref = nullptr;
					data = nullptr;
				}
			}
		};

		// Equality comparison operator
		inline bool operator==(const OwningPointer<T>& i_other) const
		{
			return data == i_other.data;
		};

		// Equality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator==(const OwningPointer<U>& i_other) const
		{
			return data == reinterpret_cast<T*>(i_other.data);
		};

		// Equality comparison operator for comparing to an Observing Pointer
		inline bool operator==(const ObservingPointer<T>& i_other) const
		{
			return data == i_other.data;
		};

		// Equality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator==(const ObservingPointer<U>& i_other) const
		{
			return data == reinterpret_cast<T*>(i_other.data);
		};

		// Inequality comparison operator
		inline bool operator!=(const OwningPointer<T>& i_other) const
		{
			return !(data == i_other.data);
		};

		// Inequality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator!=(const OwningPointer<U>& i_other) const
		{
			return !(data == reinterpret_cast<T*>(i_other.data));
		};

		// Inequality comparison operator for comparing to an Observing Pointer
		inline bool operator!=(const ObservingPointer<T>& i_other) const
		{
			return !(data == i_other.data);
		};

		// Inequality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator!=(const ObservingPointer<U>& i_other) const
		{
			return !(data == reinterpret_cast<T*>(i_other.data));
		};

		// Equality comparison operator directly to pointer
		inline bool operator==(T* i_ptr) const
		{
			return data == i_ptr;
		};

		// Equality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator==(U* i_ptr) const
		{
			return data == i_ptr;
		};

		// Equality comparison operator for nullptr
		inline bool operator==(std::nullptr_t nullp) const
		{
			return data ? false : true;
		};

		// Inequality comparison operator directly to pointer
		inline bool operator!=(T* i_ptr) const
		{
			return !(data == i_ptr);
		};

		// Inequality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator!=(U* i_ptr) const
		{
			return !(data == i_ptr);
		};

		// Inequality comparison operator for nullptr
		inline bool operator!=(std::nullptr_t nullp) const
		{
			return data ? true : false;
		};

		// bool operator - shorthand for != nullptr;
		inline operator bool() const
		{
			return data ? true : false;
		};

		// member access operator
		T* operator->()
		{
			return data;
		};

		// indirection operator
		T& operator*()
		{
			DEBUG_ASSERT(data != nullptr);
			return *data;
		};

	};

	template<class T>
	class ObservingPointer
	{
		template<class U>
		friend class OwningPointer;
		template<class U>
		friend class ObservingPointer;

	private:
		ReferenceCounters* ref;
		T* data;

	public:
		// Default Constructor
		ObservingPointer() : ref(nullptr), data(nullptr) {};

		// Copy Constructors
		ObservingPointer(const ObservingPointer& i_owner)
		{
			DEBUG_ASSERT(i_owner.ref);
			if (i_owner.ref->OwnerReferences != 0)
			{
				ref = i_owner.ref;
				data = i_owner.data;
				ref->ObserverReferences++;
			}
			else
				DEBUG_ASSERT(false);
		};

		template<class U>
		ObservingPointer(const OwningPointer<U>& i_owner)
		{
			ref = i_owner.ref;
			data = reinterpret_cast<T*>(i_owner.data);
			ref->ObserverReferences++;
		};

		template<class U>
		ObservingPointer(const ObservingPointer<U>& i_owner)
		{
			if (i_owner.ref->OwnerReferences != 0)
			{
				ref = i_owner.ref;
				data = reinterpret_cast<T*>(i_owner.data);
				ref->ObserverReferences++;
			}
			else
				DEBUG_ASSERT(false);
		};

		// Destructor
		~ObservingPointer()
		{
			if (ref)
			{
				ref->ObserverReferences--;
			}
		};

		// Assignment operators
		ObservingPointer& operator=(const ObservingPointer<T>& i_other)
		{
			if (*this == i_other)
			{
				return *this;
			}
			else
			{
				if (ref != nullptr)
				{
					ref->ObserverReferences--;
					if (ref->OwnerReferences == 0)
					{
						delete ref;
						delete data;
					}
				}
				ref = i_other.ref;
				data = i_other.data;
				ref->ObserverReferences++;
				return *this;
			}
		};

		template<class U>
		ObservingPointer& operator=(const ObservingPointer<U>& i_other)
		{
			if (*this == i_other)
			{
				return *this;
			}
			else
			{
				if (ref != nullptr)
				{
					ref->ObserverReferences--;
					if (ref->OwnerReferences == 0)
					{
						delete ref;
						delete data;
					}
				}
				ref = i_other.ref;
				data = reinterpret_cast<T*>(i_other.data);
				ref->ObserverReferences++;
				return *this;
			}
		};

		template<class U>
		inline ObservingPointer& operator=(const OwningPointer<U>& i_other)
		{
			if (ref != nullptr)
			{
				ref->ObserverReferences--;
				if (ref->OwnerReferences == 0)
				{
					delete ref;
					delete data;
				}
			}
			ref = i_other.ref;
			data = reinterpret_cast<T*>(i_other.data);
			ref->ObserverReferences++;
			return *this;
		};

		ObservingPointer<T>& operator=(std::nullptr_t i_null)
		{
			if (ref != nullptr)
			{
				ref->ObserverReferences--;
				if (ref->OwnerReferences == 0)
				{
					delete ref;
					delete data;
				}
			}
			ref = nullptr;
			data = nullptr;
			return *this;
		};

		// Create an Owning Pointer from this Observing Pointer
		inline OwningPointer<T> AcquireOwnership()
		{
			OwningPointer<T> tmp = OwningPointer<T>();
			if (ref->OwnerReferences != 0)
			{
				tmp.data = this->data;
				tmp.ref = this->ref;
				ref->OwnerReferences++;
			}
			return tmp;
		};

		// Equality comparison operators
		inline bool operator==(const OwningPointer<T>& i_other) const
		{
			return ref == i_other.ref;
		};

		template<class U>
		inline bool operator==(const OwningPointer<U>& i_other) const
		{
			return ref == i_other.ref;
		};

		inline bool operator==(const ObservingPointer<T>& i_other) const
		{
			return ref == i_other.ref;
		};

		template<class U>
		inline bool operator==(const ObservingPointer<U>& i_other) const
		{
			return ref == i_other.ref;
		};

		inline bool operator==(T* i_ptr) const
		{
			if (ref->OwnerReferences != 0)
			{
				return data == i_ptr;
			}
			else
				return false;
		};

		template<class U>
		inline bool operator==(U* i_ptr) const
		{
			if (ref->OwnerReferences != 0)
			{
				return data == i_ptr;
			}
			else
				return false;
		};

		// Inequality comparison operators
		inline bool operator!=(const OwningPointer<T>& i_other) const
		{
			return !(ref == i_other.ref);
		};

		template<class U>
		inline bool operator!=(const OwningPointer<U>& i_other) const
		{
			return !(ref == i_other.ref);
		};

		inline bool operator!=(const ObservingPointer<T>& i_other) const
		{
			return !(ref == i_other.ref);
		};

		template<class U>
		inline bool operator!=(const ObservingPointer<U>& i_other) const
		{
			return !(ref == i_other.ref);
		};

		inline bool operator!=(T* i_ptr) const
		{
			return !(operator==(T * i_ptr));
		};

		template<class U>
		inline bool operator!=(U* i_ptr) const
		{
			return !(operator==(U * i_ptr));
		};

		// bool operator
		inline operator bool() const
		{
			return data ? true : false;
		};

		// member access operator
		T* operator->()
		{
			if (ref->OwnerReferences != 0)
			{
				return data;
			}
			else
			{
				DEBUG_ASSERT(false);
				return nullptr;
			}
		};

		// indirection operator
		T& operator*()
		{
			if (ref->OwnerReferences != 0)
			{
				DEBUG_ASSERT(data != nullptr);
				return *data;
			}
			else
			{
				DEBUG_ASSERT(false);
				return *data;
			}
		};
	};

	template<typename T, typename... U>
	static OwningPointer<T> Create(U&&... args)
	{
		T* obj = new T(std::forward<U>(args)...);
		OwningPointer<T> o_pointer{obj};
		return o_pointer;
	}
}

template<typename T>
using Owner =  Tempest::OwningPointer<T>;

template<typename T>
using Observer = Tempest::ObservingPointer<T>;