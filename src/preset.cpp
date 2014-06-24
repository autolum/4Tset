//
//  preset.cpp
//  yunapp
//
//  Created by Jörg Plutôtes on 03/04/14.
//
//

#include "preset.h"

preset::preset(){
    val.resize(24);
    for (int i = 0; i < 24; i++){
        val[i] = 0;
        col = ofColor(0);
    }
};

void preset::print(){
    for (int i = 0; i < 24; i++) cout << val[i];
};

void preset::set(int i, bool v){
    val[i] = v;
};

void preset::set(string vals){
    for(int i = 0; i < 24; i++){
        if (vals[i] == '1'){
            val[i] = true;
        }
        else val[i] = false;
    }
    
}

string preset::getstr(){
    string str;
    for (int i = 0; i < 24; i++) str += ofToString(val[i]);
    return str;
};
