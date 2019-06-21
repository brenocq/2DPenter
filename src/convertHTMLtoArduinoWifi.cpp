#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void openFile(ifstream &file, string fileName);

int main(int argc, char const *argv[]) {
  ifstream htmlFile;
  ifstream outputFile;
  string htmlName;
  string outputName;
  int aux;
  char htmlAux;

  //---------- Receive .html file name ----------//
  cout<<"Enter the name of the .html file: ";
  cin>>htmlName;
  aux = htmlName.find(".html");
  // Add .html at the end if necessary
  if(aux==std::string::npos)
    htmlName += ".html";

  openFile(htmlFile, htmlName);

  //---------- Receive .txt file name ----------//
  cout<<"Enter the name of the output .txt file: ";
  cin>>outputName;
  aux = outputName.find(".txt");
  // Add .txt at the end if necessary
  if(aux==std::string::npos)
    outputName += ".txt";

  openFile(outputFile, outputName);
  ofstream out(outputName.c_str());
  //------------- Process html file ------------//
  char c;
  out<<"client.println(\"";

  htmlFile.get(c);
  while(!htmlFile.eof()){
    if(c=='\r'){
      htmlFile.get(c);
      continue;
    }else if(c=='\n' && !htmlFile.eof()){
      htmlFile.get(c);
      if(htmlFile.eof()){
        out<<"\");\n";
      }else{
        out<<"\");\nclient.println(\"";
      }
      continue;
    }else if(c=='\t'){
      htmlFile.get(c);
      continue;
    }else if(c=='\"'||c=='\''){
      out<<'\\';
    }else if(c=='%'){
      out<<'%';
    }

    out<<c;
    htmlFile.get(c);
  }
  out<<"client.println();\n";


  htmlFile.close();
  outputFile.close();
  return 0;
}

void openFile(ifstream &file, string fileName){
  // Check if the file exists
  file.open(fileName.c_str());
  if(file.fail()){
    cerr<<"Failed to open the file "<<fileName<<"... Please close the program"<<endl;
  }else{
    cout<<fileName<<" open successfully!"<<endl;
  }
}
