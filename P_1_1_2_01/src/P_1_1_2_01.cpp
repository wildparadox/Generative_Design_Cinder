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


class P_1_1_2_01 : public App {
  public:
	void setup() override;
    void mouseMove( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
  
  private:
    vec2        mouseLocation;
    float segmentCount = 360.f;
    float radius = 300.f;
};

void prepareSettings(P_1_1_2_01::Settings *settings){
    settings->setWindowSize( 800, 800 );
    //settings->setFrameRate( 60.0f );
    //settings->setFullScreen( false );
}

void P_1_1_2_01::setup()
{
}

void P_1_1_2_01::mouseMove( MouseEvent event )
{
        mouseLocation = vec2(event.getX(), event.getY());
}

void P_1_1_2_01::keyDown( KeyEvent event ){
    char keyPressed = event.getChar();
    switch (keyPressed) {
        case '1':{
            segmentCount = 360.f;
            break;
        }
        case '2':{
            segmentCount = 36.f;
        }
            break;
        case '3':{
            segmentCount = 18.f;
        }
            break;
        case '4':{
            segmentCount = 12.f;
        }
            break;
        case '5':{
            segmentCount = 6.f;
        }
            break;
        case 's':
        case 'S':{
            vector<std::string> fileTypes;
            fileTypes.push_back("png");
            fs::path path = getSaveFilePath("", fileTypes);
            writeImage( path.string() , copyWindowSurface() );
            break;
        }
    }
}

void P_1_1_2_01::update()
{
}

void P_1_1_2_01::draw()
{
    gl::clear( Color::black() );

    float angleStep = 360.f/segmentCount;
    gl::disableWireframe();
    gl::begin(GL_TRIANGLE_FAN);
        gl::vertex(getWindowWidth()/2, getWindowHeight()/2);
        for (float angle=0.f; angle<=360.f; angle+=angleStep){

            float vx = getWindowWidth()/2 + cos(toRadians(angle))*radius;
            float vy = getWindowHeight()/2 + sin(toRadians(angle))*radius;

            gl::vertex(vx, vy);
            float h = lmap(angle, 0.f, 360.f, 0.f, 1.f);
            float s = lmap(mouseLocation.x, 0.f, (float)getWindowWidth(), 0.f, 1.f);
            float v = lmap(mouseLocation.y, 0.f, (float)getWindowHeight(), 0.f, 1.f);
            gl::color(Color(CM_HSV, h, s, v));

        }
    gl::end();
}

CINDER_APP( P_1_1_2_01, RendererGl, prepareSettings)
