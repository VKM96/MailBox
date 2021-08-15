/**
 * @file MailBoxDynamic.c
 * @author vishal k
 * @brief Mailbox implementation using dynamic memory allocation
 * @date 2020-12-31
 * @note Define @ref USE_DYNAMIC_MAILBOX in @ref UsrConfig.h to use the file
 * 
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "UsrConfig.h"
#include "MailBoxDynamic.h"

#ifdef USE_DYNAMIC_MAILBOX

/**
 * @brief Helper function to create new node
 * 
 * @param newMsg data for the new created node
 * @return sMailNode_t* pointer to the new node created
 */
static sMailNode_t* MailboxDynamicNewMail(const char* const newMsg)
{
    sMailNode_t* pNewsMailNode = (sMailNode_t*)malloc(sizeof(sMailNode_t));
    assert(NULL != pNewsMailNode);

    memcpy(pNewsMailNode->msg , newMsg , MAX_MSG_SIZE);
    pNewsMailNode->next = NULL ;

    return pNewsMailNode ;
}

/**
 * @brief Initialization function
 * 
 * @param Me Equivalent to this pointer in cpp
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxDynamicInit(sMailBoxDynamic_t* const Me)
{
    assert(NULL != Me);

    Me->head = NULL;
    Me->CurMsgIndex  = 0;
    Me->ActiveMsgNum = 0;

    return E_NOERROR;

}

/**
 * @brief Add new node , utilizes @ref MailboxDynamicNewMail
 * 
 * @param Me Equivalent to this pointer in cpp
 * @param newmsg data for the new node
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxDynamicAddMail(sMailBoxDynamic_t* const Me, const char* const newmsg)
{
    assert(NULL != Me);
    assert(NULL != newmsg);

    eMailStatus_t status = E_NOERROR ;

    sMailNode_t* pNewsMailNode = MailboxDynamicNewMail(newmsg);

    sMailNode_t* iter = Me->head ;

    /// If no nodes are present make the new node head 
    if(NULL == iter)
    {
        Me->head = pNewsMailNode ;
    }
    else
    {
        /// Append node to the end of the list
        while(iter->next != NULL)
        {
            iter = iter->next ;
        }
        iter->next = pNewsMailNode ;

    }

    /// If number of nodes exceed predefined max nodes, then free oldest node 
    if(Me->ActiveMsgNum >= MAX_MAILS)
    {
        iter = Me->head;
        Me->head = Me->head->next;
        free(iter);
        status = E_MAILBOXOVERWRITTEN ;
    }
    /// Update active message count 
    else
    {
        Me->ActiveMsgNum++;
    }

    status = E_NOERROR ;
    
    return status;

}

/**
 * @brief scroll to the next message
 * 
 * @param Me  Equivalent to this pointer in cpp
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxDynamicScrollNext(sMailBoxDynamic_t* const Me)
{
    assert(NULL != Me);

    eMailStatus_t status = E_MAILBOXEMPTY ;

    if(1 >= Me->ActiveMsgNum)
    {
        Me->CurMsgIndex = 0 ;
        status = E_MAILBOXEMPTY ;
    }
    else 
    {
        sMailNode_t* iter = Me->head ;

        ///Traverse to next node
        iter = iter->next ;
        Me->CurMsgIndex++ ;
        
        ///If end node is reached reset current node iterator to head node
        if(Me->CurMsgIndex >= MAX_MAILS)
        {
            Me->CurMsgIndex = 0 ;
        }

        status = E_NOERROR ;

    }
    return status;
}

/**
 * @brief View function displays the current message in the message box
 * 
 * @param Me Equivalent to this pointer in cpp
 * @param msg pointer that will be filled up with the current message
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxDynamicview(sMailBoxDynamic_t* const Me , char* const msg)
{
    assert(NULL != Me);

    eMailStatus_t status = E_NOERROR ;
    sMailNode_t* iter = Me->head ;

    /// If there are no messages , set buffer to null 
    if(0 == Me->ActiveMsgNum)
    {
        memset(msg,0,sizeof(msg));
        status = E_MAILBOXEMPTY ;
    }
    
    else
    {
        ///If the current index is pointing to the last node reset the index to head
        if(Me->CurMsgIndex >= Me->ActiveMsgNum)
        {
            Me->CurMsgIndex = 0 ;
        }

        /// iterate over the list until the data at the current index is obtained and copy data to @ref msg
        for(size_t i = 0; i< Me->CurMsgIndex ; i++)
        {
            iter = iter->next ;
        }
        memcpy(msg,iter->msg,MAX_MSG_SIZE);
    }

    return status;

}

/**
 * @brief Delete the currently viewing message
 * 
 * @param Me Equivalent to this pointer in cpp
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxDynamicDeleteMail(sMailBoxDynamic_t* const Me )
{
    assert(NULL != Me);

    eMailStatus_t status = E_NOERROR ;

    /// If there are no messages set status to empty 
    if(0 == Me->ActiveMsgNum )
    {
        status = E_MAILBOXEMPTY;
    }
    else
    {
        sMailNode_t* iter = Me->head ;
        sMailNode_t* prevIter = iter;
        uint8_t lCurMsgIndex = 0 ;

        /// If the present message is the head node, update head node to next node 
        if(0 == Me->CurMsgIndex)
        {
            prevIter = iter ;
            iter = iter->next ;
            Me->head = iter ;
            free(prevIter);
        }
        else
        {
            /// Iterate to the node to be deleted as pointed by the current index, update links and free the deleted node
            while( (NULL != iter) && (lCurMsgIndex != Me->CurMsgIndex) )
            {
                ++lCurMsgIndex ;
                prevIter = iter ;
                iter = iter->next ;
            }
            ///End of the mailbox reached delete end node
            if(NULL == iter)
            {
                prevIter->next = NULL ;
                free(iter);
            }
            else
            {
                prevIter->next = iter->next ;
                free(iter);
            }
            status = E_NOERROR ;
        }
    }

    /// Reduce the activemessage count      
    if(Me->ActiveMsgNum > 0)
    {
        Me->ActiveMsgNum-- ;
    }

    return status;
}

#endif