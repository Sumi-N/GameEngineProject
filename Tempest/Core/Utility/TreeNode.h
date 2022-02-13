#pragma once

#include "Define.h"

namespace Tempest 
{
	template <typename T>
	class TreeNode 
	{
	public:
		TreeNode(T data);

	private:
		T data;
		TreeNode* next;
	};
}