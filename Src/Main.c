/**
 * @file Main.c
 * @author vishalK
 * @brief 
 * @version @ref VERSION
 * @date 2020-12-31
 * @bug No known bugs at the time of development
 * @todo Clean up demo console application.
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include "MailBoxWrapper.h"
#include "UsrConfig.h"
#include "Version.h"

/**
 * @brief Utility function for program info
 * 
 */
void printInfo()
{
    printf("version %d\n",VERSION);
    printf("Compile Date %s\n",COMPILE_DATE);
    printf("Compile time %s\n",COMPILE_TIME);
}

static void MailBoxDemonstration();

/**
 * @brief Function entry point, mailbox demonstration made. @see MailBoxWrapper.h
 * 
 * 
 * @return int 
 */
int main()
{
    printInfo();
    /// @ref MailBoxDemonstration
    MailBoxDemonstration();
    return 0;


}

/**
 * @brief utility enum for using in console demo application
 * 
 */
typedef enum
{
    E_ADD,      /**< Add message to message box*/
    E_DELETE,   /**< Delete current message from message box*/
    E_SCROLL,   /**< Scroll though messages in message box*/
    E_VIEWALL   /**< View all messages in message box*/
}eDemo_t;

static const char* InitMsg = "\nEnter : \n0 to add\n1 to delete\n2 to scroll\n3 to view the full msgbox \r\n" ;

/**
 * @brief Utility function to demonstrate static and dynamic mail box
 * @note Check @ref usrConfig to change between static and dynamic mailbox implementation
 * @see MailBoxWrapper.c
 * 
 */
static void MailBoxDemonstration()
{
    char tempbuf[30];
    char UsrMsg[30];
    int UserIn = 0;
    eMailStatus_t status ;

    #ifdef USE_STATIC_MAILBOX 
    printf("\nUsing Static MailBox\n" );
    #elif USE_DYNAMIC_MAILBOX
    printf("\nUsing Dynamic MailBox\n" );
    #else
    #error Select an implementation to use
    #endif

    status = MailboxInit();
    printf("%s",InitMsg);

    while(1)
    {
        scanf("%d",&UserIn);

        switch (UserIn)
        {
        case E_ADD :
        {
            printf("\nEnter message to add:\t");
            scanf("%s",UsrMsg);
            status = MailboxAddMail(UsrMsg);

            if(E_MAILBOXOVERWRITTEN == status)
            {
                printf("\nOldest message overwritten");
            }
            break;
        }

        case E_DELETE :
        {
            printf("\nDeleted message on screen");
            status = MailboxDeleteMail();
            break;
        }

        case E_SCROLL :
        {
            printf("\nScrolled to next message");
            status = MailboxScrollNext();
            if(E_MAILBOXEMPTY == status)
            {
                printf("\nNo messages");
            }
            break;
        }

        case E_VIEWALL :
        {
            printf("\nViewing all messages :\n");
            status = MailboxViewAll();
            break;
        }
        default:
        {
            printf("%s",InitMsg);
        }

        }
            printf("\nMessage on screen is :\t");
            status = Mailboxview(tempbuf );
            if(E_MAILBOXEMPTY == status)
            {
                printf("\nNo messages left\r\n");
            }
            else
            {
                puts(tempbuf);
            }

    }
}


