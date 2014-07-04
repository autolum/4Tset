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

string preset::getBytes(){
    string str;
    str += "LED/";
    unsigned char null = 1;
    for (int i = 0; i < 24; i++){
        if(val[i]){
            str += col.r & 0xff;
            str += col.g & 0xff;
            str += col.b & 0xff;
        }
        else {
            str += null;
            str += null;
            str += null;
        }
        
    }
    return str;
};

string preset::getInts(){
    string str;
    str += "LED/";
    for (int i = 0; i < 24; i++){
        if(val[i]) str += ofToString(col.getHex());
        else str += "0";
        str += "/";
    }
    return str;
};


