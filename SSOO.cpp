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
#include <semaphore.h>

 using namespace std;
 sem_t sem;
 int ipcount = 0;
 char *ipdata[100];
 static string host;
 static string ping_again;

///HILOS/////////////////////////////////////////////////////////////////////////////////////////
struct thread_data{
   int thread_id;
   int sum;
   char *ip;
};

struct thread_data thread_data_array[100];


/////////PINGS/////////////////////////////////////////////////////////////////
// display linked list contents

void *Print(void *threadarg)
{
   int taskid, sum;
   char *ip;
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;
   taskid = my_data->thread_id;
   sum = my_data->sum;
   ip = my_data->ip;
   std::string aux = std::string(ip);
   system(("ping -c 2 " + aux).c_str());
   sleep(1);
   printf("Thread %d: %s  Sum=%d\n", taskid, ip, sum);
   pthread_exit(NULL);
}

////////////main////////////////////////////////////////////////////////////
int main (){

   struct Node* head = NULL; 
   //sem_init(&sem,0,NULL);
   

   ifstream archivo;
   std::string texto;
   int i = 0;
   archivo.open("archivo_listado_ips.txt",ios::in);
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
      printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
   }
  }
   pthread_exit(NULL);
   return 0;  
}