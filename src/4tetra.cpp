//
//  4tetra.cpp
//  yunapp
//
//  Created by Jörg Plutôtes on 24/03/14.
//
//

#include "4tetra.h"

ftetra::ftetra(float _a){
    
    a = _a;
    
    for (int k = 0; k < 4; k++){
    for (int j = 0; j < 12; j++){
    for (int i = 0; i < 3; i++){
        stripV[j+k*12][i] = (tetraV[stripI[j]][i]+tetraOFF[k][i])*a;
        //cout << stripV[j][i] << "\n";
    }}}
    
    for (int k = 0; k < 4; k++){
    for (int j = 0; j < 4; j++){
        points.addVertex(ofVec3f((tetraV[k][0]+tetraOFF[j][0])*a,
                                 (tetraV[k][1]+tetraOFF[j][1])*a,
                                 (tetraV[k][2]+tetraOFF[j][2])*a));
    }}
    
    points.setMode(OF_PRIMITIVE_POINTS);
    fbo.allocate(renderres, renderres);
    pfbo.allocate(renderres/4, renderres/4);
    
    fbo.begin();
        ofClear(0,0,0,255);
    fbo.end();
    
    for (int i = 0; i < 24; i++){
        stripS[i] = 0;
    }

}

void ftetra::draw(float red, float green, float blue){
    ofSetLineWidth(5);
    ofSetColor(40);
    for (int i = 0; i < 24; i++){
        if (!stripS[i])
            ofLine(stripV[2*i][0], stripV[2*i][1], stripV[2*i][2],
                   stripV[2*i+1][0], stripV[2*i+1][1], stripV[2*i+1][2]);
    }
    ofSetLineWidth(8);
    ofSetColor(red,green,blue);
    for (int i = 0; i < 24; i++){
        if (stripS[i])
            ofLine(stripV[2*i][0], stripV[2*i][1], stripV[2*i][2],
                   stripV[2*i+1][0], stripV[2*i+1][1], stripV[2*i+1][2]);
    }
    ofSetColor(255);

}

void ftetra::render(float red, float green, float blue){
    

    ofPushStyle();
    ofEnableSmoothing();
    //ofEnableDepthTest();
    glPointSize(24);
    glEnable(GL_POINT_SMOOTH);
    
    
    fbo.begin();
    
        ofClear(80, 80, 80, 255);
        ofSetupScreenOrtho(1024,1024,1024,-1024);
    
        ofPushMatrix();
            ofTranslate(renderres/2, renderres/2-220);
            ofScale(0.75, 0.75);
            ofRotateX(-90);
            draw(red, green, blue);
            ofSetColor(40);
            points.draw();
        ofPopMatrix();

        glPointSize(20);
        ofPushMatrix();
            ofTranslate(renderres/2-260, renderres/2+300);
            ofScale(0.4, 0.4);
            ofRotateX(15);
            //ofRotateY(ofGetElapsedTimef()*4);
            draw(red, green, blue);
            ofSetColor(40);
            points.draw();
        ofPopMatrix();

        ofPushMatrix();
            ofTranslate(renderres/2+260, renderres/2+300);
            ofScale(0.4, 0.4);
            ofRotateX(15);
            //ofRotateY(-ofGetElapsedTimef()*4);
            ofRotateY(180);
            draw(red, green, blue);
            ofSetColor(40);
            points.draw();
        ofPopMatrix();
    
    fbo.end();
    ofPopStyle();
}

void ftetra::gPrev(){
    
    pfbo.begin();
    
    ofClear(0, 0, 0, 255);
    ofSetupScreenOrtho(1024,1024,1024,-1024);
    
    ofPushMatrix();
    ofTranslate(renderres/2, renderres/2-220);
    ofScale(0.75, 0.75);
    ofRotateX(-90);
    draw(255, 255, 255);
    ofPopMatrix();
    
    pfbo.end();
    
}
