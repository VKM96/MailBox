MailBox                      {#mainpage}
============
    Mail Box implementation for use in embedded systems

**Code Structure**

1. Source files are present in @ref Src
2. Interface files are present in @ref inc
3. Please refer doxygen generated HTML documentation in the Doc/html subfolder for implementation details
4. The function entry point is @ref Main.c

**Usage**

1. Initialize using respective init function before use.


**Modification**

1. Select either @ref USE_STATIC_MAILBOX or @ref USE_DYNAMIC_MAILBOX from @ref UsrConfig.h
2. Maximum size and number of messages are controlled by changing paramaeters in @ref MailBoxDefines.h

**Permissions**

1. Please refer to the LICENSE file 