#pragma once

#include "Define.h"

namespace Tempeest 
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