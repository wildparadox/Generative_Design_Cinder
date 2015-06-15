/**
 * changing colors and size by moving the mouse
 *
 * MOUSE
 * position x          : size
 * position y          : color
 *
 * KEYS
 * s                   : save png
 * space               : randomize colors
 */

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"
#include "cinder/Rand.h"
using namespace ci;
using namespace ci::app;
using namespace std;


class P_1_2_1_01 : public App {
  public:
	void setup() override;
    void mouseMove( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
    void randomizeColors();
    
  private:
    vec2        mouseLocation;
    Rand numberGenerator;
    int tileCountX = 2;
    int tileCountY = 10;
    
    vector<Color> colorsLeft;
    vector<Color> colorsRight;
    vector<Color> colors;
    bool interpolateShortest = false;
};

void prepareSettings(P_1_2_1_01::Settings *settings){
    settings->setWindowSize( 800, 800 );
    //settings->setFrameRate( 60.0f );
    //settings->setFullScreen( false );
}

void P_1_2_1_01::setup()
{
    randomizeColors();
}

void P_1_2_1_01::mouseMove( MouseEvent event )
{
        mouseLocation = vec2(event.getX(), event.getY());
}

void P_1_2_1_01::keyDown( KeyEvent event ){
    char keyPressed = event.getChar();
    switch (keyPressed) {
        case '1':
            interpolateShortest = false;
            break;
        case '2':
            interpolateShortest = true;
            break;
        case ' ':
            randomizeColors();
            break;
        case 's':
        case 'S':
            vector<std::string> fileTypes;
            fileTypes.push_back("png");
            fs::path path = getSaveFilePath("", fileTypes);
            writeImage( path.string() , copyWindowSurface() );
            break;
    }
}

void P_1_2_1_01::update()
{
    
}

void P_1_2_1_01::draw()
{
    gl::clear();
    tileCountX = (int)lmap((float)mouseLocation.x, 0.f, (float)getWindowWidth(), 2.f, 100.f);
    tileCountY = (int)lmap((float)mouseLocation.y, 0.f, (float)getWindowHeight(), 2.f, 10.f);
    float tileWidth = (float)getWindowWidth() / (float)tileCountX;
    float tileHeight = (float)getWindowHeight() / (float)tileCountY;
    Color interCol = Color::white();
    
    colors.clear();
    
    for(int gridY = 0; gridY < tileCountY; gridY++){
        Color col1 = colorsLeft[gridY];
        Color col2 = colorsRight[gridY];
        
        for(int gridX = 0; gridX < tileCountX; gridX++){
            float amount = lmap((float)gridX, 0.f, (float)tileCountX-1.f, 0.f, 1.f);
            
            if(interpolateShortest){
                vec3 col1hsv = rgbToHsv(col1);
                vec3 col2hsv = rgbToHsv(col2);
                vec3 newColor = lerp(col1hsv, col2hsv, amount);
                interCol = Color(CM_HSV, newColor.x, newColor.y, newColor.z);
            }
            else{
                interCol = lerp(col1, col2, amount);
            }
            
            gl::color(interCol);
            
            float posX = tileWidth*gridX;
            float posY = tileHeight*gridY;

            gl::drawSolidRect(Rectf(posX, posY, posX + tileWidth, posY + tileHeight));
        }
        
        // just for Ease export, not used in this example
        colors.push_back(interCol);
    }
}

void P_1_2_1_01::randomizeColors(){
    colorsLeft.clear();
    colorsRight.clear();
    
    for (int i=0; i<tileCountY; i++) {
        colorsLeft.push_back(Color(CM_HSV, numberGenerator.nextFloat(0.167f), numberGenerator.nextFloat(1.0f), 1.0f));
        colorsRight.push_back(Color(CM_HSV, numberGenerator.nextFloat(0.44f, 0.528f), 1.0f, numberGenerator.nextFloat(1.0f)));;
    }
}

CINDER_APP( P_1_2_1_01, RendererGl, prepareSettings)
