#include<iostream>
#include<string>
#include <fstream>
#include<vector>

using namespace std;




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




void parseValue( vector<int> &arr, string str){

    string word = "";
   

    for (auto x : str) 
    {
        
        if (x == ' ')
        {   
             //cout<<word << endl;
            arr.push_back(stoi(word));
          // *((arr+ *(rows))+(count)) = stoi(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    
    arr.push_back(stoi(word));



}


void SafeSequence (int *noProcess, int *noResources, vector<int> &allocation, vector<int> &maximum, vector<int> &resources  ){



    int n = *noProcess; // Number of processes
    int m = *noResources; // Number of resources

    cout<<"m2: "<<m<<endl;


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

    cout<<allocation.size()<<" "<<avail[0]<<endl;


    for(int c=0; c<m; c++){
        for(int j=c; j<allocation.size(); j=j+m){
            avail[c] += allocation[j];
     }
    }

    for(int v=0; v<m; v++){
        avail[v] = resources[v]-avail[v];
    }
     




    

    //display all arrays
    cout<<"m: "<<m<<" n: "<<n<<endl;

    cout<<"\nalloc: ";
    for(int x=0; x<n; x++){
        cout<<endl;
        for(int y=0; y<m; y++){
            cout<<alloc[x][y]<<" ";
        }
    }

    cout<<"\n\nmax: ";
    for(int x=0; x<n; x++){
        cout<<endl;
        for(int y=0; y<m; y++){
            cout<<max[x][y]<<" ";
        }
    }

        cout<<"\n\navail: "<<endl;
        for(int y=0; y<m; y++){
            cout<<avail[y]<<" ";
        }
    
    
  //bankers algo here
    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (int k = 0; k < 5; k++) {
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
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
  
    cout << "\n\nFollowing is the SAFE Sequence" << endl;
    for (int i = 0; i < n - 1; i++)
        cout << " Thread " << ans[i] << ",";
    cout << " Thread " << ans[n - 1] <<endl;


}

int main(){


    
    int m = 0 ; //number of resources
    int NoProcess = 0;


    string myText;
    int countline=1;
    

    // Read from the text file
    ifstream MyReadFile("../inputfile.txt");
    
    

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) { //tujuan: nak kira number of line dlm txt and number of resources
        
        if(countline==2){
         GetNumberofResources(&m,myText);
        }
        countline++;

    }
    MyReadFile.close();
    countline--;
    m--;




    //count how many process are there in the txt
    NoProcess = (countline-6)/2;

    //initialize kan all the vectors
    vector<int> resources;
    vector<int> maximum;
    vector<int> allocation;
    vector<int> available;


    int line=1;



    cout<<"total line: "<<countline<<endl;
    cout<<"no of resources: "<<m<<endl;
    cout<<"no of processes: "<<NoProcess<<endl;

    if(countline <= 7 || ( countline >7 && countline%2!=0) ){
        cout<<"insufficient/unbalanced values in inputfile.txt!"<<endl; //nak make sure yang number of matrix balanced
    }

    else{ //baru ambik values2 dlm notepad

   
    ifstream MyReadFile2("../inputfile.txt"); 



     while ( getline (MyReadFile2, myText) ){


         if(line==2){
             int i=0;
             parseValue(resources, myText);
             line++;

         }
         else if(line>=5 && line <= ((5+NoProcess)-1)){
             
            parseValue(maximum, myText);
        
             line++;

             

         }
         else if(line > (((5+NoProcess)-1)+2) && line <= countline ){
            parseValue(allocation,myText);
             line++;

         }
         else{
             line++;
         }

    }
    
    MyReadFile2.close();

    SafeSequence(&NoProcess,&m,allocation,maximum,resources);




    




    

    


    

    }
    

    

    
    

    return 0;
}