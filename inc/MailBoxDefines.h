/**
 * @file MailBoxDefines.h
 * @author vishal k
 * @brief common configuarable defines in mail box
 * @date 2021-03-06
 * 
 * 
 */
#ifndef MAILBOXDEFINES_H
#define MAILBOXDEFINES_H

#include <stddef.h>

static const size_t MAX_MAILS = 4 ;     //> Max number of messages
static const size_t MAX_MSG_SIZE = 16 ; //> MAc size of each message

/**
 * @brief enums for holding error types
 * 
 */
typedef enum 
{
    E_NOERROR ,
    E_MAILBOXEMPTY,
    E_MAILBOXOVERWRITTEN
}eMailStatus_t;


#endif