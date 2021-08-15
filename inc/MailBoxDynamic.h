/**
 * @file MailBoxDynamic.h
 * @author vishal k
 * @brief dynamic mailbox interface
 * @date 2021-03-06
 * 
 */

#ifndef MAILBOXDYNAMIC_H
#define MAILBOXDYNAMIC_H

#include <stdint.h>
#include <stddef.h>
#include "UsrConfig.h"
#include "MailBoxDefines.h"

/**
 * @brief Struct to hold messages
 * 
 */
typedef struct sMailNode_t
{
    char msg[MAX_MSG_SIZE];
    sMailNode_t* next;
    
}sMailNode_t;

/**
 * @brief Structure to hold dynamic mail box
 * 
 */
typedef struct 
{
    sMailNode_t* head;
    uint8_t CurMsgIndex;
    size_t ActiveMsgNum;

}sMailBoxDynamic_t;

eMailStatus_t MailboxDynamicInit(sMailBoxDynamic_t* const Me);
eMailStatus_t MailboxDynamicDeleteMail(sMailBoxDynamic_t* const Me );
eMailStatus_t MailboxDynamicAddMail(sMailBoxDynamic_t* const Me, const char* const msg);
eMailStatus_t MailboxDynamicScrollNext(sMailBoxDynamic_t* const Me);
eMailStatus_t MailboxDynamicview(sMailBoxDynamic_t* const Me , char* const msg);

#endif