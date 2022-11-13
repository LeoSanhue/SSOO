#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <pthread.h> 
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
#include <cstdio>
//#include "ping.h"
#include <semaphore.h>

 using namespace std;
 int ipcount = 0;
 char *ipdata[100];
 static string host;
 static string ping_again;
 sem_t sem;
///////LINK list/////////////////////////////////////////////////////////////////////////////////
struct Node
{
   string data;
   struct Node *next;
};
void push(struct Node** head, string node_data)
{
   struct Node* newNode = new Node;
 
   newNode->data = node_data;
 
   newNode->next = (*head);
 
   (*head) = newNode;
}
 
void insertAfter(struct Node* prev_node, string node_data)
{
if (prev_node == NULL)
{
   cout<<"the given previous node is required,cannot be NULL"; return; } 
 
   struct Node* newNode =new Node; 
 
   newNode->data = node_data;
 
   newNode->next = prev_node->next;
 
    prev_node->next = newNode;
}
 
void append(struct Node** head, string node_data)
{
struct Node* newNode = new Node;
 
struct Node *last = *head; 
 
newNode->data = node_data;
 
newNode->next = NULL;
 
if (*head == NULL)
{
*head = newNode;
return;
}
 
while (last->next != NULL)
last = last->next;
 
last->next = newNode;
return;
}
 
void displayList(struct Node *node)
{
   while (node != NULL)
   {
      cout<<node->data<<"-->";
      node = node->next;
   }
 
if(node== NULL)
cout<<"null"; 
} 

///HILOS/////////////////////////////////////////////////////////////////////////////////////////
struct thread_data{
   int thread_id;
   int sum;
   char *ip;
};

struct thread_data thread_data_array[100];


/////////PINGS/////////////////////////////////////////////////////////////////
// display linked list contents
void printDesign(){
   std::string Banner;
   Banner =         "IP            Trans.      Rec.       Perd.      Estado\n";
   cout << Banner + "------------------------------------------------------\n";
}

string Proc1 (string text){
   string ip;
   //cout << text;
   for(int i=0;i<12;i++){
   ip += text[5+i] +"  ";
   }
   return ip; 
}
string Proc2 (string text){
   string t,r,plf, st = "DOWN";
   int pl;
   stringstream apl;
   //cout << text;
         t = text[0];
         r = text[23];         
   pl = std::stoi(t)-std::stoi(r);
   if (std::stoi(r)>0){
      st = "  UP";
   }
   apl << pl;
   apl >> plf;
   text = t+"          "+r+"           "+plf+"         "+st+"\n";
   return text;
}



void *Print(void *threadarg)
{  
   int taskid, sum;
   char *ip;
   struct thread_data *my_data;
   ifstream archive;
   std::string text;
   std::string in;
   int i;

   my_data = (struct thread_data *) threadarg;
   taskid = my_data->thread_id;
   sum = my_data->sum;
   ip = my_data->ip;

   std::string aux = std::string(ip);
   system(("ping -c 2 " + aux + "> rping.txt").c_str());
   sleep(1);

   archive.open("rping.txt",ios::in);
   if(archive.fail()){
      cout << "No se pudo abrir el archivo\n";
      exit(1);
   }else{
       i = 0;
       while(!archive.eof()){
       getline(archive,text);
       //cout << text << endl;
       if(i==0){
         in = Proc1(text);
         cout << aux + "     ";
       }
       if(i==3){
         in = Proc2(text);
         cout << in ;
       }
       i++;
      }
      archive.close();
      system("rm rping.txt");
   }
   pthread_exit(NULL);

}





////////////main////////////////////////////////////////////////////////////
int main(int argc, char const *argv[]){

   string nombreArchivo = argv[1];
   struct Node* head = NULL; 
   std::string texto;
   ifstream archivo(nombreArchivo.c_str());
   if(archivo.fail()){
      cout << "No se pudo abrir el archivo\n";
      exit(1);
   }else{
      while(!archivo.eof()){
         getline(archivo,texto);
         //cout << texto << endl;
         texto.erase(remove_if(texto.begin(),texto.end(),::isspace),texto.end());
         std::string str = texto;
         char *cstr = new char[str.length() + 1];
         ipdata[ipcount]=strcpy(cstr, str.c_str());
         ipcount++;
      }
      archivo.close();
   }
   

   pthread_t p[ipcount];
   int *taskids;
   int t,sum,rc;
   sum=0;
   

   printDesign();
   for (t=0;t<ipcount;t++){
     sum = sum + t;
     thread_data_array[t].thread_id = t;
     thread_data_array[t].sum=sum;
     thread_data_array[t].ip=ipdata[t];
     printf("Creating thread %d\n", t);
      
      rc = pthread_create(&p[t], NULL, Print, (void *) 
        &thread_data_array[t]);
         pthread_join(p[t],NULL);

   if (rc) {
      printf("ERROR  %d\n", rc);
    exit(-1);
   }
  }
   pthread_exit(NULL);
   return 0;  
}