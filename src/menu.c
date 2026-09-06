#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#include "../include/custom.h"

int open_clb(Ihandle *self)
{
  Ihandle *file_dlg = IupFileDlg();
  IupSetAttribute(file_dlg, "DIALOGTYPE", "OPEN");
  IupSetAttribute(file_dlg, "TITLE", "Select a BMP Image");
  IupSetAttribute(file_dlg, "EXTFILTER", "BMP Images (*.bmp)|*.bmp|");

  IupPopup(file_dlg, IUP_CENTER, IUP_CENTER);

  if (IupGetInt(file_dlg, "STATUS") != -1)
  {
    char *fileName = IupGetAttribute(file_dlg, "VALUE");
    size_t s = strlen(fileName);
    state.currentImageFile = (char *)malloc(sizeof(char) * (s));
    strcpy(state.currentImageFile, fileName);

    // printf("%s\n", state.currentImageFile);

    int err;
    state.currentImage = imFileImageLoadBitmap(state.currentImageFile, 0, &err);
    state.undoImage = imImageDuplicate(state.currentImage);

    if (err)
    {
      printf("Error code in open_clb : %d\n", err);
    }

    updateUIImage(self);
  }

  IupDestroy(file_dlg);
  return IUP_DEFAULT;
}

int saveAs_clb(Ihandle *self)
{
  if (!isAppStateValid())
    return IUP_DEFAULT;

  Ihandle *file_dlg = IupFileDlg();
  IupSetAttribute(file_dlg, "DIALOGTYPE", "SAVE");
  IupSetAttribute(file_dlg, "TITLE", "Save image as...");
  IupSetAttribute(file_dlg, "EXTFILTER", "BMP Images (*.bmp)|*.bmp|");
  IupSetAttribute(file_dlg, "EXTDEFAULT", "bmp");

  IupPopup(file_dlg, IUP_CENTER, IUP_CENTER);

  if (IupGetInt(file_dlg, "STATUS") != -1)
  {
    char *fileName = IupGetAttribute(file_dlg, "VALUE");
    int err = imFileImageSave(fileName, "BMP", state.currentImage);

    if (err)
    {
      // printf("Debug inside\n");
      Ihandle *dlg = IupMessageDlg();

      IupSetAttribute(dlg, "DIALOGTYPE", "WARNING");
      IupSetAttribute(dlg, "TITLE", "Error!!!");
      IupSetAttribute(dlg, "BUTTONS", "OK");
      IupSetAttribute(dlg, "VALUE", "Couldn't save the image");
      IupPopup(dlg, IUP_CURRENT, IUP_CURRENT);
      IupDestroy(dlg);
    }
    else
    {
      Ihandle *dlg = IupMessageDlg();

      IupSetAttribute(dlg, "DIALOGTYPE", "WARNING");
      IupSetAttribute(dlg, "TITLE", "Success!!!");
      IupSetAttribute(dlg, "BUTTONS", "OK");
      IupSetAttribute(dlg, "VALUE", "Success fully saved the image");
      IupPopup(dlg, IUP_CURRENT, IUP_CURRENT);
      IupDestroy(dlg);
    }

    updateUIImage(self);
  }

  IupDestroy(file_dlg);
  return IUP_DEFAULT;
}

int ext_clb(Ihandle *self)
{
  return IUP_CLOSE;
}