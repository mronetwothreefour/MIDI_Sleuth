#include "G_020_Main_Component.h"

Main_Component::Main_Component()
{
    setSize(600, 400);
}

void Main_Component::paint(Graphics& g) {
    g.setFont (FontOptions (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void Main_Component::resized() {
}

Main_Component::~Main_Component() {
}
