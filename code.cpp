#include<iostream>
#include<string>
#include<fstream>
#include<dirent.h>
#include<sys/types.h>
#include<vector>
#include<set>

using namespace std;
string path ; // global variable for path of the directory
//defining a class book
class book{
   public:
     string title , author ,release_date,language, filename;
 };


//asking user to input type of each book
void make_index_txt_file(){
   fstream fio1,fio2;
   fio1.open("index1.txt",ios::in);
   fio2.open("index.txt",ios::out);
   string line;
   while(getline(fio1,line)){
      if(line.at(0)=='.')
      {continue;}
      
      //cout<<line<<endl;
      fio2<<line<<endl;
      cout<<"Enter the type of: "<<endl;
         cout<<line;
         string type;
         cin>>type;
         fio2<<"  "<<type<<endl;
   }
   fio1.close();
   fio2.close();
   return;
}

//function to open a directory and write filenames in a file.
void explore(char* dir_name){
   fstream fio;
    string line;
    fio.open("index1.txt",ios::out);
    
    
   DIR *dr;      
   struct dirent *entry;           //stuff in the directory
   dr = opendir(dir_name);
   if(dr){
      
      while(fio){
      while((entry = readdir(dr))!= NULL){
            fio<< entry->d_name <<" - "<<endl;
      }
      if((entry=readdir(dr))==NULL)
      break;
      }
      closedir(dr);
   }
   fio.close();


}


//making a list of books with their file name , title , author , date,language
void booklist( vector<book> &list_all_book){

fstream fobj;ifstream fileobj;
   
   fobj.open("index.txt",ios::in|ios::out);
   
   string word,word2,line;
   book b1;      // book object
   while(fobj>>word){
      if(word.find(".txt")!=string::npos){
         
         b1.filename = word;           //assigning filename in book object
         string path = "/Users/prativa/Desktop/code/"+word;
         fileobj.open(path);
      
         while(fileobj>>word2){
            
            if(word2=="Title:")
            {
               getline(fileobj,line);
            b1.title = line;      //assigining title in book object
            }

            if(word2=="Author:")
            {getline(fileobj,line);
            b1.author=line;      //assigining author in book object
            
            }

            if(word2 == "Date:"){
               getline(fileobj,line);
               b1.release_date=line;   //assigining release date in book object
               
            }
            if(word2=="Language:"){
               getline(fileobj,line);
               b1.language=line;       //assigining language in book object
               
               break;
            }
            
            
         }
         list_all_book.push_back(b1);     //adding book object in a vector 
         fileobj.close();
      }

   }
return;
}


//function to print the filename , title and author
void print_list_all_books(vector<book> list_all_books){
int n = list_all_books.size();
for(int i=0;i<n;i++){
   cout<<"File name - "<<list_all_books[i].filename<<endl;
   cout<<"Title - "<<list_all_books[i].title<<endl;
   cout<<"Author - "<<list_all_books[i].author<<"\n"<<endl;
}
return ;
}


//search for a book by its title or author name
void search_book(string name,vector<book> list_all_books){
   int i,n = list_all_books.size();
   cout<<"Matching Book list is:-"<<endl;
   for( i=0;i<n;i++){
      string str1,str2;
      str1 = list_all_books[i].title;
      str2 = list_all_books[i].author;
      transform(str1.begin(),str1.end(),str1.begin(),::tolower);
      transform(str2.begin(),str2.end(),str2.begin(),::tolower); 
      transform(name.begin(),name.end(),name.begin(),::tolower);

      if(str1.find(name)!=string::npos||str2.find(name)!=string::npos){
         
         cout<<"File name - "<<list_all_books[i].filename<<endl;
         cout<<"Title - "<<list_all_books[i].title<<endl;
         cout<<"Author - "<<list_all_books[i].author<<"\n"<<endl;   
      }
   }
   if(i == n-1)
   cout<<"book not found";
}


//display a book (100 lines of the book are diplayed )
void Display_Book(string filename){
  string path = "/Users/girishkumar/Desktop/c_program/SE_assigment/books/"+filename; 
   fstream fo;
   string line;
   fo.open(path);
   int count =0;
   //cout<<"True"<<endl;
   while(fo){
      if(count==100)       //100 lines of book
      break;
      getline(fo,line);
      cout<<line<<endl;
      count++;
   }
}

//function  of top 5 chapters containing a particular word in novel
void recurrent_word_in_novel(string filename){
   cout<<"Enter the word to be searched for: ";
   string word,line;
   cin>>word;
   fstream fi;
   set<pair <int,string> > s;
   string path = "/Users/girishkumar/Desktop/c_program/SE_assigment/books/"+filename;
   fi.open(path);
   if(fi)
   cout<<"true"<<endl;
   int count=0,pos =0;
   string chapterold,chapter;
   while(fi){
      getline(fi,line);
      
      if(line.find("BOOK")!=string ::npos)
      continue;
      if(line.find("CHAPTER")!=string::npos)
      {   chapter = line;
         //cout<<line<<endl;
         if(count ==0)
         {
         continue;}
         pair<int,string> x = make_pair(count,chapterold);
         //cout<<count<<" "<<chapterold<<endl;
         s.insert(x);
         count=0;
      }
       chapterold = chapter;
      if(line.find(word)!=string::npos)
      count++;
     }
      
   int j=1;
   set<pair <int,string> > ::reverse_iterator rit;
   for(rit = s.rbegin(); rit != s.rend();rit++){
      cout<<rit->first<<" "<<rit->second<<endl;
      j++; 
      if(j>5)
      break;
   }
   // return;

}



int main(){
    

    cout<<"enter the full path of directory : ";
    string str,name,filename;
    cin>>path;
    int i,k,n = path.length();
    char dir[n];
    strcpy(dir,path.c_str());
    explore(dir);
    make_index_txt_file();
      
   vector<book> list_all_book;
   
   booklist(list_all_book);
   cout<<"\nType corresponding numbers for the functionalities:"<<endl;
   cout<<"\n1. List all the books along with their file name."<<endl;
   cout<<"2. search for a book by its title or author name ."<<endl;
   cout<<"3. Diplay a book from any of the above two list."<<endl;
   cout<<"4. Enter the type of book : Novel or Play . and search a word in it."<<endl;
   cout<<"-1 to exit the program."<<endl;
   int num;
   while(num!=-1){
   cin>>num;
    switch (num)
    {
       case 1: 
            cout<<"List of all books is:"<<endl;
            print_list_all_books(list_all_book);
           break;
       case 2:
            cout<<"enter any title or author name :-";
            cin>>str;
            search_book(str,list_all_book);
           break;
      case 3:
            cout<<"Enter a file name of book from above list:-";
            cin>>filename;
            Display_Book(filename);
           break;
      case 4:
            
            k = list_all_book.size();
            for( i =0;i<k;i++){
               //if(list_all_book[i].filename.find(name))
               cout<<list_all_book[i].filename<<endl;
            }
            cout<<"\nEnter the name of the book from above list: "  ;
            cin>>name;
            
            recurrent_word_in_novel(name);
           break;
      case -1:
           return 0;
    }
   }
    
return 0;
}
