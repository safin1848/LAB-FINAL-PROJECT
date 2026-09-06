#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iup.h>
#include <im.h>
#include <im_image.h>
#include <iupim.h>

#include "../include/custom.h"

void updateUIImage(Ihandle *self)
{
  if (state.currentImage == NULL)
  {
    printf("Error : Couldn't update UI Image because no current image found\n");
    return;
  }

  if (state.imageWidget == NULL)
  {
    printf("Error : couldn't imageWidget not initialized\n");
    return;
  }

  Ihandle *old_img = (Ihandle *)IupGetAttributeHandle(state.imageWidget, "IMAGE");
  Ihandle *new_img = IupImageFromImImage(state.currentImage);

  /*
  if (!old_img)
  {
    printf("Couldn't get old_img in updateUIImage()\n");
    return;
  }
  */

  if (!new_img)
  {
    printf("Couldn't get new_img in updateUIImage()\n");
    return;
  }

  IupSetAttribute(state.imageWidget, "TITLE", NULL);
  IupSetAttributeHandle(state.imageWidget, "IMAGE", new_img);

  IupUpdate(state.imageWidget);
  IupMap(state.imageWidget);
  IupRefresh(state.imageWidget);

  if (old_img)
    IupDestroy(old_img);
}