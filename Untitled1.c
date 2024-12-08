system("clear");
        /**Accessing all note for searching**/
        while(fread(&notes,sizeof(App),1,fp))
        {
         /**Searching Note name with search name**/
        if(!strcmp(notes.name,searchname))
          {
            /**Displaying information if found and search tracking will have 1 value**/
            printf("\t\t\t\t%d.%s\n\n",n+1,notes.name);
            for(int i=0;i<notes.NumberOFLines;i++)
                printf("%s\n",notes.SpaceOfNote[i]);
            printf("\n\t\t\t\t\tCreated:%s %s",notes.CreatedDate,notes.Createdtime);
            printf("\n\t\t\t\t\tLast modified:%s %s\n",notes.ModifiedDate,notes.Modifiedtime);
            printf("-------------------------------------------------------------------------\n");
            found=1;
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
