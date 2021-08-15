/**
 * @file MailBoxStatic.h
 * @author vishal k
 * @brief Header file for static mail box
 * @version 0.1
 * @date 2021-03-06
 * 
 * 
 */
#ifndef MAILBOXSTATIC_H
#define MAILBOXSTATIC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "MailBoxDefines.h"

/**
 * @brief Struct to hold messages
 * 
 */
typedef struct 
{
    bool present;
    int8_t index;
    char msg[MAX_MSG_SIZE];

}sMail_t;

/**
 * @brief Structure to hold static mail box
 * 
 */
typedef struct 
{
    sMail_t Mails[MAX_MAILS];
    uint8_t CurMsgIndex;
    size_t ActiveMsgNum;
}sMailBox_t;

eMailStatus_t MailboxStaticInit(sMailBox_t* const Me);
eMailStatus_t MailboxStaticDeleteMail(sMailBox_t* const Me);
eMailStatus_t MailboxStaticAddMail(sMailBox_t* const Me , const char* newMsg);
eMailStatus_t MailboxStaticScrollNext(sMailBox_t* const Me);
eMailStatus_t MailboxStaticview(sMailBox_t* const Me , char* const msg);


#endif