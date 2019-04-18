#pragma once
#include <assert.h>
#include <algorithm>
#include <vector>

namespace Engine {
	template<class ... Params> class Delegate {
	public:
		Delegate() :
			pInstance(nullptr),
			pMethodStub(nullptr) {}

		bool operator==(const Delegate & i_other) {
			return (pInstance == i_other.pInstance && pMethodStub == i_other.pMethodStub);
		}

		template <class T, void (T::*TMethod)(Params ...)>
		static Delegate Create(T* i_pInstance) {
			return Delegate(i_pInstance, &method_stub<T, TMethod>);
		}

		operator bool() const {
			return pInstance != nullptr;
		}

		void operator()(Params ... i_Parameters) const {
			assert(pMethodStub);
			return (*pMethodStub)(pInstance, i_Parameters ...);
		}

		void ExecuteIfBound(Params ... i_Parameters) const {
			if (pInstance)
			{
				assert(pMethodStub);
				(*pMethodStub)(pInstance, i_Parameters ...);
			}
		}

	private:
		typedef void(*tMethodStub)(void * i_pInstance, Params ... i_Parameter);

		void * pInstance;
		tMethodStub pMethodStub;

		explicit Delegate(void * i_pInstance, tMethodStub i_pMethodStub) :
			pInstance(i_pInstance),
			pMethodStub(i_pMethodStub)
		{
			assert(pInstance);
			assert(pMethodStub);
		}

		template <class T, void (T::*TMethod)(Params ...)>
		static void method_stub(void * pInstance, Params ... i_Parameters) {
			(static_cast<T*>(pInstance)->*TMethod)(i_Parameters...);
		}

	};

	template<class ... Params>
	class MultiCastDelegate {
	public:
		void AddDelegate(Delegate<Params ...> & i_Delegate) {
			Receivers.push_back(i_Delegate);
		}

		void RemoveDelegate(Delegate<Params ...> & i_Delegate) {

		}

		void ExecuteOnBound(Params ... i_Parames) {
			for (auto Receiver : Receivers)
				Receiver.ExecuteIfBound(i_Parames ...);
		}
	private:
		std::vector<Delegate<Params ...>> Receivers;
	};
}