#include <stdio.h>
#include <string.h>

int chklength(char string[]);
int chkduplicate(char string[10][25],char ch[],int x);
void ascsort(char string[10][25]);
void descsort(char string[10][25]);

int main()
{
    char string[10][25],chr;
    int i=0,j=0,s=0,ad;
    printf("Enter 10 strings :\n");
    while(i<10)
    {
    printf("Enter the string %d: " ,i+1);
    fgets(string[i],50,stdin);
    if(chklength(string[i]) || chkduplicate(string,string[i],i))
    {
        printf("Please re - Enter string : \n");
    }
    else
    {
        i++;
    }
    }
    printf("Enter 'A' for ascending and 'D' for descending\n");
    while(s==0)
    {
    scanf("%c",&chr);
    if(chr=='A')
    {
        ascsort(string);
        s=1;
    }
    else if (chr=='D')
    {
        descsort(string);
        s=1;
    }
    else{
        printf("Error: Please enter A or D \n");
        s=0;
        continue;
    }
    }
    printf("The strings after sorting :\n");
	for(j=0;j<=9;j++){
		 puts(string[j]);
	}
	ad=strcmp(string[0],string[9]);
	if (ad>1)
	{
	printf("String with lowest ASCII value is : ");
	puts(string[9]);
	printf("String with highest ASCII value is : ");
	puts(string[0]);
	}
	else{
	printf("String with lowest ASCII value is : ");
	puts(string[0]);
	printf("String with highest ASCII value is : ");
	puts(string[9]);    
	}
    return 0;
}

// Checking the Length of the string whether it is between 1 to 25 characters

int chklength(char string[])
{
    int i=0,flag=0;
    
    if(strlen(string)>26){
    printf("Error: String length should be between 1 to 25 inclusive \n");
    flag=1;
    }
    
     if(strlen(string)-1<1){
    printf("Error: String length is 0\n");
    flag=1;
    }
    
    for (i = 0; i <=strlen(string); i++)
    {
    if(string[i] == '!'|| string[i] =='@'|| string[i] =='#'|| string[i] =='$'|| string[i] == '%'|| string[i] == '^'|| string[i] == '('|| string[i] == ')' || string[i] == '*')
    {
    printf("Error: String contains invalid characters\n");
    flag=1;
    break;
    }
    }
     if(flag==1){
         return 1;
     }
     else{
    return 0;
}
}

// Checking for the duplicate strings

int chkduplicate(char string[10][25],char ch[],int x)
{
    int h=0, flag=0;
    while(h<x){
    if(strcmp(string[h],ch)==0){
    flag=1;
    break;
    }
    h++;
    }
    if(flag==1){
        printf("Error:Duplicate string entered\n");
        return 1;
    }
    else{
        return 0;
    }
}

// Sorting the input in ascending order :

void ascsort(char string[10][25])
{
    int i,j;
    char temp[25];
	for(i=0;i<=9;i++)
    {
    for(j=i+1;j<=9;j++)
	{
	  if(strcmp(string[i],string[j])>0)
	  { 
        strcpy(temp,string[i]);
	    strcpy(string[i],string[j]);
	    strcpy(string[j],temp);
	  }
	}
    }
}

// Sorting the array in Descending order :

void descsort(char string[10][25])
{
    int i,j;
    char t[25];
    for(i=0;i<=9;i++)
    {
    for(j=i+1;j<=9;j++)
	{
	  if(strcmp(string[i],string[j])<0)
	  { 
        strcpy(t,string[i]);
	    strcpy(string[i],string[j]);
	    strcpy(string[j],t);
	  }
	}
}
}