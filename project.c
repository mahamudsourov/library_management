#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define IN 1
#define OUT 0
void Addbook();
void Searchbook();
void viewbook();
void viewbook2();
void Author();
void Name();
void Exit();
void adminMode();
void userMode();
char info[500];
struct
{
    int bid;
    char bname[25];
    char author[25];
    int nooftitles;
    char titles[500];
    int status;
} book;
struct
{
    int mid;
    char mname[25];
    char department[25];
    int availibcard;
    int phno;
} membr;
//initializing the files used in the program
FILE *librecord;
FILE *membrrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;
int main()
{
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Library management System Project in C       ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t----------------------------------------------------------------------------");
    printf("\n\n");
    while(1)
    {
    int n;
    printf("1.Admin Mode\n");
    printf("2.User Mode\n");
    printf("\nEnter any choice: ");
    scanf("%d",&n);
        char user[20],pass[20];
        if(n==1)
        {
        printf("Username :");
        fflush(stdin);
        gets( user);
        printf("Password :");
        gets( pass);
        if(strcmp(user,"admin")==0 && strcmp(pass,"1111")==0)
        {
            adminMode();
            break;
        }
        else
        {
            printf("Wrong Password !! Try Again\n");
        }
    }
    else if(n==2)
    {
        printf("Username :");
        fflush(stdin);
        gets( user);
        printf("Password :");
        gets( pass);
        if(strcmp(user,"user")==0 && strcmp(pass,"2222")==0)
        {
            userMode();
            break;
        }
        else
        {
            printf("Wrong Password !! Try Again\n");
        }
    }else
    {
        printf("Wrong Password !!! Try Again\n");
    }
}
}
void adminMode()
{
    printf("\n");
    printf("Admin Mode:\n");
    printf("1.Add Book\n");
    printf("2.Search Book by Author Name\n");
    printf("3.Search Book by Book Name\n");
    printf("4.View book\n");
    printf("5.Exit\n");

    int choice =0;
    do{
    printf("Enter Choice: ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        Addbook();
        break;
    case 2:
        Author();
        break;
    case 3:
        Name();
        break;
    case 4:
        viewbook();
        break;
        case 5:
        Exit();
    default:
        printf(" ! Invalid Input...\n");
    }

}while(choice!=5);
return (0);
}
//User Mode
void Addbook()
{
    int i;
    book.status=IN;
    //opening the librecord file
    librecord = fopen("librecord.txt","a+");
    printf("Enter The uniqueid of The Book :(Integer) \n");
    scanf("%d",&book.bid);
    printf("Enter The Name of The Book :\n");
    fflush(stdin);
    scanf("%s",book.bname);
    printf("Enter The Name of Author :\n");
    scanf("%s",book.author);
    printf("Enter The Number of Titles Of The Book:(Integer)\n");
    fflush(stdin);
    scanf("%d",&book.nooftitles);
    fprintf(librecord,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,book.status,book.nooftitles);
    printf("Enter The Titles Of The Book : \n");
    for(i=0; i<book.nooftitles; i++)
    {
        scanf("%s",book.titles);
        fprintf(librecord,"%s\t",book.titles);
    }
    fclose(librecord);
    printf(" (' ' ) A New Book has been Added Successfully...\n");
}

void viewbook()
{
    librecord = fopen("librecord.txt","a+");
    printf("\nBookid\tName\tAuthor\tStatus\tNo.\tTitles\n",info);
    do
    {
        fgets(info,500,librecord);
        printf("%s\n",info);
    }
    while(!feof(librecord));
    fclose(librecord);
    membrrecord = fopen("membrrecord.txt","a+");
    printf("\nMid\tName\tDept\tPh.no\tAvailablecards\n");
    do
    {
        fgets(info,500,membrrecord);
        printf("%s\n",info);
    }
    while(!feof(membrrecord));
    fclose(membrrecord);

}
void Author()
{
    int i;
    char Target[500];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf(" ! The file is empty... \n\n");
    else
    {
        printf("\nEnter The Name Of Author : ");
        scanf("%s",Target);
        printf("\nBooks:");
        while(!feof(librecord))
        {
            fscanf(librecord,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.nooftitles);
            if(strcmp(Target,book.author)==0)
            {
                Found=1;
                printf("%s\n",book.bname);
            }
            for(i=0; i<book.nooftitles; i++)
                fscanf(librecord,"%s",book.titles);
        }
        if(!Found)
            printf(" ! There is no such Entry...\n");
        fclose(librecord);
    }
}
void Name()
{
    int i;
    char Target[500];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        printf("\nEnter The Book Name :");
        scanf("%s",Target);
        while(!feof(librecord)&& Found==0)
        {
            fscanf(librecord,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.nooftitles);
            if(strcmp(Target,book.bname)==0)
            {
                Found=1;
                break;
            }
            for(i=0; i<book.nooftitles; i++)
                fscanf(librecord,"%s",book.titles);
        }
        if(Found)
        {
            printf("The Name of book is:               %s\n",book.bname);
            printf("\nThe Titles:\n");
            for(i=0; i<book.nooftitles; i++)
            {
                fscanf(librecord,"%s",book.titles);
                printf("%d.%s......\n",i+1,book.titles);
            }
        }
        else if(!Found)
            printf(" ! There is no such Entry...\n");
        fclose(librecord);
    }

}

void userMode()
{
    printf("\n");
    printf("User Mode:\n");
    printf("1.Search Book\n");
    printf("2.Book Lists\n");
    printf("3.Borrow Books\n");
    printf("4.Deposit Books\n");
    printf("5.Exit\n");

    int choice =0;
    do{
    printf("Enter Choice: ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        Searchbook();
        break;
    case 2:
        viewbook2();
        break;
    case 3:
        borrowbook();
        break;
        case 4:
        depositbook();
        break;
         case 5:
        Exit();
    default:
        printf(" ! Invalid Input...\n");
    }
}while(choice!=5);
return 0;
}
void Searchbook()
{
    int i;
    char Target[25],stats[3];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf(" ! The File is Empty...\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
            scanf("%s",Target);
        while(!feof(librecord)&& Found==0)
        {
        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
            if(strcmp(Target,book.bname)==0)
                Found=1;
            for(i=0;i<book.nooftitles;i++)
                fscanf(librecord,"%s",book.titles);
        }
        if(Found)
        {
            if(book.status==IN)
                strcpy(stats,"IN");
            else
                strcpy(stats,"OUT");

            printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\n\n",book.bid,book.bname,book.author,stats);
            }
        else if(!Found)
            printf("! There is no such Entry...\n");
        fclose(librecord);
    }

}
void viewbook2()
{
    librecord = fopen("librecord.txt","a+");
    printf("\nBookid\tName\tAuthor\tStatus\tNo.\tTitles\n",info);
    do
    {
        fgets(info,500,librecord);
        printf("%s\n",info);
    }
    while(!feof(librecord));
    fclose(librecord);
    membrrecord = fopen("membrrecord.txt","a+");
    printf("\nMid\tName\tDept\tPh.no\tAvailablecards\n");
    do
    {
        fgets(info,500,membrrecord);
        printf("%s\n",info);
    }
    while(!feof(membrrecord));
    fclose(membrrecord);

}
void borrowbook()
{
    int mid,i,Found1=0,Found2=0;char issubookname[20];
    //temp1=librecord;temp2=membrrecord;
    printf("\nEnter The userid of the Member : \n");
        scanf("%d",&mid);
    if((membrrecord=fopen("membrrecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(membrrecord)&& Found1==0)
        {
            fscanf(membrrecord,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);
            if(mid==membr.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard<1)
            {
                printf(" ! Library card not available...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",issubookname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    printf(" ! The file is empty...\n\n");
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                        if(strcmp(issubookname,book.bname)==0)
                            Found2=1;
                        for(i=0;i<book.nooftitles;i++)
                            fscanf(librecord,"%s",book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status==0)
                        {
                            printf(" ! Book already issued...\n");
                        }
                        else
                        {

                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("membrrecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);


                                    if(mid==membr.mid)
                                    {
                                        membr.availibcard--;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,    membr.availibcard);
                                    }
                                    else{
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,membr.availibcard);}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);


                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(issubookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",book.bid,book.bname,book.author,book.status,book.nooftitles);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,0,book.nooftitles);
                                    }
                                    for(i=0;i<book.nooftitles;i++)
                                    {
                                        fscanf(temp1,"%s",book.titles);
                                        fprintf(fp1,"%s\t",book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(membrrecord);
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                            remove("membrrecord.txt");
                            rename("fp2.txt","membrrecord.txt");
                            printf(" (' ') Book Successfully borrowed...\n");
                        }
                    }
                    else if(!Found2)
                        printf(" ! There is no such Book...\n");

                }
            }
        }
        else if(!Found1)
            printf(" ! Invalid User id...\n");


    }

}
void depositbook()
{
int mid,i,Found1=0,Found2=0,flag=0;char retbookname[20];
    temp1=librecord;temp2=membrrecord;
    printf("\nEnter The userid of the Member :\n");
        scanf("%d",&mid);
    if((membrrecord=fopen("membrrecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(membrrecord)&& Found1==0)
        {
            fscanf(membrrecord,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);
            if(mid==membr.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard>=5)
            {
                printf(" ! Error...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",retbookname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    printf(" ! The file is empty\n\n");
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                        if(strcmp(retbookname,book.bname)==0)
                        Found2=1;
                        for(i=0;i<book.nooftitles;i++)
                            fscanf(librecord,"%s",book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status==1)
                        {
                            printf(" ! Error:Book already in stock...\n");
                        }
                        else
                        {

                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("membrrecord.txt","a+"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);


                                    if(mid==membr.mid)
                                    {
                                        membr.availibcard++;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,    membr.availibcard);
                                    }
                                    else
                                    {
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,membr.availibcard);
                                    }
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);


                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(retbookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",book.bid,book.bname,book.author,book.status,book.nooftitles);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,1,book.nooftitles);
                                    }
                                    for(i=0;i<book.nooftitles;i++)
                                    {
                                        fscanf(temp1,"%s",book.titles);
                                        fprintf(fp1,"%s\t",book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(membrrecord);
                            printf("('') Book Successfully Returned...\n");
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                            remove("membrrecord.txt");
                            rename("fp2.txt","membrrecord.txt");

                        }
                    }
                    else if(!Found2)
                        printf("! There is no such Book...\n");

                }
            }
        }
        else if(!Found1)
            printf("! Invalid User id...\n");

    }


}
void Exit()
{
  exit(0);
}
