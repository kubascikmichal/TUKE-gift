#include "Panel.h"

Panel::Panel()
{
    matrix = new Adafruit_NeoMatrix(8, 8, 15);
    init();
}

Panel::~Panel()
{
}

void Panel::init()
{
    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(10);
    matrix->setFont(&dotmat10pt7b_v2);
}

void Panel::run()
{
   
}