// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <openenclave/enclave.h>
#include <openenclave/bits/stdio.h>

// Include the trusted oe_policy_tool header that is generated
// during the build. This file is generated by calling the
// sdk tool sgx_edger8r against the oe_policy_tool.edl file.
#include "oe_policy_tool_t.h"

int enclave_dummy(void)
{
    return 0;
}
   