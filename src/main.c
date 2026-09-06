#include <stdio.h>
#include <stdlib.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#include "../include/custom.h"

AppState state;

int main(int argc, char **argv)
{
    state.currentImageFile = NULL;
    state.currentImage = NULL;
    state.undoImage = NULL;
    state.imageWidget = NULL;

    IupOpen(&argc, &argv);
    setupGui();
    IupClose();

    freeState();
    return EXIT_SUCCESS;
}
