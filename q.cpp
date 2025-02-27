#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //for close
#include <stdio.h>

#include <iostream>
using namespace std;

int main() {
 
 char filename1[13]="./myfile.txt";
 int fd1=open(filename1, O_RDWR);
 
 if (fd1==-1) {
   cout<<"File1 could not open!"<<endl;
   return 1;
 }
 
 cout << "File1 opened successfully\n";

 char *map1= (char*) mmap(NULL, 100, PROT_READ, MAP_SHARED, fd1, 0);
 close(fd1); //updated
 
 if (map1==MAP_FAILED)
 {
   cout<<"File1 could not be memory mapped!"<<endl;
   return 1;
 }
 cout << "File1 mapped successfully\n";


 //Write in another file

 /*char filename2[14]="./myfile2.txt";
 int fd2=open(filename2, O_RDWR);
 
 if (fd2==-1)
 {
   cout<<"File2 could not open!"<<endl;
   return 1;
 }
 cout << "File2 opened successfully\n";
 
 char *map2= (char*) mmap(NULL, 100, PROT_WRITE, MAP_SHARED, fd2, 0);
 close(fd2); //updated
 
 if (map2==MAP_FAILED)
 {
   cout<<"File2 could not be memory mapped!"<<endl;
   return 1;
 }
 cout << "File2 opened successfully\n"; */

 FILE *fp;
 fp = fopen("myfile2.txt", "w");

//ASCI 0=48,  9=57
 
int i;

 for (i=0; i<100; i++){
 	if(map1[i] >= 48 && map1[i] <= 57 ){
 		cout<<map1[i];
 		fputc(map1[i], fp);	
 	} 	 
 }
 
 munmap(map1, 100); //to destroy

 cout <<endl << "Done till here\n";
return 0;
}