#pragma once

#include "Math.h"
#include <vector>

namespace NumberOne {
	namespace Graphics {
		
		class TransformationStack
		{
		private:
			std::vector<Math::mat4> ts_stack;
			Math::mat4* ts_stackBack;
		public:
			TransformationStack();
			void push(const Math::mat4& matrix, bool override = false);
			void pop();
			inline const Math::mat4* getStackBack() { return ts_stackBack; }
		//	inline const std::vector<Math::mat4>* getStack() { return &ts_stack; }
		};
} }
 // !TRANSFORMATION_STACK_H
