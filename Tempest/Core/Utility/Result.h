#pragma once

#include "Define.h"

#define RETURN_IFNOT_SUCCESS(i_condition)\
	{\
		if(static_cast<Tempest::Result>(i_condition) != Tempest::ResultValue::Success)\
		{\
			return i_condition;\
		}\
	}

namespace Tempest
{
	enum class eResult : bool
	{
		IsSuccess = true,
		IsFailure = false
	};

	enum class eSeverity : uint8_t
	{
		Default = 0,   // Nothing went wrong, OR you just didn't set severity
		Warning = 1,   // Some negligible error happened
		Error   = 127, // Something went wrong and the caller should take action accordingly
		Fatal   = 255  // The program will exit or crash
	};

	enum class eSystem : uint8_t
	{
		General,

		Application,
		GameThread,
		RenderThread,

		Count          // This must be the last
	};
	static_assert(static_cast<uint8_t>(eSystem::Count) <= 0x80, "A result's system ID must fit into 7 bits");

	// Result class is 32 bit boolean class where it has the information about result, severity, system etc...
	// The first bit is a boolean that tells you if the result is success or not. From 2 to 16 bit are the bits
	// that tells you about what system it is related, From 17 to 24 bits are the information about severity of
	// the error. The rest of bits, 17 to 32 bits are the bits that can assign to an arbitrary ID for various reason. 

	class Result
	{
	public:

#define TEMPEST_RESULTS_SUCCESS_MASK   0x80000000
#define TEMPEST_RESULTS_SYSTEM_MASK    0x7f000000
#define TEMPEST_RESULTS_SYSTEM_SHIFT   24
#define TEMPEST_RESULTS_SEVERITY_MASK  0x00ff0000
#define TEMPEST_RESULTS_SEVERITY_SHIFT 16

		constexpr operator bool() const 
		{
			return IsSuccess(); 
		}

		constexpr bool IsSuccess() const
		{
			return (value & TEMPEST_RESULTS_SUCCESS_MASK) != 0;
		}

		constexpr eResult GetSystem() const
		{
			return static_cast<eResult>((value & TEMPEST_RESULTS_SYSTEM_MASK) >> TEMPEST_RESULTS_SYSTEM_SHIFT);
		}

		constexpr eSeverity GetSeverity() const
		{
			return static_cast<eSeverity>((value & TEMPEST_RESULTS_SEVERITY_MASK) >> TEMPEST_RESULTS_SEVERITY_SHIFT);
		}

		constexpr bool operator ==(const Result i_rhs) const
		{
			return value == i_rhs.value;
		}

		constexpr bool operator !=(const Result i_rhs) const
		{
			return value != i_rhs.value;
		}

		constexpr Result(const eResult i_issuccess, const eSystem i_system, const eSeverity i_severity, const uint16_t i_id) :
			value((static_cast<bool>(i_issuccess)    ? TEMPEST_RESULTS_SUCCESS_MASK : 0)
				| (static_cast<uint8_t>(i_system)   << TEMPEST_RESULTS_SYSTEM_SHIFT)
				| (static_cast<uint8_t>(i_severity) << TEMPEST_RESULTS_SEVERITY_SHIFT)
				| i_id)
		{

		}

		const Result()
			:
			Result(eResult::IsFailure, eSystem::General, eSeverity::Default, ~static_cast<uint16_t>(0x0))
		{

		}

#undef TEMPEST_RESULTS_SUCCESS_MASK
#undef TEMPEST_RESULTS_SYSTEM_MASK
#undef TEMPEST_RESULTS_SYSTEM_SHIFT
#undef TEMPEST_RESULTS_SEVERITY_MASK
#undef TEMPEST_RESULTS_SEVERITY_SHIFT

	private:
		uint32_t value;
	};

	namespace ResultValue
	{
		// General non-specific success/failure results
		constexpr Result Success(eResult::IsSuccess, eSystem::General, eSeverity::Default, __LINE__);
		constexpr Result Failure(eResult::IsFailure, eSystem::General, eSeverity::Default, __LINE__);

		// This is returned when something is wrong with a file
		// (the file exists, but there is something wrong with its contents e.g. it is formatted incorrectly)
		constexpr Result InvalidFile(eResult::IsFailure, eSystem::General, eSeverity::Default, __LINE__);
		// This is returned when a required file doesn't exist
		constexpr Result FileDoesntExist(eResult::IsFailure, eSystem::General, eSeverity::Default, __LINE__);
		// This is returned when something fails because not enough memory was available
		constexpr Result OutOfMemory(eResult::IsFailure, eSystem::General, eSeverity::Default, __LINE__);
		// This is returned when something fails because some context-specific amount of time passed
		// (e.g. the task might have succeeded if more time had been spent,
		// the task might succeed if tried again at a later time, etc.)
		constexpr Result TimeOut(eResult::IsFailure, eSystem::General, eSeverity::Warning, __LINE__);

		// This can be compared against if the caller wants to know if no value was assigned
		//constexpr Result Undefined();
	}
}