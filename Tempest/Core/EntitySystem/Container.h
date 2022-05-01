#pragma once

namespace Tempest
{
	template<typename T>
	class ContainerInfo
	{
		ptrdiff_t src;
		size_t index_size;
		size_t size;
		size_t offset;
	};

	constexpr size_t ContainerSize = 4096 * 1024;

	class Section
	{

	};

	class Container
	{
		Section section[2];
	};
}

