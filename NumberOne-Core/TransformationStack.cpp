#include "TransformationStack.h"

namespace NumberOne {
	namespace Graphics {
	
		TransformationStack::TransformationStack()
		{
			ts_stack.push_back(Math::mat4::identity());
			ts_stackBack = &ts_stack.front();
		}

		void TransformationStack::push(const Math::mat4& matrix, bool override)
		{
			//If override, back of t-stack will only have the passed in matrix rather than
			//having the total t-stack value to allow for correct pop
			if (override)
			{
				ts_stack.push_back(matrix);
			}
			else
				ts_stack.push_back(matrix * *ts_stackBack);
			ts_stackBack = &ts_stack.back();
		}

		void TransformationStack::pop()
		{
			if (ts_stack.size() > 1)
			{
				ts_stack.pop_back();
				ts_stackBack = &ts_stack.back();
			}
		}
	}
}