
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector> 
#include "db.h"
using namespace std;


int main(int argc, char **argv)
{
   string user;
   string credential;
   string host;
   string port;
   string database;
   
  for(int i=1;i<=10;i++){
        if(strcmp(argv[i], "-u")
        user=argv[i+1];
        else if(strcmp(argv[i], "-c")
        user=argv[i+1];
        else if(strcmp(argv[i], "-h")
        user=argv[i+1];
        else if(strcmp(argv[i], "-p")
        user=argv[i+1];
        else if(strcmp(argv[i], "-d")
        user=argv[i+1];
       
   }
    
db_login(host,port,database,user,credential);
    
    db_begin();
 
   char buffer[100];
   for(int i=11;i<argc;i++){
       
   file=fopen(argv[i],"r");
   char buffer[100];
   std::vector<char*>line;
   while(fgets(buffer,100,file)) { 
       
      
     char* token = strtok(buffer, " "); 
      
    
        //printf("%s\n", token);
        if(strcmp(token, "n\n")==0){
            cout<<"n"<<endl;
           while(token){
            user=token; 
            token = strtok(NULL, " ");  
           }
            int n=db_create_table_hersteller();
            int m=db_create_table_produkt();
        }
        else if(strcmp(token, "ih")==0){
            std::vector<char*>line;
            cout<<"ih"<<endl;
             while(token){
            //cout<<token<<endl; 
            if(strcmp(token, "ih")!=0)
            line.push_back(token);
            token = strtok(NULL, " ");  
           }
             int n=db_check_hnr(line[0]);
             if (n==1)
             n=db_update_hersteller(line[0],line[1],line[2]);
             else if(n==0)
             n=db_insert_hersteller(line[0],line[1],line[2]);
             else n=db_rollback();
            
        
            
        }
        else if(strcmp(token, "ip")==0){
            std::vector<char*>line;
          
            cout<<"ip"<<endl;
             while(token){
           // cout<<token<<endl;
           if(strcmp(token, "ih")!=0)
            line.push_back(token);
            token = strtok(NULL, " ");  
           }
            int n=db_check_pnr(line[0]);
            if (n==1)
            n=db_update_produkt(line[0],line[1],line[2],line[3]);
            else if(n==0)
            n=db_insert_produkt(line[0],line[1],line[2],line[3]);
            else n=db_rollback();
            
        }
        
        
        else if(strcmp(token, "i")==0){
            std::vector<char*>line;
          
            cout<<"i"<<endl;
             while(token){
           // cout<<token<<endl;
           if(strcmp(token, "i")!=0)
            line.push_back(token);
            token = strtok(NULL, " ");  
           }
             int n=db_check_hnr(line[0]);
             if (n==1)
             n=db_update_hersteller(line[0],line[1],line[2]);
             else if(n==0)
             n=db_insert_hersteller(line[0],line[1],line[2]);
             else n=db_rollback();
             
             int n=db_check_pnr(line[0]);
             if (n==1)
             n=db_update_produkt(line[3],line[4],line[5],line[0]);
             else if(n==0)
             n=db_insert_produkt(line[3],line[4],line[5],line[0]);
             else n=db_rollback();
            
           
            
        }
        
        else if(strcmp(token, "dh")==0){
            std::vector<char*>line;
          
            cout<<"dh"<<endl;
             while(token){
           // cout<<token<<endl;
           if(strcmp(token, "dh")!=0)
            line.push_back(token);
            token = strtok(NULL, " ");  
           }
             
             
             int n=db_check_pnr(line[0]);
             if (n==1)
             n=db_delete_produkt(line[0]);
             n=db_delete_hersteller(line[0]);
            
           
            
        }
        
        
        else if(strcmp(token, "dp")==0){
            std::vector<char*>line;
          
            cout<<"dp"<<endl;
             while(token){
           // cout<<token<<endl;
           if(strcmp(token, "dp")!=0)
            line.push_back(token);
            token = strtok(NULL, " ");  
           }
             
             int n=db_delete_hersteller(line[0]);
            
           
            
        }
        
        
         else if(strcmp(token, "ch")==0){
            std::vector<char*>line;
          
            cout<<"ch"<<endl;
             while(token){
           // cout<<token<<endl;
           if(strcmp(token, "ch")!=0)
            line.push_back(token);
            token = strtok(NULL, " ");  
           }
             string tabelle="hersteller";
             int n=db_count(tabelle);
            
            
            
        }
        
        else if(strcmp(token, "cp")==0){
            std::vector<char*>line;
          
            cout<<"cp"<<endl;
             while(token){
           // cout<<token<<endl;
           if(strcmp(token, "cp")!=0)
            line.push_back(token);
            token = strtok(NULL, " ");  
           }
             string tabelle="produkt";
             int n=db_count(tabelle);
            
           
            
        }
        
       
       
     
   
   }
 }
db_delete(); 
db_commit();


    return 0;
}
