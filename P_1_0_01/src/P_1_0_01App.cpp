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


class P_1_0_01App : public App {
  public:
	void setup() override;
    void mouseMove( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
  
  private:
    vec2        mouseLocation;
    Color       backgroundColor;
    Rectf       square;
    Color       squareColor;
};

void prepareSettings(P_1_0_01App::Settings *settings){
    settings->setWindowSize( 720, 720 );
    //settings->setFrameRate( 60.0f );
    //settings->setFullScreen( false );
}

void P_1_0_01App::setup()
{
}

void P_1_0_01App::mouseMove( MouseEvent event )
{
        mouseLocation = vec2(event.getX(), event.getY());
}

void P_1_0_01App::keyDown( KeyEvent event ){
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

void P_1_0_01App::update()
{
    backgroundColor = Color( CM_HSV, lmap(mouseLocation.y/2.0f, 0.0f, 360.0f, 0.0f, 1.0f), 1.0f, 1.0f );
    squareColor = Color( CM_HSV, lmap(mouseLocation.y/2.0f, 0.0f, 360.0f, 1.0f, 0.0f), 1.0f, 1.0f );
    float squareSize = abs(getWindowWidth()/2.0f - mouseLocation.x)*2.0f;
    float squarePosition = getWindowWidth()/2.0f - squareSize/2.0f;
    square = Rectf(squarePosition, squarePosition, squarePosition + squareSize, squarePosition + squareSize);
}

void P_1_0_01App::draw()
{
	gl::clear( backgroundColor );
    gl::color(squareColor);
    gl::drawSolidRect(square);
}

CINDER_APP( P_1_0_01App, RendererGl, prepareSettings)
