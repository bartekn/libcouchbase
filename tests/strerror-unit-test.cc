/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 *     Copyright 2011 Couchbase, Inc.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#include "config.h"
#include <gtest/gtest.h>
#define LIBCOUCHBASE_INTERNAL 1
#include <libcouchbase/couchbase.h>

class Strerror : public ::testing::Test
{
};

TEST_F(Strerror, testNoCrash)
{
    for (int ii = -10; ii < 0xffff; ++ii) {
        EXPECT_NE((const char *)NULL,
                  lcb_strerror(NULL, (lcb_error_t)ii));
    }
}

TEST_F(Strerror, allCodesDocumented)
{
    const char *generic = lcb_strerror(NULL, (lcb_error_t) - 1);
    ASSERT_NE((const char *)NULL, generic);
    for (int ii = 0; ii < LCB_MAX_ERROR_VAL; ++ii) {
        EXPECT_STRNE(generic,
                     lcb_strerror(NULL, (lcb_error_t)ii));
    }

    for (int ii = LCB_MAX_ERROR_VAL; ii < 0xffff; ++ii) {
        EXPECT_STREQ(generic,
                     lcb_strerror(NULL, (lcb_error_t)ii));
    }

}
