#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(80, 80, 80,255);
    //bool connected = tcpClient.setup("192.168.240.1", 5555);
    red = 200;
    green = 200;
    blue = 200;
    pidx = 0;
    set.col = ofColor(red,green,blue);
    presets.push_back(set);
    sprintf(cbuffer,"%d / %d", pidx+1, (int) presets.size());
    //sprintf(filename,"presets.xml");
    filename = "001.xml";
    sdir.open("presets");
    sdir.create();
    cout << "path: " << sdir.path()+"/"+filename << "\n";
    
    gui = new ofxUICanvas(0,0,318,600);
    gui->setDrawBack(false);
    gui->setFont("GUI/SourceCodePro-Bold.otf");
    //gui->setFont("GUI/Sansation-Bold.ttf");
    gui->setDrawPadding(false);
    gui->setWidgetSpacing(4);
    filetxt = gui->addTextInput("filename", filename,310-104,50,4,4,OFX_UI_FONT_MEDIUM);
    PXLmatrix = gui->addToggleMatrix("PXLMATRIX", 4, 6,50,50);
    gui->setGlobalSliderHeight(50);
    rslide = gui->addBiLabelSlider("RED", " R", "200 ", 0.0, 255.0, &red);
    gslide = gui->addBiLabelSlider("GREEN", " G", "200 ", 0.0, 255.0, &green);
    bslide = gui->addBiLabelSlider("BLUE", " B", "200 ", 0.0, 255.0, &blue);
    gui->addWidget(new ofxUILabelButton("<<", false, 50, 50, 4, 494, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton(">>", false, 50, 50, 56, 494, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("+", false, 50, 50, 212, 494, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("-", false, 50, 50, 264, 494, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("c", false, 50, 50, 212, 546, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("a", false, 50, 50, 264, 546, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("pid", false, 50, 50, 108, 494, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("pmx", false, 50, 50, 160, 494, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelToggle("send", false,102,50,4,546,OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelToggle("connect", false,102,50,108,546,OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("s", false, 50, 50, 212, 4, OFX_UI_FONT_MEDIUM));
    gui->addWidget(new ofxUILabelButton("l", false, 50, 50, 264, 4, OFX_UI_FONT_MEDIUM));
        
    filetxt->setAutoClear(false);
    filetxt->setTriggerType(OFX_UI_TEXTINPUT_ON_ENTER);
    
    pid = (ofxUILabelButton *) gui->getWidget("pid");
    pmx = (ofxUILabelButton *) gui->getWidget("pmx");
    pid->setLabelText(ofToString(pidx+1));
    pmx->setLabelText(ofToString(presets.size()));
    
    rslide->setColorBack(ofColor(0,0,0,100));
    rslide->setColorFill(ofColor(255,0,0,50));
    rslide->setColorFillHighlight(ofColor(255,0,0,200));
    gslide->setColorBack(ofColor(0,0,0,100));
    gslide->setColorFill(ofColor(0,255,0,50));
    gslide->setColorFillHighlight(ofColor(0,255,0,200));
    bslide->setColorBack(ofColor(0,0,0,100));
    bslide->setColorFill(ofColor(0,0,255,50));
    bslide->setColorFillHighlight(ofColor(0,0,255,200));
    
    rlabel = rslide->getRightLabel();
    glabel = gslide->getRightLabel();
    blabel = bslide->getRightLabel();
    
    toggles = PXLmatrix->getToggles();
    for (int i = 0; i < toggles.size(); i++){
        toggles[i]->setColorFill(ofColor(255,200));
        toggles[i]->setColorBack(ofColor(0,100));
        //toggles[i]->setLabelText(ofToString(i));
        //toggles[i]->setLabelVisible(true);
    }
    
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    
    pyra = new ftetra(2);
    pyra->render(red,green,blue);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    /*
    int nled = 0;
    
    if(tcpClient.isConnected()) {
        string str = tcpClient.receive(); // did anything come in
    }
    
    red = ofRandom(55);
    green = ofRandom(55);
    blue = ofRandom(55);
    char cmd[18];
    sprintf(cmd, "LED/%d/%d/%d/%d",nled,red,green,blue);
    tcpClient.send(cmd);
    
    if (red>255) red = 0;
     */
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofSetBackgroundColor(40, 43, 53);
    pyra->fbo.draw(918-600, 0, 600, 600);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_RETURN && filetxt->isFocused()){
        filename = filetxt->getTextString();
        sdir.listDir();
        files.clear();
        files = sdir.getFiles();
        for(int i = 0; i<files.size(); i++){
            int sc = strcmp(files[i].getFileName().c_str(), filename.c_str());
            //cout << files[i].getFileName() << "  " << sc << "\n";
            if(sc == 0) loadPrst();
            else {
                presets.clear();
                set.val.assign(24, false);
                presets.push_back(set);
                updatePrst(0);
            }
        }
    }


}

//--------------------------------------------------------------
void ofApp::updatePrst(int i){
    for (int k = 0; k < 24; k++){
        pyra->stripS[k] = presets[i].val[k];
        toggles[k]->setValue(presets[i].val[k]);
        red = presets[i].col.r;
        green = presets[i].col.g;
        blue = presets[i].col.b;
        
    }
}
//--------------------------------------------------------------
void ofApp::savePrst(){
    presetsXML.clear();
    presetsXML.addTag("Presets");
    presetsXML.pushTag("Presets");
    for (int i = 0; i < presets.size(); i++) {
        presetsXML.addTag("preset");
        presetsXML.pushTag("preset", i);
        presetsXML.addValue("set", presets[i].getstr());
        presetsXML.addValue("r", presets[i].col.r);
        presetsXML.addValue("g", presets[i].col.g);
        presetsXML.addValue("b", presets[i].col.b);
        presetsXML.popTag();
    }
    presetsXML.popTag();
    presetsXML.saveFile(sdir.path()+"/"+filename);
}
void ofApp::loadPrst(){
    if(presetsXML.loadFile(sdir.path()+"/"+filename)){
        presets.clear();
        presetsXML.pushTag("Presets");
        int np = presetsXML.getNumTags("preset");
        for (int i = 0; i < np; i++) {
            presetsXML.pushTag("preset", i);
            string sp  = presetsXML.getValue("set", "000000000000000000000000");
            set.set(sp);
            int r = presetsXML.getValue("r",0);
            int g = presetsXML.getValue("g",0);
            int b = presetsXML.getValue("b",0);
            set.col = ofColor(r,g,b);
            cout << i << " " << r << "\n";
            presets.push_back(set);
            presetsXML.popTag();
    }
    presetsXML.popTag();
    pidx = 0;
    updatePrst(0);
    
    }
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    for (int i = 0; i < toggles.size(); i++){
        bool val = toggles[i]->getValue();
        pyra->stripS[i] = val;
        set.set(i,val);
    }
    set.col = ofColor(red,green,blue);
    presets[pidx] = set;
    
	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		red = slider->getScaledValue();
        char val[10];
        sprintf(val,"%d",(int)red);
        rlabel->setLabel(val);
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		green = slider->getScaledValue();
        char val[10];
        sprintf(val,"%d",(int)green);
        glabel->setLabel(val);
	}
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		blue = slider->getScaledValue();
        char val[10];
        sprintf(val,"%d",(int)blue);
        blabel->setLabel(val);
	}
    else if(name == "+"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            set.val.assign(24, false);
            presets.insert(presets.begin()+pidx+1, set);
            pidx++;
            updatePrst(pidx);
        }
    }
    else if(name == "c"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            set.val.assign(24, false);
            presets[pidx] = set;
            updatePrst(pidx);
        }
    }

    else if(name == "a"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            set.val.assign(24, true);
            presets[pidx] = set;
            updatePrst(pidx);
        }
    }
    
    else if(name == "-"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            if(presets.size()>1){
            presets.erase(presets.begin()+pidx);
            pidx--;
            if (pidx < 0) pidx = presets.size()-1;
            }
            updatePrst(pidx);
        }
    }
    else if(name == "<<"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            pidx--;
            if (pidx < 0) pidx = presets.size()-1;
            updatePrst(pidx);
        }
    }
    else if(name == ">>"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            pidx++;
            if (pidx > presets.size()-1) pidx = 0;
            updatePrst(pidx);
        }
    }
    else if(name == "s"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            savePrst();
        }
    }
    else if(name == "l"){
        ofxUIButton *btn = (ofxUIButton *) e.widget;
        if(btn->getValue()){
            loadPrst();
        }
        pidx = 0;
        updatePrst(pidx);
    }
    set.col = ofColor(red,green,blue);
    pyra->render(red,green,blue);
    pid->setLabelText(ofToString(pidx+1));
    pmx->setLabelText(ofToString(presets.size()));
    //pyra->fbo.draw(918-600, 0, 600, 600);
}