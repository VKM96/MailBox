/**
 * @file MailBoxWrapper.c
 * @author vishal K
 * @brief Wrapper around static and dynamic mailbox. Used by main application for demonstration
 * @date 2020-12-31
 * @note stdio.h is used only in the viewall function. It should be compiled out in the main application
 * @todo Update wrapper functions to use function pointers. 
 * 
 * 
 */

#include <assert.h>
#include <stdio.h> /// Used for view all for demonstration

#include "MailBoxWrapper.h"
#include "UsrConfig.h"
#include "MailBoxDefines.h"
#include "MailBoxDynamic.h"
#include "MailBoxStatic.h"

#ifdef USE_STATIC_MAILBOX


sMailBox_t gMailBoxStatic;                                                  /**< global sMailBox_t object for static mail box*/
sMailBox_t* pGMailBoxStatic = &gMailBoxStatic;
static eMailStatus_t MailboxStaticViewAll(sMailBox_t const* const Me );

#else

sMailBoxDynamic_t gMailBoxDynamic;                                          /**< global gMailBoxDynamic object for dynamic mail box*/
sMailBoxDynamic_t* pgMailBoxDynamic = &gMailBoxDynamic ;                   
static eMailStatus_t MailboxDynamicViewAll(sMailBoxDynamic_t const* const Me );

#endif


/**
 * @brief wrapper init function around @ref MailboxStaticInit and @ref MailboxDynamicInit
 * 
 * @return eMailStatus_t @ref eMailStatus_t
 */
eMailStatus_t MailboxInit()
{
    eMailStatus_t status = E_NOERROR ;

    #ifdef USE_STATIC_MAILBOX

    status = MailboxStaticInit(pGMailBoxStatic) ;

    #else 

    status = MailboxDynamicInit(pgMailBoxDynamic);

    #endif

    return status ;
}

/**
 * @brief wrapper message delete  function around @ref MailboxStaticDeleteMail and @ref MailboxDynamicDeleteMail
 * 
 * @return eMailStatus_t @ref eMailStatus_t
 */
eMailStatus_t MailboxDeleteMail()
{
    eMailStatus_t status = E_NOERROR ;

    #ifdef USE_STATIC_MAILBOX

    status = MailboxStaticDeleteMail(pGMailBoxStatic) ;

    #else 

    status = MailboxDynamicDeleteMail(pgMailBoxDynamic);

    #endif

    return status ;
}

/**
 * @brief wrapper message add  function around @ref MailboxStaticAddMail and @ref MailboxDynamicAddMail
 * 
 * @return eMailStatus_t @ref eMailStatus_t
 */
eMailStatus_t MailboxAddMail(const char* msg)
{
    eMailStatus_t status = E_NOERROR ;

    #ifdef USE_STATIC_MAILBOX

    status = MailboxStaticAddMail(pGMailBoxStatic,msg) ;

    #else 

    status = MailboxDynamicAddMail(pgMailBoxDynamic,msg);

    #endif

    return status ;

}

/**
 * @brief wrapper scroll function around @ref MailboxStaticScrollNext and @ref MailboxDynamicScrollNext
 * 
 * @return eMailStatus_t @ref eMailStatus_t
 */
eMailStatus_t MailboxScrollNext()
{
    eMailStatus_t status = E_NOERROR ;

    #ifdef USE_STATIC_MAILBOX

    status = MailboxStaticScrollNext(pGMailBoxStatic) ;

    #else 

    status = MailboxDynamicScrollNext(pgMailBoxDynamic);

    #endif

    return status ;

}

/**
 * @brief wrapper view function around @ref MailboxStaticview and @ref MailboxDynamicview
 * 
 * @return eMailStatus_t @ref eMailStatus_t
 */
eMailStatus_t Mailboxview(char* const msg)
{
    eMailStatus_t status = E_NOERROR ;

    #ifdef USE_STATIC_MAILBOX

    status = MailboxStaticview(pGMailBoxStatic,msg) ;

    #else 

    status = MailboxDynamicview(pgMailBoxDynamic,msg);

    #endif

    return status ;

}

/**
 * @brief wrapper view all function around @ref MailboxStaticViewAll and @ref MailboxDynamicViewAll
 * 
 * @return eMailStatus_t @ref eMailStatus_t
 * @note This function uses printf. It is for demonstration only. Should be removed in the actual implementation
 */
eMailStatus_t MailboxViewAll()
{
    eMailStatus_t status = E_NOERROR ;

    #ifdef USE_STATIC_MAILBOX

    status = MailboxStaticViewAll(pGMailBoxStatic) ;

    #else 

    status = MailboxDynamicViewAll(pgMailBoxDynamic);

    #endif

    return status ;

}

/**
 * @brief Utility function to view all messages in static mail box
 * 
 * @param Me 
 * @return eMailStatus_t 
 * 
 * @note This function uses printf. It is for demonstration only. Should be removed in the actual implementation
 */
static eMailStatus_t MailboxStaticViewAll(sMailBox_t const* const Me )
{
    assert(NULL != Me);

    eMailStatus_t status = E_NOERROR ;

    if(0 == Me->ActiveMsgNum)
    {
        status = E_MAILBOXEMPTY ;
    }
    else
    {
        for(size_t i = 0 ; i < MAX_MAILS ; i++)
        {
            if(true == Me->Mails[i].present)
            {
                printf("%d\t",Me->Mails[i].index);
                puts(Me->Mails[i].msg);

            }
        }
        status = E_NOERROR;
    }

    return status;
}

/**
 * @brief Utility function to view all messages in dynamic mail box
 * 
 * @param Me 
 * @return eMailStatus_t 
 * 
 * @note This function uses printf. It is for demonstration only. Should be removed in the actual implementation
 */
static eMailStatus_t MailboxDynamicViewAll(sMailBoxDynamic_t const* const Me )
{
    assert(NULL != Me);

    eMailStatus_t status = E_NOERROR ;

    if(0 == Me->ActiveMsgNum)
    {
        status = E_MAILBOXEMPTY ;
    }
    else
    {
        sMailNode_t* iter = Me->head ;

        while(NULL != iter)
        {
            printf("\n%s\n",iter->msg);
            iter = iter->next;
        }
        status = E_NOERROR;
    }

    return status;
}