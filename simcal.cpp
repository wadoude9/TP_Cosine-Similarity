#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

map<string, int> readFile(string path) {

    ifstream file;
    file.open(path);
    string line;
    
    map<string, int> filemap;

    while (getline(file, line)){
        int index = 0;
        string word = "";
        for (int i=0; i<line.length(); i++){
            string alpha = "";
            alpha += tolower(line[i]);
            if ((alpha != " ") & (int(line[i]) != 13) & (alpha.length() > 0)){
                word += alpha;
            } else{  // end word
                if (int(word[0]) != 0){  // word found
                    if (filemap
            .count(word) == 1){  // increment word count
                        filemap
                [word] ++;
                    }else{ // add new word 
                        filemap
                [word] = 1; 
                    }
                    word = "";
                    index = i+1;
                }
            }
        }
        // last word in the file
        if ((int(word[0]) != 13) & (int(word[0]) != 0)){ 
            if (filemap
    .count(word) == 1){
                filemap
        [word] ++;
            }else{
                filemap
        [word] = 1;
            }
        }
    }
    file.close();
    return filemap;
}

int main(int argc, char *argv[]) {
    map<string, int> file1, file2;
    file1 = readFile(argv[1]);
    file2 = readFile(argv[2]);
    vector<string> keys;
    for (auto it = file1.begin(); it != file1.end(); ++it) {
        if (find(keys.begin(), keys.end(), it->first) == keys.end()){
            // add unique words only
            keys.push_back(it->first);
        }
    }
    for (auto it = file2.begin(); it != file2.end(); ++it) {
        if (find(keys.begin(), keys.end(), it->first) == keys.end()){
             // add unique words only
            keys.push_back(it->first);
        }
    }
    int product, distanceA, distanceB = 0;
    int instancesA, instancesB = 0;
    for (int i=0; i<keys.size(); i++){
        if (file1.count(keys[i]) == 1){
            instancesA = file1[keys[i]];}else instancesA = 0;
        if (file2.count(keys[i]) == 1){
            instancesB = file2[keys[i]];}else instancesB = 0;
        product += instancesA*instancesB;
        distanceA += pow(instancesA, 2);
        distanceB += pow(instancesB, 2);
    }
    float similarity = (product / (sqrt(distanceA) * sqrt(distanceB))) * 100;
    cout << similarity << "%\n";
    return 0;
}
