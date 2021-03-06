#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "4tetra.h"
#include "preset.h"
#include "ofxNetwork.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void updatePrst(int i);
		
    
		void keyPressed(int key);
		//void keyReleased(int key);
		//void mouseMoved(int x, int y);
		//void mouseDragged(int x, int y, int button);
		//void mousePressed(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		//void windowResized(int w, int h);
		//void dragEvent(ofDragInfo dragInfo);
		//void gotMessage(ofMessage msg);
         
        ofxTCPClient tcpClient;
        bool tcpCon;
        bool msgsend;
    
        ofxUILabelButton * sndB;
        ofxUITextInput *filetxt;
        ofxUILabelButton *pid;
        ofxUILabelButton *pmx;
        ofxUILabelButton *nextB;
        ofxUILabelButton *prevB;
        ofxUIBiLabelSlider *rslide;
        ofxUIBiLabelSlider *gslide;
        ofxUIBiLabelSlider *bslide;
        ofxUILabel *rlabel;
        ofxUILabel *glabel;
        ofxUILabel *blabel;
        ofxUILabel *pLabel;
        ofxUILabel *pmax;
        ofxUIToggleMatrix  *PXLmatrix;
        vector<ofxUIToggle *> toggles;
        ofxUIDropDownList *ddl;
        ofxUICanvas *gui;
        void guiEvent(ofxUIEventArgs &e);
    
        ftetra *pyra;
    
        char stripset[24];
        preset set;
    
        float red, green, blue;
        float rot;
    
        ofxXmlSettings presetsXML;
        vector<preset> presets;
    
        void savePrst();
        void loadPrst();
        void sendPrst();
    
        int pidx;
        char cbuffer[50];
        string filename;
        ofDirectory sdir;
        vector<ofFile> files;
    
};
