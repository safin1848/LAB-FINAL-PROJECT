#include <stdint.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#ifndef MY_CUSTOM_HEADER
#define MY_CUSTOM_HEADER

// GUI Setup Declarations
void setupGui();

// UI update
void updateUIImage(Ihandle *self);

// Just 2-3 error checking function
int isAppStateValid();

// Control/Callback Function Declarations
int grayScale_clb(Ihandle *self);
int Inversion_clb(Ihandle *self);
int horizontalFlip_clb(Ihandle *self);
int verticalFlip_clb(Ihandle *self);
int rotate90_clb(Ihandle *self);
int blur_clb(Ihandle *self);
int undo_clb(Ihandle *self);

int crop_clb(Ihandle *self);
int brightness_clb(Ihandle *self);

// Menu callback functions
int open_clb(Ihandle *self);
int saveAs_clb(Ihandle *self);
int ext_clb(Ihandle *self);
// Image struct

typedef struct
{
  int width;
  int height;
  uint8_t *data;
} Image;

// Application State

typedef struct
{
  char *currentImageFile;
  imImage *currentImage;
  imImage *undoImage;
  Ihandle *imageWidget;
} AppState;

// Globally declare the appstate

extern AppState state;
void freeState();
void printState();

#endif