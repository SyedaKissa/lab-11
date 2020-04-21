#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //for close

#include <iostream>
using namespace std;

int main()
{
 
 char filename1[13]="./myfile.txt";
 int fd1=open(filename1, O_RDWR);
 
 if (fd1==-1)
 {
   cout<<"File could not open!"<<endl;
   return 1;
 }
 
 cout << "File opened suc\n";

 char *map1= (char*) mmap(NULL, 100, PROT_READ, MAP_SHARED, fd1, 0);
 close(fd1); //updated
 
 if (map1==MAP_FAILED)
 {
   cout<<"File could not be memory mapped!"<<endl;
   return 1;
 }



 //Write in another file

 char filename2[14]="./myfile2.txt";
 int fd2=open(filename2, O_RDWR);
 
 if (fd2==-1)
 {
   cout<<"File could not open!"<<endl;
   return 1;
 }
 
 char *map2= (char*) mmap(NULL, 100, PROT_WRITE, MAP_SHARED, fd2, 0);
 close(fd2); //updated
 
 if (map2==MAP_FAILED)
 {
   cout<<"File could not be memory mapped!"<<endl;
   return 1;
 }


//Screen + another file

//ASCI 0=48,  9=57
 int j = 0;
 for (int i=0; i<100; i++)
 {
 	if(map1[i] >= 48 && map1[i] ){
 		cout<<map1[i];
 		map2[j] = map1[i];
 	}  
 	j++; 
 }
 cout<<"Now map2" <<endl;

 for(int i = 0; i < 100; i++){
 	cout<<map2[i];
 }
 cout<<endl;

 //map[0]='B'; To change

 cout <<"Done till here\n";

 munmap(map1, 100); //to destroy
 munmap(map2, 100); //to destroy

return 0;
}