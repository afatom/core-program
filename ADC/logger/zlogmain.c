#include "zlog4c.h"
#include <stdio.h>
#include <stdlib.h>

#include "mu_test.h"
#include <unistd.h>

UNIT(test)

ASSERT_THAT(ZLOG("HeapModule", LOG_ERROR, "Hi iam in main now") == 0);
ZlogInit("config.txt");
ASSERT_THAT(ZLOG("HeapModule", LOG_ERROR, "Hi iam in main now") != 0);
ASSERT_THAT(ZLOG("HeapModule", LOG_DEBUG, "Test message bla bla ") == 0);
ASSERT_THAT(ZLOG("TestModule", LOG_FATAL, "Test message bla bla sasd") != 0);

ZlogInit("config.txt");   /*<< updating log level for severe level */
ASSERT_THAT(ZLOG("HeapModule", LOG_ERROR, "Hi iam in main now") != 0);
ASSERT_THAT(ZLOG("HeapModule", LOG_DEBUG, "Test message bla bla ") == 0);
ASSERT_THAT(ZLOG("TestModule", LOG_FATAL, "Test message bla bla sasd") != 0);


END_UNIT

TEST_SUITE(logger_test)
TEST(test)
END_SUITE
