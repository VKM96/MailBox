/**
 * @file MailBoxStatic.c
 * @author vishal k
 * @brief Mailbox implementation using static memory allocation
 * @date 2020-12-31
 * @note Define @ref USE_STATIC_MAILBOX in @ref UsrConfig.h to use the file
 * 
 */
#include <string.h>
#include <assert.h>
#include "MailBoxStatic.h"
#include "UsrConfig.h"

#ifdef USE_STATIC_MAILBOX

/**
 * @brief Helper function to obtain next free slot in @ref sMailBox_t
 * 
 * @param Me Equivalent to this pointer in cpp
 * @param pNextslot Pointer that will be updated with the available slot by the function
 * @return eMailStatus_t status @ref eMailStatus_t
 */
static eMailStatus_t MailboxNextSlot(sMailBox_t* Me , int8_t* pNextslot)
{
    eMailStatus_t status = E_MAILBOXOVERWRITTEN ;

    /// Loop until all msg slots have been checked
    for(size_t i = 0 ; i < MAX_MAILS ; i++)
    {
        /// Empty slot found, break from searching and set status to no error
        if(false == Me->Mails[i].present)
        {
            *pNextslot = i ;
            status = E_NOERROR ;
            break;
        }
    }

    if(E_NOERROR != status)
    {
        /// Loop until last msg with index 0 is found
        for(size_t i = 0 ; i < MAX_MAILS ; i++)
        {
            /// slot with oldest msg found, break from searching and set status to overwritten
            if(0 == Me->Mails[i].index)
            {
                *pNextslot = i ;
                status = E_MAILBOXOVERWRITTEN ;
                break;
            }
        }

    }

    return status;
}

/**
 * @brief Helper function that returns the slot in which @ref sMail_t with @ref index is present
 * 
 * @param Me Equivalent to this pointer in cpp
 * @param index Logical index of the message whose real slot index needs to be found
 * @param pMsgIndex will be updated with the real slot address of @ref index
 * @return eMailStatus_t status @ref eMailStatus_t
 */
static eMailStatus_t MailboxFindMSg(sMailBox_t* Me , int8_t index , int8_t* pMsgIndex)
{
    eMailStatus_t status = E_MAILBOXEMPTY ;

    /// If no active messages set status to empty
    if(0 == Me->ActiveMsgNum)
    {
        status = E_MAILBOXEMPTY;
    }
    else
    {
        /// Iterate over all possible slots and return the slot with the @ref index
        for(size_t i = 0 ; i < MAX_MAILS ; i++)
        {
            if( (index == Me->Mails[i].index) && (true == Me->Mails[i].present ) )
            {
                
                *pMsgIndex = i;
                status = E_NOERROR;
                break;
            }

        } 
    }

    return status;
}

/**
 * @brief Initialization function
 * 
 * @param Me Equivalent to this pointer in cpp
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxStaticInit(sMailBox_t* const Me)
{
    assert(NULL != Me);

    Me->ActiveMsgNum = 0;

    /// Iterate over all possible slots and init all @ref Mails params
    for(size_t i = 0 ; i < MAX_MAILS ; i++)
    {
        Me->Mails[i].present = false ;
        Me->Mails[i].index = 0;
        Me->CurMsgIndex = 0 ;
        memset( (Me->Mails[i].msg), 0 ,MAX_MSG_SIZE*sizeof(char));
    }
    return E_NOERROR;
}

/**
 * @brief Delete the currently viewing message
 * 
 * @param Me Equivalent to this pointer in cpp
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxStaticDeleteMail(sMailBox_t* const Me)
{
    assert(NULL != Me);

    eMailStatus_t status = E_MAILBOXEMPTY ;
    uint8_t lCurMsgIndex = 0;

    /// Iterate over all slots, look for @ref Mails with index matching current message index
    for(size_t i = 0 ; i < MAX_MAILS ; i++)
    {
        if( (Me->CurMsgIndex == Me->Mails[i].index ) && (true == Me->Mails[i].present))
        {
            /// @ref Mails found, clear the slot and set active @ref present status to false
            Me->Mails[i].present = false ;
            lCurMsgIndex = Me->Mails[i].index ;
            Me->Mails[i].index = 0;
            memset( (Me->Mails[i].msg), 0 ,MAX_MSG_SIZE*sizeof(char));
            break;
        }
    }

    /// Update the indices of all slots with index value greater than deleted message
    for(size_t i = 0 ; i < MAX_MAILS ; i++)
    {
        if( (true == Me->Mails[i].present) && (Me->Mails[i].index > lCurMsgIndex) )
        {
            Me->Mails[i].index-- ;
        }
    }

    /// If the deleted message is the last message reset current message to first message
    if(Me->CurMsgIndex == Me->ActiveMsgNum-1)
    {
        Me->CurMsgIndex = 0;
    }

    /// Decrease active ,essage count
    if(Me->ActiveMsgNum > 0)
    {
        Me->ActiveMsgNum-- ;
        status = E_NOERROR ;
    }

    return status;
}

/**
 * @brief Add new message to mailbox
 * 
 * @param Me Equivalent to this pointer in cpp
 * @param newMsg 
 * @return eMailStatus_t 
 */
eMailStatus_t MailboxStaticAddMail(sMailBox_t* const Me , const char* newMsg)
{
    assert(NULL != Me);

    eMailStatus_t status = E_MAILBOXOVERWRITTEN ;
    int8_t nextSlot = 0;

    status = MailboxNextSlot(Me,&nextSlot);

    /// if empty slot obtained from @ref MailboxNextSlot increase msg number
    if(E_NOERROR == status)
    {
        Me->ActiveMsgNum++ ;
        status = E_NOERROR ;
    }
    else
    {
        /// No empty slot, replace the msg with index 0 
        for(size_t i = 0 ; i < MAX_MAILS ; i++)
        {
            if( (true == Me->Mails[i].present) && (0 != Me->Mails[i].index ) )
            {
                Me->Mails[i].index-- ;
            }
        }
        
    }
    
    /// Copy message to the acquired slot and set its index to messagenum-1
    /// This ensures that the older messages have lower indices
    memcpy(Me->Mails[nextSlot].msg , newMsg , MAX_MSG_SIZE);
    Me->Mails[nextSlot].present = true ;
    Me->Mails[nextSlot].index = Me->ActiveMsgNum-1 ;  

    return status;
    
}


/**
 * @brief Put the current message into @ref msg
 * 
 * @param Me Equivalent to this pointer in cpp
 * @param msg pointer that will be filled up with the current message
 * @return eMailStatus_t  @ref eMailStatus_t
 */
eMailStatus_t MailboxStaticview(sMailBox_t* const Me , char* const msg)
{
    assert(NULL != Me);

    eMailStatus_t status = E_NOERROR ;

    /// If empty update status
    if(0 == Me->ActiveMsgNum)
    {
        status = E_MAILBOXEMPTY ;
    }
    else
    {
        /// Iterate over all slots and copy msg with its @ref index as @ref CurMsgIndex to @ref msg
        for(size_t i = 0 ; i < MAX_MAILS ; i++)
        {
            if( (Me->CurMsgIndex == Me->Mails[i].index) && (true == Me->Mails[i].present))
            {
                memcpy(msg , Me->Mails[i].msg, MAX_MSG_SIZE);
                status = E_NOERROR ;
                break;
            }
        }
        
    }
    return status;
}

/**
 * @brief scroll to the next message
 * 
 * @param Me Equivalent to this pointer in cpp
 * @return eMailStatus_t status @ref eMailStatus_t
 */
eMailStatus_t MailboxStaticScrollNext(sMailBox_t* const Me)
{
    assert(NULL != Me);

    eMailStatus_t status = E_MAILBOXEMPTY ;
    int8_t NextValidMsgIndex;

    // If no message or only message dont scroll and update status
    if(1 >= Me->ActiveMsgNum)
    {
        Me->CurMsgIndex = 0 ;
        status = E_MAILBOXEMPTY ;
    }
    else
    {
        do
        {
            /// Increment the @ref CurMsgIndex and search for the message with that @ref CurMsgIndex using @ref MailboxFindMSg
            /// Keep incrementing  @ref CurMsgIndex till a msg with that @ref index is found
            Me->CurMsgIndex++ ;
            status = MailboxFindMSg(Me,Me->CurMsgIndex,&NextValidMsgIndex) ;

            /// If @ref CurMsgIndex goes out of bounds loop back to zero
            if(Me->CurMsgIndex > MAX_MAILS-1)
            {
                Me->CurMsgIndex = 0;
                break;
            }
            
        } while (status != E_NOERROR) ;
        

    }

    return status;
}

#endif
        

   