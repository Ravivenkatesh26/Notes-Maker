#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 50

typedef struct
{
    char name[20];
    char CreatedDate[15];
    char Createdtime[15];
    char ModifiedDate[15];
    char Modifiedtime[15];
    char LockQuestion[2];
    int lock;
    char SpaceOfNote[N*2][N*2];
    int NumberOFLines;
}App;

App notes;/**Struct variable**/

void CreateNote()
{
    time_t t = time(NULL);/**To get modified time and date**/
    struct tm tm = *localtime(&t);/** Accessing time and date using this fn**/
    char *ModifiedDate=malloc(50);/*** Modified time & time variable**/
    char *MOdifiedTime=malloc(50);

    system("clear");
    printf("\t\t\t\t\t\t\%s\n\n",notes.name);/**Displaying Note name entered**/
    printf("NOTE-->Print STOP(uppercase) to end note.\n\n");
    /**Providing '\n' until user enters 'STOP'**/
    for(int i=0;;i++)
    {
        gets(notes.SpaceOfNote[i]);
        if(strstr(notes.SpaceOfNote[i],"STOP"))
        {
            notes.NumberOFLines=i;
            break;
        }
    }
    snprintf(ModifiedDate,50,"%d-%02d-%02d",tm.tm_year + 1900,tm.tm_mon + 1,tm.tm_mday);
    snprintf(MOdifiedTime,50,"%02d:%02d:%02d",tm.tm_hour,tm.tm_min,tm.tm_sec);
    strcpy(notes.ModifiedDate,ModifiedDate);/**Storing modified date and time**/
    strcpy(notes.Modifiedtime,MOdifiedTime);
    free(ModifiedDate);/**Freeing allocated memory modified and time**/
    free(MOdifiedTime);
}


int TitleSort()
{
    int found=0;

    typedef struct
     {
      char name[20];
      char CreatedDate[15];
      char Createdtime[15];
      char ModifiedDate[15];
      char Modifiedtime[15];
      char LockQuestion[2];
      int lock;
      char SpaceOfNote[N*2][N*2];
      int NumberOFLines;
    }write;

    write temp;
    write copy;
    write anothercopy1;
    write anothercopy2;
    write sortednote;
    int ch,n=0;

    system("clear");
    FILE *fpcopy=fopen("Notes.txt","r");
    FILE *fpsort=fopen("Sorting.txt","w+");
    FILE *fptemp=fopen("Temp.txt","w+");
    FILE *fpanothertemp=fopen("AnotherTemp.txt","w+");
    int pos=0,getpos;

    if(fpcopy==NULL || fpsort==NULL || fptemp==NULL || fpanothertemp==NULL)
        {
            printf("\n\tError occurred while opening APP!\n");
            exit(0);
        }

    while((ch=fgetc(fpcopy))!=EOF)
    {
        fputc(ch,fpsort);
    }

    fseek(fpsort,0,SEEK_SET);
    while(fread(&copy,sizeof(write),1,fpsort))
    {
        pos=ftell(fpsort);
        fseek(fpsort,0,SEEK_SET);
        while(fread(&temp,sizeof(write),1,fpsort))
        {
            getpos=ftell(fpsort);

            if(strcmp(copy.name,temp.name)<0)
            {
               fseek(fpsort,pos-sizeof(write),SEEK_SET);
               fseek(fptemp,0,SEEK_SET);
               while((ch=fgetc(fpsort))!=EOF)
              {
              if(ftell(fpsort)<pos)
              {
              fputc(ch,fptemp);
              }
              }

              fseek(fpsort,getpos-sizeof(write),SEEK_SET);
              fseek(fpanothertemp,0,SEEK_SET);
              while((ch=fgetc(fpsort))!=EOF)
              {
              if(ftell(fpsort)<getpos)
              {
              fputc(ch,fpanothertemp);
              }
              }

              fseek(fpanothertemp,0,SEEK_SET);
              fseek(fptemp,0,SEEK_SET);
              fread(&anothercopy1,sizeof(write),1,fpanothertemp);
              fread(&anothercopy2,sizeof(write),1,fptemp);
              fseek(fpsort,pos-sizeof(write),SEEK_SET);
              fwrite(&anothercopy1,sizeof(write),1,fpsort);
              fseek(fpsort,getpos-sizeof(write),SEEK_SET);
              fwrite(&anothercopy2,sizeof(write),1,fpsort);
            }
            fseek(fpsort,getpos,SEEK_SET);
        }
        fseek(fpsort,pos,SEEK_SET);
    }

    fseek(fpsort,0,SEEK_SET);
    printf("\t\t\t\t\t\tSORTED NOTES\n\n");
    while(fread(&sortednote,sizeof(write),1,fpsort))
    {
        if(!strcmp(sortednote.LockQuestion,"s")|| !strcmp(sortednote.LockQuestion,"S"))
        {
            printf("\t\t\t\t%d.%s\n\n",n+1,sortednote.name);
            printf("\t\t\t\tLOCKED\n");
            printf("\n\t\t\t\t\tCreated:%s %s",sortednote.CreatedDate,sortednote.Createdtime);
            printf("\n\t\t\t\t\tLast modified:%s %s\n",sortednote.ModifiedDate,sortednote.Modifiedtime);
            printf("-------------------------------------------------------------------------\n");
            n++;
            found=1;
        }else
        {
        /**Displaying information in file into monitor**/
        printf("\t\t\t\t%d.%s\n\n",n+1,sortednote.name);
        for(int i=0;i<sortednote.NumberOFLines;i++)
            printf("%s\n",sortednote.SpaceOfNote[i]);
        printf("\n\t\t\t\t\tCreated:%s %s",sortednote.CreatedDate,sortednote.Createdtime);
        printf("\n\t\t\t\t\tLast modified:%s %s\n",sortednote.ModifiedDate,sortednote.Modifiedtime);
        printf("-------------------------------------------------------------------------\n");
        n++;
        found=1;
        }
    }

    fpsort=fopen("Sorting.txt","w");
    fptemp=fopen("Temp.txt","w");
    fpanothertemp=fopen("AnotherTemp.txt","w");

    fclose(fpsort);
    fclose(fpcopy);
    fclose(fptemp);
    fclose(fpanothertemp);
    return found;
}

int DisplayNote(char check[])
{
    int found=0,n=0;
    FILE *fp=fopen("Notes.txt","r");/**Opening file using file pointer for reading**/

    if(strcmp(check,"yes")==0)
        {
            system("clear");
            printf("\t\t\t\t\t\tALL NOTES\n\n");/** Just displaying 'ALL NOTES' **/
        }

    if(fp==NULL)/**Checking whether it is possible to open**/
    {
        printf("\n\tError occurred while opening APP!\n");
        exit(0);
    }

         /**Reading Note from file until it finds EOF **/
    while(fread(&notes,sizeof(App),1,fp))
    {
        if(!strcmp(notes.LockQuestion,"s")|| !strcmp(notes.LockQuestion,"S"))
        {
            printf("\t\t\t\t%d.%s\n\n",n+1,notes.name);
            printf("\t\t\t\tLOCKED\n");
            printf("\n\t\t\t\t\tCreated:%s %s",notes.CreatedDate,notes.Createdtime);
            printf("\n\t\t\t\t\tLast modified:%s %s\n",notes.ModifiedDate,notes.Modifiedtime);
            printf("-------------------------------------------------------------------------\n");
            n++;
            found=1;
        }else
        {
        /**Displaying information in file into monitor**/
        printf("\t\t\t\t%d.%s\n\n",n+1,notes.name);
        for(int i=0;i<notes.NumberOFLines;i++)
            printf("%s\n",notes.SpaceOfNote[i]);
        printf("\n\t\t\t\t\tCreated:%s %s",notes.CreatedDate,notes.Createdtime);
        printf("\n\t\t\t\t\tLast modified:%s %s\n",notes.ModifiedDate,notes.Modifiedtime);
        printf("-------------------------------------------------------------------------\n");
        n++;
        found=1;
        }
    }
    fclose(fp);
    fp=NULL;

    return found;
}

int EditNote(int tracking)
{
    char newname[N/2];
    char *ModifiedDate=malloc(50),*ModifiedTime=malloc(50);/**Note date and time variable**/
    FILE *fp=fopen("Notes.txt","r+");
    time_t t = time(NULL);/**Time variable**/
    struct tm tm = *localtime(&t);/** Accessing date and time from library fn**/
    int i=0,found=0;

    printf("\n\tEnter the new name of the note: ");
    fgetc(stdin);
    gets(newname);
    fseek(fp,tracking,SEEK_SET);
    while(newname[i]!='\0')
        {
            fputc(newname[i],fp);
            i++;
        }
    fputc('\0',fp);
    i=0;
    snprintf(ModifiedDate,50,"%d-%02d-%02d",tm.tm_year + 1900,tm.tm_mon + 1,tm.tm_mday);
    snprintf(ModifiedTime,50,"%02d:%02d:%02d",tm.tm_hour,tm.tm_min,tm.tm_sec);
    strcpy(notes.ModifiedDate,ModifiedDate);/**Storing modified date**/
    strcpy(notes.Modifiedtime,ModifiedTime);/**Storing modified time**/
    fseek(fp,tracking+50,SEEK_SET);
    while(ModifiedDate[i]!='\0')
        {
            fputc(ModifiedDate[i],fp);
            i++;
        }
    fputc('\0',fp);
    i=0;
    fseek(fp,tracking+65,SEEK_SET);
    while(ModifiedTime[i]!='\0')
        {
            fputc(ModifiedTime[i],fp);
            i++;
        }
    fputc('\0',fp);
     return found=1;
}

int RestOrSetPIN(int tracking,int check)
{
    FILE *fp=fopen("Notes.txt","r+");
    int newpin;

lock:
    {
    printf("\n\tEnter new 4 digit PIN:: ");
    scanf("%d",&newpin);
    if(newpin/1000>=1 && newpin/1000<=9)
    {
        printf("\n\tSuccessfully locked!");
    }
    else
    {
        printf("\n\tInvalid PIN,try again\n");
        goto lock;
    }
    }

    if(check==27)
    {
        fseek(fp,tracking+80,SEEK_SET);
        fputc('s',fp);
        fseek(fp,tracking+82,SEEK_SET);
        fprintf(fp,"%d",newpin);
    }

    return 1;
}

int main()
{
    int opt,found=0,moreopt=0,MoreLockOpt=0;/**choice variable & search tracking variable**/
    char *Createdate=malloc(50),*Createdtime=malloc(50);/**Note date and time variable**/
    char searchname[N/2],deletename[N/2],renamenote[N/2];/**Searching name variable**/
    char saveopt[2],continueopt[2],resetpin[2];/**Saving variable to store it on file**/
    int n=0,sortopt,lockopt;/**variable for displaying number of notes**/
    FILE *fp;/**File pointer for file operations**/
    char unlockname[N/2];
    int tracking=0,LockFound=0;

    do
 {
    time_t t = time(NULL);/**Time variable**/
    struct tm tm = *localtime(&t);/** Accessing date and time from library fn**/
    system("clear");

    /****Choice to be selected****/
    printf("\t\t\t\t\t\tNOTES\n\n");
    printf("\t-->1.Add Note\n\n");
    printf("\t-->2.All Notes\n\n");
    printf("\t-->3.Search Note\n\n");
    printf("\t-->4.More\n\n");
    printf("\tPlease enter the option: ");

    scanf("%d",&opt);/**Choice storing**/

    /**Switch statement to select appropriate operation according choice**/
    switch(opt)
    {
        /**Creating Notes**/
    case 1:
        lockopt=0;
        system("clear");
        /***Opening file to store note in a+ bcz of note should be contagious***/
        fp=fopen("Notes.txt","a+");

        if(fp==NULL)/**Checking whether it is possible to open or not**/
        {
            printf("\n\tError occurred while opening APP!\n");
            exit(0);/**exiting if not possible to open**/
        }

        printf("Enter the Name of the note: ");
        fgetc(stdin);
        fgets(notes.name,20,stdin);/**File name storing**/
        notes.name[strlen(notes.name)-1]=0;/**Bcz of fgets '\n' will be appended**/

        CreateNote();/**Passing curzer into this operation**/

        /**snprintf is used to convert int to string(time&date)**/
        snprintf(Createdate,50,"%d-%02d-%02d",tm.tm_year + 1900,tm.tm_mon + 1,tm.tm_mday);
        snprintf(Createdtime,50,"%02d:%02d:%02d",tm.tm_hour,tm.tm_min,tm.tm_sec);
        strcpy(notes.CreatedDate,Createdate);/**Storing created date**/
        strcpy(notes.Createdtime,Createdtime);/**Storing createdtime**/
        printf("\n\tDo you want lock your note[s/n]: ");
        gets(notes.LockQuestion);
    lock:
    {
        if(!strcmp(notes.LockQuestion,"S")|| !strcmp(notes.LockQuestion,"s"))
        {
            printf("\n\tEnter 4 digit PIN: ");
            scanf("%d",&notes.lock);
            if(notes.lock/1000>=1 && notes.lock/1000<=9)
                {
                    printf("\n\tSuccessfully locked!");
                }
                else
                {
                    printf("\n\tInvalid PIN,try again\n");
                    goto lock;
                }
        }
    }

        printf("\n\n\tDo you want to save[s/n]: ");
        scanf("%s",saveopt);/**Storing save opt and operating acrn to it**/
        if(!strcmp(saveopt,"s") || !strcmp(saveopt,"S"))
        {
         fwrite(&notes,sizeof(App),1,fp);/**Storing "entire note into file"**/
         printf("\n\tSuccessfully saved!\n");
        }else
        printf("\n\tSorry,unable to save:(");

        free(Createdate);/**Revealing allocated memory for date & time**/
        free(Createdtime);
        fclose(fp);/**Closing file pointer(file closing)**/
        fp=NULL;
        break;

      /**Displaying NOtes**/
    case 2:
        found=DisplayNote("yes");
         if(found==0)
         {
           printf("\tSorry,there is no note that have been saved!");
         }

        break;
        /**Searching Note**/
    case 3:
        system("clear");
        fp=fopen("Notes.txt","r");/**Opening file using file pointer for reading**/
        n=0,found=0;

        printf("Enter the search name: ");
        fgetc(stdin);
        fgets(searchname,20,stdin);/**Storing search name**/
        searchname[strlen(searchname)-1]=0;
        system("clear");
        /**Accessing all note for searching**/
        while(fread(&notes,sizeof(App),1,fp))
        {
         /**Searching Note name with search name**/
        if(!strcmp(notes.name,searchname))
          {
            /**Displaying information if found and search tracking will have 1 value**/
            if(!strcmp(notes.LockQuestion,"s")|| !strcmp(notes.LockQuestion,"S"))
                {
                    printf("\t\t\t\t%d.%s\n\n",n+1,notes.name);
                    printf("\t\t\t\tLOCKED\n");
                    printf("\n\t\t\t\t\tCreated:%s %s",notes.CreatedDate,notes.Createdtime);
                    printf("\n\t\t\t\t\tLast modified:%s %s\n",notes.ModifiedDate,notes.Modifiedtime);
                    printf("-------------------------------------------------------------------------\n");
                    found=1;
                }else
                {
                    /**Displaying information in file into monitor**/
                    printf("\t\t\t\t%d.%s\n\n",n+1,notes.name);
                    for(int i=0;i<notes.NumberOFLines;i++)
                        printf("%s\n",notes.SpaceOfNote[i]);
                    printf("\n\t\t\t\t\tCreated:%s %s",notes.CreatedDate,notes.Createdtime);
                    printf("\n\t\t\t\t\tLast modified:%s %s\n",notes.ModifiedDate,notes.Modifiedtime);
                    printf("-------------------------------------------------------------------------\n");
                    found=1;
                }
          }
          n++;
        }
        /**If search tracking variable value is 0 then Note not found**/
        if(found==0)
        {
        printf("\t\t\t\t\tSorry,unable to find note:(\n");
        goto CheckNote;
        }

        fclose(fp);
        fp=NULL;

         /**If search tracking variable value is 0 then Note not found**/
        if(found==0)
        {
        printf("\t\t\t\t\tSorry,unable to find note:(\n");
        goto CheckNote;
        }
        break;
    case 4:
        system("clear");
        /**Displaying 'More' operations **/
        printf("\t\t\t\t\t\tMORE\n\n");
        printf("\t-->1.Edit\n\n");
        printf("\t-->2.Sort\n\n");
        printf("\t-->3.Delete\n\n");
        printf("\t-->4.Lock\n\n");
        printf("\tEnter the option you want to operate: ");
        scanf("%d",&moreopt);/** Storing More opt**/

        if(moreopt==1)
        {
            fp=fopen("Notes.txt","r");
            lockopt=0,found=0;

            system("clear");
            printf("\t\t\t\t\t\tEDIT\n\n\n");
            printf("\n\tEnter the old name of the note to be renamed: ");
            fgetc(stdin);
            gets(renamenote);

             while(fread(&notes,sizeof(App),1,fp))
            {
                tracking=ftell(fp)-sizeof(App);
              /**Searching Note name with rename**/
              if(!strcmp(notes.name,renamenote))
               {
                   if(!strcmp(notes.LockQuestion,"s")|| !strcmp(notes.LockQuestion,"S"))
                   {
                       printf("\n\tThis note is locked.");
                       printf("\n\tEnter PIN to rename: ");
                       scanf("%d",&lockopt);
                       if(lockopt==notes.lock)
                       {
                            found=EditNote(tracking);
                       }else
                       {
                           printf("\n\tIncorrect PIN");
                           break;
                       }
                   }else
                   {
                       found=EditNote(tracking);
                   }
               }
            }

            if(found==0)
            {
                    printf("\n\tSorry,unable rename.");
        CheckNote:
                {
                    printf("\n\tPlease Note:");
                    printf("\n\t\t1.Entered note name already exists");
                    printf("\n\t\t2.Entered note name matches with existing note name(including cases)");
                }
            }else
            printf("\n\tSuccessfully renamed!");

            fclose(fp);

        }else if(moreopt==2)
        {
            /**Displaying sorting operations**/
            found=0;
            system("clear");
            printf("\t\t\t\t\t\tSORT BY\n\n");
            printf("\t-->1.Title\n\n");
            printf("\t-->2.Created Date\n\n");
            printf("\tEnter the option you want to operate: ");
            scanf("%d",&sortopt);/**Storing sorting opt**/
            if(sortopt==1)
            {
                /**Passing curzer into TitleSort fn**/
                found=TitleSort();
                if(found==0)
                    {
                        printf("\tSorry,there no note that have been saved!");
                    }
            }else if(sortopt==2)
            {
                system("clear");
                printf("\t\t\t\t\t\tSORTED NOTES\n\n");
                /**Passing curzer into modified label in 'All NOTES'**/
                DisplayNote("NULL");
            }
            else
                printf("\n\tInvalid choice\n");
        }else if(moreopt==3)
        {
            lockopt=0;
            fp=fopen("Notes.txt","r");/**Opening file for reading**/
            FILE *fpdel=fopen("Deleting.txt","w");/**Creating Deleting file**/
            found=0;

            if(fpdel==NULL)/**Checking whether it is able to open**/
            {
            printf("\n\tError occurred while opening APP!\n");
            exit(0);
            }

            system("clear");
            printf("\t\t\t\t\t\tDELETE\n\n\n");
            printf("\n\tEnter name of the note to be deleted: ");
            fgetc(stdin);
            gets(deletename);/**Storing name to be deleted**/

            fseek(fp,0,SEEK_SET);
            while(fread(&notes,sizeof(App),1,fp))
             {
                 /**checking deleting name with note name**/
              if(!strcmp(notes.name,deletename))
               {
                   if(!strcmp(notes.LockQuestion,"s")|| !strcmp(notes.LockQuestion,"S"))
                   {
                       printf("\n\tThis note is locked");
                       printf("\n\tPlease enter PIN to delete note: ");
                       scanf("%d",&lockopt);
                       if(lockopt==notes.lock)
                       {
                           found=1;/**Delete track**/
                           LockFound=1;
                       }else
                       {
                       printf("\n\tIncorrect PIN");
                       found=0;
                       LockFound=0;
                       break;
                       }
                   }else
                   {
                       found=1;/**Delete track**/
                       LockFound=1;
                   }
               }
               else if(strcmp(notes.name,deletename))
                {
                    fwrite(&notes,sizeof(App),1,fpdel);
                }
            }

            if(LockFound==1)
            {
                /**renaming delete file original file(Notes)**/
                rename("Deleting.txt","Notes.txt");
            }else
            {
                remove("Deleting.txt");
            }

            if(found==1)
            {
                /**If delete track value if 1 then note is deleted**/
                printf("\n\tSuccessfully deleted\n");
            }else
            printf("\n\tSorry,Unable to delete\n");

            fclose(fpdel);
            fclose(fp);
        }else if(moreopt==4)
        {
            tracking=0,lockopt=0;
            found=0;
            system("Clear");
            printf("\t\t\t\t\t\tLOCK\n\n");
            printf("\t-->1.View locked note\n\n");
            printf("\t-->2.Unlock note permanently\n\n");
            printf("\t-->3.Set/Reset PIN\n\n");
            printf("\tEnter the option you want to operate: ");
            scanf("%d",&MoreLockOpt);

            if(MoreLockOpt==1)
            {
                n=0;
                fp=fopen("Notes.txt","r");
                system("clear");
                printf("\t\t\t\t\t\tVIEW LOCKED NOTE\n\n");
                printf("\n\tEnter name of the note: ");
                fgetc(stdin);
                gets(unlockname);

                while(fread(&notes,sizeof(App),1,fp))
                {
                    if(!strcmp(notes.name,unlockname))
                    {
                        if(!strcmp(notes.LockQuestion,"s")|| !strcmp(notes.LockQuestion,"S"))
                        {
                            printf("\n\tEnter PIN of the note: ");
                            scanf("%d",&lockopt);

                            if(lockopt==notes.lock)
                            {
                            label:
                                {
                                 printf("\n\n");
                                 printf("\t\t\t\t%d.%s\n\n",n+1,notes.name);
                                 for(int i=0;i<notes.NumberOFLines;i++)
                                    printf("%s\n",notes.SpaceOfNote[i]);
                                 printf("\n\t\t\t\t\tCreated:%s %s",notes.CreatedDate,notes.Createdtime);
                                 printf("\n\t\t\t\t\tLast modified:%s %s\n",notes.ModifiedDate,notes.Modifiedtime);
                                 printf("-------------------------------------------------------------------------\n");
                                 found=1;
                                }
                            }else
                            {
                                printf("\n\tIncorrect PIN.");
                                printf("\n\tSorry,Unable to open note.");
                                found=5;
                                break;
                            }
                        }else
                        {
                            goto label;
                        }
                    }
                    n++;
                }

                if(found==0)
                    {
                        goto CheckNote;
                    }

                    fclose(fp);
                    fp=NULL;
            }
            else if(MoreLockOpt==2)
            {
                found=0;
                fp=fopen("Notes.txt","r+");
                system("clear");
                printf("\t\t\t\t\t\tUNLOCK NOTE PERMANENTLY\n\n");
                printf("\n\tEnter name of the note: ");
                fgetc(stdin);
                gets(unlockname);

                while(fread(&notes,sizeof(App),1,fp))
                {
                    tracking=ftell(fp)-sizeof(App);
                    if(!strcmp(notes.name,unlockname))
                    {
                       if(!strcmp(notes.LockQuestion,"s")|| !strcmp(notes.LockQuestion,"S"))
                       {
                           printf("\n\tEnter PIN of the note: ");
                            scanf("%d",&lockopt);

                            if(lockopt==notes.lock)
                            {
                                fseek(fp,tracking+80,SEEK_SET);
                                fputc('n',fp);
                                found=1;
                            }else
                            {
                                printf("\n\tIncorrect PIN.");
                                printf("\n\tSorry,Unable to open note.");
                                found=5;
                                break;
                            }
                       }else
                       {
                           printf("\n\t\"%s\" note is already been unlocked!",unlockname);
                           found=5;
                           break;
                       }
                    }
                }

                if(found==0)
                {
                   goto CheckNote;
                }else if(found==1)
                {
                    printf("\n\tSuccessfully unlocked \"%s\" note permanently.",unlockname);
                }

                fclose(fp);
                fp=NULL;
            }else if(MoreLockOpt==3)
            {
                found=0;
                fp=fopen("Notes.txt","r+");

                system("clear");
                printf("\t\t\t\t\t\tSET/RESET PIN\n\n");
                printf("\n\tEnter name of the note: ");
                fgetc(stdin);
                gets(unlockname);

                while(fread(&notes,sizeof(App),1,fp))
                {
                   tracking=ftell(fp)-sizeof(App);
                   if(!strcmp(notes.name,unlockname))
                   {
                      if(!strcmp(notes.LockQuestion,"s")|| !strcmp(notes.LockQuestion,"S"))
                      {
                          printf("\n\tThis note already have been set PIN!");
                          printf("\n\tDo you want to reset PIN[s/n]: ");
                          scanf("%s",resetpin);
                          if(!strcmp(resetpin,"s") || !strcmp(resetpin,"S"))
                          {
                              printf("\n\tEnter PIN of this note: ");
                              scanf("%d",&lockopt);
                              if(lockopt==notes.lock)
                              {
                                  found=RestOrSetPIN(tracking,15);
                              }else
                              {
                                printf("\n\tIncorrect PIN.");
                                printf("\n\tSorry,Unable to open note.");
                                found=5;
                                break;
                              }
                          }else
                          {
                              break;
                              found=5;
                          }
                      }else
                      {
                          found=RestOrSetPIN(tracking,27);
                      }
                   }

                }
            }
        }
        break;
    default:
        printf("\n\tInvalid Choice\n");
    }

    /**Asking whether to continue with operation**/
    if(opt==1)
    {
        exit(0);
    }else
    printf("\n\n\tDo you want to continue[s/n]: ");
    scanf("%s",continueopt);
    strcpy(continueopt,strupr(continueopt));

 }while(!strcmp(continueopt,"S"));

    return 0;
}
//Bugs that has to be fixed!
/*******************************
1.There is bug while renaming a note name(first letter of note name is getting discarded).
2.There is misleading output statement when user enters wrong
PIN for editing the note.
*****************************************/

