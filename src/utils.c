#include <stdio.h>
#include <stdlib.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#include "../include/custom.h"

int isAppStateValid()
{

  if (state.undoImage == NULL &&
      state.currentImage == NULL &&
      state.currentImageFile == NULL)
  {

    // printf("Debug inside\n");
    Ihandle *dlg = IupMessageDlg();

    IupSetAttribute(dlg, "DIALOGTYPE", "WARNING");
    IupSetAttribute(dlg, "TITLE", "Warning!!!");
    IupSetAttribute(dlg, "BUTTONS", "OK");
    IupSetAttribute(dlg, "VALUE", "You haven't selected an image yet!!!\nBye bye!!!\n");

    IupPopup(dlg, IUP_CURRENT, IUP_CURRENT);

    IupDestroy(dlg);
    return 0;
  }

  // printf("Debug outside\n");

  return 1;
}

void freeState()
{
  if (state.currentImageFile != NULL)
  {
    printf("%s\n", state.currentImageFile);
    free(state.currentImageFile);
  }

  if (state.currentImage != NULL)
    imImageDestroy(state.currentImage);
  if (state.undoImage != NULL)
    imImageDestroy(state.undoImage);
}

void printState()
{
  printf("Filename : %s\n", state.currentImageFile);
  printf("CurrentImage: %p\n", state.currentImage);
  printf("UndoImage: %p\n", state.undoImage);
  printf("ImageWidget: %p\n", state.imageWidget);
}