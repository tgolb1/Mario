#include "FileProcessor.h"

FileProcessor::FileProcessor(){
}

FileProcessor::~FileProcessor(){

}

void FileProcessor::readFile(string file){
    string line;
    int i = 0;
    ifstream inFile(file);

    while(getline(inFile, line)) {
        fLine[++i] = stoi(line);
    }
}