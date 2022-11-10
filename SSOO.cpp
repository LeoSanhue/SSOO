#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h> 
#include <unistd.h>
#include <pthread.h> 

 using namespace std;

 static string host;
 static string ping_again;

void * ping (void * arg){
   system("cls");
   cout  << "Host: ";
   cin   >> host ; 
   system(("ping " + host).c_str());
   cout  << endl;
   cout  << "Y(es) or N(o)\n\n";
   cout  << "Ping another host: ";
   cin   >> ping_again;
   if(ping_again == "Y"|| ping_again == "y")
   {
      system,("cls");
      ping(arg);
   }else if(ping_again == "N" || ping_again == "n")
   {
      system("exit");
   }
}
void * ping1(void * arg){
   system("cls");
   host = "www.qacengr.com" ;
   system(("ping " + host).c_str());
   sleep(1); 
   cout << endl;
}
void * ping2(void * arg){
   system("cls");
   host = "8.8.8.8" ;
   system(("ping " + host).c_str());
   sleep(2); 
   cout << endl;
}
void * ping3(void * arg){
   system("cls");
   host = "myspace.cl" ;
   system(("ping " + host).c_str());
   sleep(3); 
   cout << endl;
}
void * ping4(void * arg){
   system("cls");
   host = "1.1.1.1" ;
   system(("ping " + host).c_str());
   sleep(4); 
   cout << endl;
}
int main () 
{  
   pthread_t p1,p2,p3,p4;
   pthread_create(&p1, NULL, &ping1, NULL);
   pthread_create(&p2, NULL, &ping2, NULL);
   pthread_create(&p3, NULL, &ping3, NULL);
   pthread_create(&p4, NULL, &ping4, NULL);
   pthread_join(p1,NULL);
   pthread_join(p2,NULL);
   pthread_join(p3,NULL);
   pthread_join(p4,NULL);

   return 0;  
}