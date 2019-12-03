#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>

#include <stdlib.h>
#include <time.h>

using namespace std;

bool buildMap();
void writeIndex();
void AddWordtoMap(string);
void writeSorted();
void Filter();
bool isLetter(string);
map <string, int> jobMap;
map <string, int> filterMap;
typedef pair<string, int> myPair;
vector<myPair> myVec;

int main(int argc, char** argv) {
if (buildMap()){
 cout<<"The map has "<< jobMap.size() << " elements" << endl;
 writeIndex();
 cout << endl << endl;
 
 system("pause");
 
 cout << "Sorted" << endl;
 writeSorted();
 cout << endl << endl;
 
 system("pause");
 
 cout << "Filter" << endl;
 Filter();
 
 jobMap.clear();
 cout<<"The map has "<< jobMap.size() << " elements" << endl;
}

return 0;
}

bool buildMap(){
string filename;

cout << "Enter file name (which is 'jobs') : " << endl;
cin >> filename;
filename += ".csv";

ifstream inputFile(filename.c_str());
string line;

if(inputFile.is_open()){
 cout << "File opened Successfully" << endl << endl;

 while(getline(inputFile, line)){
  size_t prev = 0, pos;
  
  while((pos =  line.find_first_of
   ("~`=!@$%^&*)/\?-_|[,. }] (_{;':""></", prev)) != string::npos){
   if(pos>prev){
    AddWordtoMap(line.substr(prev, pos-prev));
   }
   
   prev = pos + 1;
  }

  if(prev < line.length()){
   AddWordtoMap(line.substr(prev, std::string::npos));
  }
 }
 
 inputFile.close();
}
else{
 cout << "Unable to open file-" << endl;

 return false;
}

return true;
}


void writeIndex(){
for(map<string, int> ::iterator itr = jobMap.begin(); 
     itr != jobMap.end(); ++itr){
 std::cout<<"\n  "<< setw(30) <<itr->first<< setw(10)<<itr->second;
}
}

void writeSorted(){
copy(jobMap.begin(),
  jobMap.end(),
  std::back_inserter<std::vector<myPair> >(myVec));
  
sort(myVec.begin(), myVec.end(),
  [](const myPair& l, const myPair& r) {
   if (l.second != r.second)
    return l.second > r.second;

   return l.first > r.first;
  });
  
/*for (auto const &myPair: myVec) {
 std::cout<<"\n  "<< setw(30) << myPair.first << setw(10)<< myPair.second;
}*/
}

string specialWords[2]= {"C++", "C#"};

void AddWordtoMap(string str){
if(isLetter(str)){
map<string, int> ::iterator it = jobMap.find(str);
if(it != jobMap.end()){
it->second = it->second + 1;
}
else{
jobMap.insert(std::make_pair(str, 1));
}
}
}

bool isLetter(string word){
int i = 0;
for(i= 0; i < 2; i++){
if(word == specialWords[i]){
goto stop;
}
}
for(i = 0; i < word.size(); i++){
int uppercaseChar = tolower(word[i]);
if (uppercaseChar < 'a' || uppercaseChar > 'z'){
return false;
}
}
stop: return true;
}

void Filter(){
srand(time(NULL));

int ans = 0;

std::string filename = "Job.csv";
fstream outputFile(filename, ios::out);

outputFile << "Words" << ";" << "Repetitions" << endl;

for (auto const &myPair: myVec){  
filterword:cout << "The word '" << myPair.first << "' appears " << myPair.second << " times repeated in the text." << endl;
 cout << "Do you want to keep it in the search?" << endl;
 cout << "1. Yes " << setw(10) << "2. No" << endl;
 //cin >> ans;
 ans = 1 + rand()%(3-1);
 cout << ans;
 
 if(ans == 1){
  filterMap.insert(std::make_pair(myPair.first, myPair.second));
  
  outputFile << myPair.first << ";" << myPair.second << endl;
 }
 /*else if(ans == 3){
  for(map<string, int> ::iterator itr = filterMap.begin(); 
      itr!=filterMap.end(); ++itr){
   std::cout<<"\n  "<< setw(30) <<itr->first<< setw(10)<<itr->second;
  }
  cout << endl;
  goto filterword;
 }
 else if(ans == 4){
  break;
 }*/
 else if(ans != 2){  
  goto filterword;
 }
 
 cout << endl;
}
}


