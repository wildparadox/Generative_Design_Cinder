/**
 * changing colors and size by moving the mouse
 *
 * MOUSE
 * position x          : size
 * position y          : color
 *
 * KEYS
 * s                   : save png
 * p                   : save pdf
 */

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class P_1_1_1_01 : public App {
  public:
	void setup() override;
    void mouseMove( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
    bool mouseIsOnScreen();
    
  private:
    vec2        mouseLocation;
};

void prepareSettings(P_1_1_1_01::Settings *settings){
    settings->setWindowSize( 800, 400 );
    //settings->setFrameRate( 60.0f );
    //settings->setFullScreen( false );
}

void P_1_1_1_01::setup()
{
}

void P_1_1_1_01::mouseMove( MouseEvent event )
{
        mouseLocation = vec2(event.getX(), event.getY());
}

void P_1_1_1_01::keyDown( KeyEvent event ){
    char keyPressed = event.getChar();
    switch (keyPressed) {
        case 's':
        case 'S':
            vector<std::string> fileTypes;
            fileTypes.push_back("png");
            fs::path path = getSaveFilePath("", fileTypes);
            writeImage( path.string() , copyWindowSurface() );
            break;
    }
}

void P_1_1_1_01::update()
{

}

void P_1_1_1_01::draw()
{
    if(mouseIsOnScreen()){
        gl::clear( Color(0.f,0.f,0.f) );
        int stepX = mouseLocation.x+2;
        int stepY = mouseLocation.y+2;
        for (int gridY=0; gridY<getWindowHeight(); gridY+=stepY){
            for (int gridX=0; gridX<getWindowWidth(); gridX+=stepX){
                float hue = lmap((float)gridX, 0.f, (float)getWindowWidth(), 0.f, 1.f);
                float saturation = lmap((float)(getWindowHeight()-gridY), 0.f, (float)getWindowHeight(), 0.f, 1.f);
                gl::color(Color(CM_HSV, hue, saturation, 1.f));
                Rectf rect(gridX, gridY, gridX+stepX, gridY+stepY);
                gl::drawSolidRect(rect);
            }
        }
    }
}

bool P_1_1_1_01::mouseIsOnScreen(){
    if(mouseLocation.x > 0 && mouseLocation.x < getWindowWidth() && mouseLocation.y > 0 && mouseLocation.y < getWindowHeight()){
        return true;
    }
    return false;
}

CINDER_APP( P_1_1_1_01, RendererGl, prepareSettings)
