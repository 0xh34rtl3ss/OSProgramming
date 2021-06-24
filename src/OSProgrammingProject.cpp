#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;



void clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}

void GetNumberofResources( int *m, string str){ //tujuan: nk kira ada brapa resources

    int count=1;
    string word = "";

    for (auto x : str) 
    {
        
        if (x == ' ')
        {   
            
            // cout<<word << endl;
            count++;
            word = "";
        }
        else {
            word = word + x;
        }
    }
    count++;
    *m = count;
    // cout <<word << endl;

}




int parseValue( vector<int> &arr, string str){

    string word = "";
    bool passed=true;
   
    for (auto x : str) 
    {
        
        if (x == ' ')
        {   
             //cout<<word << endl;
           
            try{
              arr.push_back(stoi(word));
            
            }
            catch (exception& e) {
	          cout << "Error reading annotations. No space at the front and end please ";
            return 0;
            }
     

          // *((arr+ *(rows))+(count)) = stoi(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    
    try{
    arr.push_back(stoi(word));
    return 1;
    }
    catch (exception& e) {
	          cout << "Error reading annotations. No space at the front and end please ";
            return 0;
    }




}



void SafeSequence (int *noProcess, int *noResources, vector<int> &allocation, vector<int> &maximum, vector<int> &resources, int thread, vector<int> &input  ){



    int n = *noProcess; // Number of processes
    int m = *noResources; // Number of resources
    vector <int>temp_avail;

  


   // cout<<"m2: "<<m<<endl;


     int alloc[n][m] ; //buat array and masukkan value vector ke dalam array
    for(int i=0; i<n; i++){
     for(int j=0; j<m; j++){
       alloc[i][j] = allocation[ (i*m) + j];
     }
    }


    int max[n][m];//buat array and masukkan value vector ke dalam array
    for(int i=0; i<n; i++){
     for(int j=0; j<m; j++){
       max[i][j] = maximum[ (i*m) + j];
     }
    }


    int avail[m];//buat array and masukkan value vector ke dalam array

    for(int i=0; i<m; i++){
        avail[i]=0;
    }

   // cout<<allocation.size()<<" "<<avail[0]<<endl;


    for(int c=0; c<m; c++){
        for(int j=c; j<allocation.size(); j=j+m){
            avail[c] += allocation[j];
     }
    }

    for(int v=0; v<m; v++){
        avail[v] = resources[v]-avail[v];
    }

    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }


 
     
  //process the request
  if(thread>=0){
    int tempNeed=0;
    int tempRequest=0;
    int tempAvail=0;
    int tempAlloc=0;
    // int rows = thread*4;

    int start= pow(10,(m-1));
   // cout<<"start: "<<start<<endl;

    int j=0; //dapatkan int from array sebab nk compare
    while(start>=1 && j<m){
      tempNeed += (need[thread][j]*start);
      tempRequest += (input[j+1]*start);
      tempAvail += (avail[j]*start);
      tempAlloc += (alloc[thread][j]*start);
      

      j++;
      start= start/10; 
    }


    if(tempRequest<=tempNeed && tempRequest<=tempAvail){


      //update values to the one requested
      tempAvail = tempAvail - tempRequest; 
      tempAlloc = tempAlloc + tempRequest;
      tempNeed = tempNeed - tempRequest;



      //reset the values to 0
      for(int i=0; i<m; i++){
        need[thread][i]=0;
        avail[i]=0;
        alloc[thread][i]=0;
      }

      //saving the new values
      int j= (m-1);
      while (tempAvail > 0 && j>=0 ) {
      avail[j] = ( tempAvail % 10);
      j--;
      tempAvail = tempAvail / 10;
      }

        for(int i=0; i<m; i++){
        temp_avail.push_back(avail[i]);
      }

      int l= (m-1);
      while (tempAlloc > 0 && l>=0 ) {
      alloc[thread][l] = ( tempAlloc % 10);
      l--;
      tempAlloc = tempAlloc / 10;
      }

     
      int u= (m-1);
      while (tempNeed > 0 && u>=0 ) {
      need[thread][u] = ( tempNeed % 10);
      u--;
      tempNeed = tempNeed / 10;
      }

        //bankers algo here
    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

    int y = 0;
    int counter=0;
    for (int k = 0; k < n; k++) { //initiallly 5
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
  
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                        
                        break;
                    }
                }
  
                if (flag == 0) {
                    ans[ind++] = i;
                    counter++;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    if(counter==n){

        // //display all arrays
    clear_screen();

    bool displayed=false;
    cout<<"alloc"<<"\t"<<"max"<<setw(10)<<"avail"<<setw(10)<<"need"<<endl;
    for(int x=0; x<n; x++){ //m=no of resources
    cout<<endl;
      for(int j=0; j<4; j++){
        if(j==0){
          for(int y=0; y<m; y++){
            cout<<alloc[x][y]<<" ";
          }
          cout<<"\t";
        }
        else if(j==1){

          for(int y=0; y<m; y++){
            cout<<max[x][y]<<" ";
          }
          cout<<"\t";
        }
        else if(j==2){

          if(displayed==1){
            for(int y=0; y<m; y++){
            cout<<"  ";
            }
            cout<<"\t";
          }
          
          
          else{

          for(int y=0; y<temp_avail.size(); y++){
            cout<<temp_avail[y]<<" ";
          }
          cout<<"\t";
          displayed=1;

          }        

          }

        
        else if(j==3){

          for(int y=0; y<m; y++){
            cout<<need[x][y]<<" ";
          }
          cout<<"\t";

        }
      
      }
      
    }
    


      cout << "\n\n0" << endl;
      for (int i = 0; i < n - 1; i++)
        cout << " Thread " << ans[i] << ",";
      cout << " Thread " << ans[n - 1] <<endl;



    }
    else{
    clear_screen();
       cout<<"-1"<<endl;
    }



    }
    else{
    clear_screen();
      cout<<"-1"<<endl;

    }
    
  }
  else{


       bool displayed=false;
    cout<<"alloc"<<"\t"<<"max"<<setw(10)<<"avail"<<setw(10)<<"need"<<endl;
    for(int x=0; x<n; x++){ //m=no of resources
    cout<<endl;
      for(int j=0; j<4; j++){
        if(j==0){
          for(int y=0; y<m; y++){
            cout<<alloc[x][y]<<" ";
          }
          cout<<"\t";
        }
        else if(j==1){

          for(int y=0; y<m; y++){
            cout<<max[x][y]<<" ";
          }
          cout<<"\t";
        }
        else if(j==2){

          if(displayed==1){
            for(int y=0; y<m; y++){
            cout<<"  ";
            }
            cout<<"\t";
          }
          
          
          else{

          for(int y=0; y<m; y++){
            cout<<avail[y]<<" ";
          }
          cout<<"\t";
          displayed=1;

          }        

          }

        
        else if(j==3){

          for(int y=0; y<m; y++){
            cout<<need[x][y]<<" ";
          }
          cout<<"\t";

        }
      
      }
      
    }

    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

        int y = 0;
    int counter=0;
    for (int k = 0; k < n; k++) { //initiallly 5
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
  
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                        
                        break;
                    }
                }
  
                if (flag == 0) {
                    ans[ind++] = i;
                    counter++;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

          cout << "\n\n0" << endl;
      for (int i = 0; i < n - 1; i++)
        cout << " Thread " << ans[i] << ",";
      cout << " Thread " << ans[n - 1] <<endl;





  }

    



    
    
    



}

int main(){


    
    int m = 0 ; //number of resources
    int NoProcess = 0;


    string myText;
    int countline=1;
    

    // Read from the text file
    ifstream MyReadFile("../inputfile.txt");
    cout<<"opening file..."<<endl;
    
    

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) { //tujuan: nak kira number of line dlm txt and number of resources
        
        if(countline==2){
         GetNumberofResources(&m,myText);
        }
        countline++;

    }
    MyReadFile.close();
    cout<<"file read succesfully..."<<endl;
    countline--;
    m--;




    //count how many process are there in the txt
    NoProcess = (countline-6)/2;

    //initialize kan all the vectors
    vector<int> resources;
    vector<int> maximum;
    vector<int> allocation;
    vector<int> available;
    bool okreadfile=true;


    int line=1;



    cout<<"total no of line: "<<countline<<endl;
    cout<<"no of resources: "<<m<<endl;
    cout<<"no of processes: "<<NoProcess<<endl;

    if(countline <= 7 || ( countline >7 && countline%2!=0) ){
        cout<<"insufficient/unbalanced values in inputfile.txt!"<<endl; //nak make sure yang number of matrix balanced
    }

    else{ //baru ambik values2 dlm notepad

   cout<<"importing values from file..."<<endl;
    ifstream MyReadFile2("../inputfile.txt"); 



     while ( getline (MyReadFile2, myText) ){


         if(line==2){
             int i=0;
             if(parseValue(resources, myText) ==0){
                cout<<">> at line ["<<line<<"]"<<endl;
                okreadfile=0;
             }
             line++;

         }
         else if(line>=5 && line <= ((5+NoProcess)-1)){
             
             if(parseValue(maximum, myText) ==0){
                cout<<">> at line ["<<line<<"]"<<endl;
                okreadfile=0;
             }
        
             line++;

             

         }
         else if(line > (((5+NoProcess)-1)+2) && line <= countline ){
            if(parseValue(allocation, myText) ==0){
                cout<<">> at line ["<<line<<"]"<<endl;
                okreadfile=0;
             }
             line++;

         }
         else{
             line++;
         }

    }
    
    MyReadFile2.close();
    cout<<"successfully importing values from file..."<<endl;

    string userinput="1";
    vector<int> uservalues;

    SafeSequence(&NoProcess,&m,allocation,maximum,resources,-1,uservalues);

    
  if(okreadfile==1){
    do{
      cout<<"\nEnter your request: ";
      getline(cin, userinput);
      if(parseValue(uservalues, userinput) ==0){
        //break;
        uservalues.clear();
      }
        else{
             if(uservalues.size() == (m+1)){ //check user input cukup tk value
            
              SafeSequence(&NoProcess,&m,allocation,maximum,resources,uservalues[0],uservalues);
               uservalues.clear();
               // break;
               }
              else{
                   uservalues.clear();
                  }
            }


    }while(userinput!="0");

  }



    

    }
    
  cout<<"unable to run the program, fix the inputfile.txt first"<<endl;
    

    
    

    return 0;
}
