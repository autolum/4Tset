//
//  preset.h
//  yunapp
//
//  Created by Jörg Plutôtes on 03/04/14.
//
//

#ifndef __4Tset__preset__
#define __4Tset__preset__

#include "ofMain.h"

class preset {
    public:
        vector<bool> val;
        ofColor col;
        preset();
        void print();
        void set(int i, bool v);
        void set(string vals);
        string getstr();
        string getBytes();
        string getInts();
};


#endif /* defined(__yunapp__preset__) */
