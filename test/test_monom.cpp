#include "stack.h"

#include <gtest.h>



TEST(Queue, can_create_queue) 
{
	ASSERT_NO_THROW(Queue<int> q);
}

