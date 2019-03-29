#pragma once
#include "DebugLog.h"

#include <assert.h>
#include <stdint.h>

namespace Engine {

	typedef uint64_t	ref_counter_t;

	struct ReferenceCounters
	{
		ref_counter_t		OwnerReferences;
		ref_counter_t		ObserverReferences;

		ReferenceCounters(ref_counter_t i_InitialOwners, ref_counter_t i_InitialObservers) :
			OwnerReferences(i_InitialOwners),
			ObserverReferences(i_InitialObservers)
		{ }
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
		ReferenceCounters * ref;
		T * data;

	public:
		// Default Constructor
		OwningPointer() {
			ref = nullptr;
			data = nullptr;
		};

		// Standard Constructor
		explicit OwningPointer(T * i_ptr) {
			data = i_ptr;
			ref = new ReferenceCounters(1,0);
		};

		// Copy Constructor
		OwningPointer(const OwningPointer & i_other) {
			this->data = i_other.data;
			this->ref = i_other.ref;
			i_other.ref->OwnerReferences++;
		};

		// Copy Constructor between polymorphic types
		// OwningPointer<Base> BasePtr( new Base() );
		// OwningPointer<Default> DefaultPtr = BasePtr; <-- Used here
		template<class U>
		OwningPointer(const OwningPointer<U> & i_other) {
			this->data = i_other.data;
			this->ref = i_other.ref;
			i_other.ref->OwnerReferences++;
		};

		// Copy Constructor - For creating an Owning Pointer from an Observing Pointer
		// Will create a OwningPointer that points to nullptr if the referenced object has been destroyet (no more Owners left, just Observers)
		OwningPointer(const ObservingPointer<T> & i_other) {
			if (i_other.ref->OwnerReferences != 0) {
				ref = i_other.ref;
				data = i_other.data;
				ref->OwnerReferences++;
			}
		};

		// Copy Constructor - For creating an Owning Pointer of a polymorphic type from an Observing Pointer
		template<class U>
		OwningPointer(const ObservingPointer<U> & i_other) {
			if (i_other.ref->OwnerReferences != 0) {
				ref = i_other.ref;
				data = i_other.data;
				ref->OwnerReferences++;
			}
		};

		// Assignment Operator
		OwningPointer & operator=(const OwningPointer & i_other) {
			if (this == &i_other)
				return *this;
			else {
				if (ref != nullptr) {
					ref->OwnerReferences--;
					if (ref->ObserverReferences == 0 && ref->OwnerReferences == 0) {
						delete ref;
						delete data;
					}
				}
				this->ref = i_other.ref;
				this->data = i_other.data;
				ref->OwnerReferences++;
				return *this;
			}
		};

		// Assignment Operator between polymorphic types
		template<class U>
		OwningPointer & operator=(const OwningPointer<U> & i_other) {
			if (this == &i_other)
				return *this;
			else {
				if (ref != nullptr) {
					ref->OwnerReferences--;
					if (ref->ObserverReferences == 0 && ref->OwnerReferences == 0) {
						delete ref;
						delete data;
					}
				}
				this->ref = i_other.ref;
				this->data = i_other.data;
				ref->OwnerReferences++;
				return *this;
			}
		};

		// Assignment Operator - Reassigns an existing Owning Pointer from an existing Observing Pointer
		OwningPointer & operator=(const ObservingPointer<T> & i_other) {
			if (ref = nullptr) {
				ref->OwnerReferences--;
				if (ref->ObserverReferences == 0 && ref->OwnerReferences == 0) {
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
		OwningPointer & operator=(const ObservingPointer<U> & i_other) {
			if (ref = nullptr)
				ref->OwnerReferences--;
			ref = i_other.ref;
			data = i_other.data;
			ref->OwnerReferences++;
		};

		// Assignment Operator - null specific
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = nullptr;
		// Don't really need to implement this. If it's not here it'll go through OwningPointer & operator=( OwningPointer & i_other);
		OwningPointer & operator=(std::nullptr_t i_null) {
			DEBUG_PRINT("The OwningPointer is about to assigned nullptr");
			assert(false);
		};

		// Assignment Operator - Assigning directly from an existing pointer
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = new Base();
		OwningPointer & operator=(T * i_ptr) {
			data = i_ptr;
			ref = new ReferenceCounters(1, 0);
			return *this;
		};

		// Destructor
		~OwningPointer() {
			ref->OwnerReferences--;
			if (ref->OwnerReferences == 0) {
				if (ref->ObserverReferences == 0) {
					delete ref;
					delete data;
					ref = nullptr;
					data = nullptr;
				}
			}
		};

		// Equality comparison operator
		inline bool operator==(const OwningPointer<T> & i_other) const {
			if (data == i_other.data) 
				return true;
			else 
				return false;
		};

		// Equality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator==(const OwningPointer<U> & i_other) const {
			if (data == i_other.data) 
				return true;
			else 
				return false;
		};

		// Equality comparison operator for comparing to an Observing Pointer
		inline bool operator==(const ObservingPointer<T> & i_other) const {
			if (data == i_other.data)
				return true;
			else
				return false;
		};

		// Equality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator==(const ObservingPointer<U> & i_other) const {
			if (data == i_other.data)
				return true;
			else
				return false;
		};

		// Inequality comparison operator
		inline bool operator!=(const OwningPointer<T> & i_other) const {
			return !(operator==(i_other));
		};

		// Inequality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator!=(const OwningPointer<U> & i_other) const {
			return !(operator==(i_other));
		};

		// Inequality comparison operator for comparing to an Observing Pointer
		inline bool operator!=(const ObservingPointer<T> & i_other) const {
			return !(operator==(i_other));
		};

		// Inequality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator!=(const ObservingPointer<U> & i_other) const {
			return !(operator==(i_other));
		};

		// Equality comparison operator directly to pointer 
		inline bool operator==(T * i_ptr) const {
			if (data == i_ptr) 
				return true;
			else 
				return false;
		};

		// Equality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator==(U * i_ptr) const {
			if (data == i_ptr)
				return true;
			else
				return false;
		};

		// Equality comparison operator for nullptr
		inline bool operator==(std::nullptr_t nullp) const {
			if (data == nullptr)
				return true;
			else
				return false;
		};

		// Inequality comparison operator directly to pointer 
		inline bool operator!=(T * i_ptr) const {
			return !(operator==(T * i_ptr));
		};

		// Inequality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator!=(U * i_ptr) const {
			return !(operator==(U * i_ptr));
		};

		// Inequality comparison operator for nullptr
		inline bool operator!=(std::nullptr_t nullp) const {
			return !(operator==(nullp));
		};

		// bool operator - shorthand for != nullptr;
		inline operator bool() const {
			if (data == nullptr)
				return false;
			else
				return true;
		};

		// member access operator
		T * operator->() {
			return data;
		};

		// indirection operator
		T & operator*() {
			assert(data != nullptr);
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
		ReferenceCounters * ref;
		T * data;

	public:
		// Default Constructor
		ObservingPointer() {
			ref = nullptr;
			data = nullptr;
		};

		// Copy Constructors
		ObservingPointer(const ObservingPointer & i_owner) {
			assert(i_owner.ref);
			if (i_owner.ref->OwnerReferences != 0) {
				ref = i_owner.ref;
				data = i_owner.data;
				ref->ObserverReferences++;
			}
			else 
				assert(false);
		};

		template<class U>
		ObservingPointer(const OwningPointer<U> & i_owner) {
			ref = i_owner.ref;
			data = i_owner.data;
			ref->ObserverReferences++;
		};

		template<class U>
		ObservingPointer(const ObservingPointer<U> & i_owner) {
			if (i_owner.ref->OwnerReferences != 0){
				ref = i_owner.ref;
				data = i_owner.data;
				ref->ObserverReferences++;
			}
			else
				assert(false);
		};

		// Destructor
		~ObservingPointer() {
			ref->ObserverReferences--;
			if (ref->ObserverReferences == 0) {
				if (ref->OwnerReferences == 0) {
					delete ref;
					delete data;
					ref = nullptr;
					data = nullptr;
				}
			}
		};

		// Assignment operators
		ObservingPointer & operator=(const ObservingPointer & i_other) {
			if (this == &i_other) {
				return *this;
			}
			else {
				if (ref != nullptr) {
					ref->ObserverReferences--;
					if (ref->OwnerReferences == 0 && ref->ObserverReferences == 0) {
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
		ObservingPointer & operator=(const ObservingPointer<U> & i_other) {
			if (this == &i_other) {
				return *this;
			}
			else {
				if (ref != nullptr) {
					ref->ObserverReferences--;
					if (ref->OwnerReferences == 0 && ref->ObserverReferences == 0) {
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
		inline ObservingPointer & operator=(const OwningPointer<U> & i_other) {
			if (ref != nullptr)
				ref->ObserverReferences--;
			ref = i_other.ref;
			data = i_other.data;
			ref->ObserverReferences++;
			return *this;
		};

		ObservingPointer<T> & operator=(std::nullptr_t i_null) {
			if (ref != nullptr) {
				ref->ObserverReferences--;
				if (ref->OwnerReferences == 0 && ref->ObserverReferences == 0) {
					delete ref;
					delete data;
				}
			}
			ref = nullptr;
			data = nullptr;
			return *this;
		};

		// Create an Owning Pointer from this Observering Pointer
		inline OwningPointer<T> AcquireOwnership() {
			OwningPointer<T> tmp = OwningPointer<T>();
			if (ref->OwnerReferences != 0) {
				tmp.data = this->data;
				tmp.ref = this->ref;
				ref->OwnerReferences++;
			}
			return tmp;
		};

		// Equality comparison operators
		inline bool operator==(const OwningPointer<T> & i_other) const {
			if (ref == i_other.ref)
				return true;
			else
				return false;
		};

		template<class U>
		inline bool operator==(const OwningPointer<U> & i_other) const {
			if (ref == i_other.ref)
				return true;
			else
				return false;
		};

		inline bool operator==(const ObservingPointer<T> & i_other) const {
			if (ref == i_other.ref)
				return true;
			else
				return false;
		};

		template<class U>
		inline bool operator==(const ObservingPointer<U> & i_other) const {
			if (ref == i_other.ref)
				return true;
			else
				return false;
		};

		inline bool operator==(T * i_ptr) const {
			if (ref->OwnerReferences != 0) {
				if (data == i_ptr)
					return true;
				else
					return false;
			}
			else
				return false;
		};

		template<class U>
		inline bool operator==(U * i_ptr) const {
			if (ref->OwnerReferences != 0) {
				if (data == i_ptr)
					return true;
				else
					return false;
			}
			else
				return false;
		};

		// Inequality comparison operators
		inline bool operator!=(const OwningPointer<T> & i_other) const {
			return !(operator==(i_other));
		};

		template<class U>
		inline bool operator!=(const OwningPointer<U> & i_other) const {
			return !(operator==(i_other));
		};

		inline bool operator!=(const ObservingPointer<T> & i_other) const {
			return !(operator==(i_other));
		};

		template<class U>
		inline bool operator!=(const ObservingPointer<U> & i_other) const {
			return !(operator==(i_other));
		};

		inline bool operator!=(T * i_ptr) const {
			return !(operator==(T * i_ptr));
		};

		template<class U>
		inline bool operator!=(U * i_ptr) const {
			return !(operator==(U * i_ptr));
		};

		// bool operator
		inline operator bool() const {
			if (data == nullptr)
				return false;
			else
				return true;
		};

		// member access operator
		T * operator->() {
			if (ref->OwnerReferences != 0) {
				return data;
			}
			else
				assert(false);
		};

		// indirection operator
		T & operator*() {
			if (ref->OwnerReferences != 0) {
				assert(data != nullptr);
				return *data;
			}
			else
				assert(false);
		};
	};

} // namespace Engine