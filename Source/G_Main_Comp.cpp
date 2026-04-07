#include "G_Main_Comp.h"

Main_Comp::Main_Comp()
{
    setSize(600, 400);
}

void Main_Comp::paint (Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setFont (FontOptions (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void Main_Comp::resized() {
}

Main_Comp::~Main_Comp() {
}
