/**
 * @file MailBoxStatic.h
 * @author vishal k
 * @brief wrapper interface around both static and dynamic mail boxes
 * @version 0.1
 * @date 2021-03-06
 * 
 * 
 */
#ifndef MAILBOXWRAPPER_H
#define MAILBOXWRAPPER_H

#include "MailBoxDefines.h"

eMailStatus_t MailboxInit();
eMailStatus_t MailboxDeleteMail();
eMailStatus_t MailboxAddMail(const char* msg);
eMailStatus_t MailboxScrollNext();
eMailStatus_t Mailboxview(char* const msg);

eMailStatus_t MailboxViewAll();


#endif