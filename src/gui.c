#include <stdio.h>
#include <stdlib.h>

#include <iup.h>

#include <im.h>
#include <im_image.h>
#include <iupim.h>

#include "../include/custom.h"

void setupGui()
{
  // main window and Vertical box to organize elements top to bottom
  Ihandle *window, *vbox;

  // all menu items
  Ihandle *file_menu, *item_open, *item_exit, *item_save_as;
  Ihandle *menu, *sub1_menu;

  // Feature buttons
  Ihandle *btn_grayScale = IupButton("Grayscale", NULL);
  Ihandle *btn_Inversion = IupButton("Inversion", NULL);
  Ihandle *btn_horizontalFlip = IupButton("Horizontal Flip", NULL);
  Ihandle *btn_verticalFlip = IupButton("Vertical Flip", NULL);
  Ihandle *btn_rotate90 = IupButton("Rotate 90deg", NULL);
  Ihandle *btn_blur = IupButton("Blur", NULL);
  Ihandle *btn_undo = IupButton("Undo", NULL);

  // Added all the call back functions to buttons
  IupSetCallback(btn_grayScale, "ACTION", (Icallback)grayScale_clb);
  IupSetCallback(btn_Inversion, "ACTION", (Icallback)Inversion_clb);
  IupSetCallback(btn_horizontalFlip, "ACTION", (Icallback)horizontalFlip_clb);
  IupSetCallback(btn_verticalFlip, "ACTION", (Icallback)verticalFlip_clb);
  IupSetCallback(btn_rotate90, "ACTION", (Icallback)rotate90_clb);
  IupSetCallback(btn_blur, "ACTION", (Icallback)blur_clb);
  IupSetCallback(btn_undo, "ACTION", (Icallback)undo_clb);

  Ihandle *hbox = IupHbox(
      btn_grayScale,
      btn_Inversion,
      btn_horizontalFlip,
      btn_verticalFlip,
      btn_rotate90,
      btn_blur,
      btn_undo,
      NULL);

  IupSetAttribute(hbox, "GAP", "4");

  Ihandle *cropXInput = IupText(NULL);
  IupSetAttribute(cropXInput, "MASK", IUP_MASK_UINT);
  IupSetAttribute(cropXInput, "VISIBLECOLUMNS", "4"); // Keep the boxes small

  Ihandle *cropYInput = IupText(NULL);
  IupSetAttribute(cropYInput, "MASK", IUP_MASK_UINT);
  IupSetAttribute(cropYInput, "VISIBLECOLUMNS", "4");

  Ihandle *cropWInput = IupText(NULL);
  IupSetAttribute(cropWInput, "MASK", IUP_MASK_UINT);
  IupSetAttribute(cropWInput, "VISIBLECOLUMNS", "4");

  Ihandle *cropHInput = IupText(NULL);
  IupSetAttribute(cropHInput, "MASK", IUP_MASK_UINT);
  IupSetAttribute(cropHInput, "VISIBLECOLUMNS", "4");

  // 2. Create the button and bind the callback
  Ihandle *cropBtn = IupButton("Crop Image", NULL);
  IupSetCallback(cropBtn, "ACTION", (Icallback)crop_clb);

  // 3. Attach all 4 input boxes to the button so the callback can read them easily
  IupSetAttributeHandle(cropBtn, "CROP_X", cropXInput);
  IupSetAttributeHandle(cropBtn, "CROP_Y", cropYInput);
  IupSetAttributeHandle(cropBtn, "CROP_W", cropWInput);
  IupSetAttributeHandle(cropBtn, "CROP_H", cropHInput);

  // 4. Pack them neatly together in a single row
  Ihandle *hboxCrop = IupHbox(
      IupLabel("Crop - X: "), cropXInput,
      IupLabel(" Y: "), cropYInput,
      IupLabel(" Width: "), cropWInput,
      IupLabel(" Height: "), cropHInput,
      cropBtn,
      NULL);

  IupSetAttribute(hboxCrop, "ALIGNMENT", "ACENTER");
  IupSetAttribute(hboxCrop, "MARGIN", "10x10");

  // Brightness adjustment label,input,button
  Ihandle *brightnessLabel, *brightnessInput, *brightnessBtn, *hboxBrightnessAdjustment;
  brightnessLabel = IupLabel("Brightness Adjustment (-255 to 255) : ");
  brightnessInput = IupText(NULL);
  brightnessBtn = IupButton("Apply", NULL);

  // only take integers as input
  IupSetAttribute(brightnessInput, "MASK", IUP_MASK_INT);
  IupSetAttribute(brightnessInput, "VISIBLECOLUMNS", "5");

  IupSetAttributeHandle(brightnessBtn, "MY_INPUT_TXT", brightnessInput);
  IupSetCallback(brightnessBtn, "ACTION", (Icallback)brightness_clb);

  hboxBrightnessAdjustment = IupHbox(brightnessLabel, brightnessInput, brightnessBtn, NULL);
  IupSetAttribute(hboxBrightnessAdjustment, "ALIGNMENT", "ACENTER");

  Ihandle *label = IupLabel("Image : ");

  // Image Label
  state.imageWidget = IupLabel(NULL);

  // this is to force GTK-3 to treat the widget as a image widget
  IupSetAttribute(state.imageWidget, "IMAGE", "DUMMY_INIT_NAME");
  IupSetAttribute(state.imageWidget, "TITLE", NULL);

  IupSetAttribute(state.imageWidget, "EXPAND", "YES");
  IupSetAttribute(state.imageWidget, "ALIGNMENT", "ACENTER:ACENTER");

  // Menu items initialized and setup callbacks

  // open
  item_open = IupItem("Open", NULL);
  IupSetCallback(item_open, "ACTION", (Icallback)open_clb);

  // save as
  item_save_as = IupItem("Save as", NULL);
  IupSetCallback(item_save_as, "ACTION", (Icallback)saveAs_clb);

  // exit
  item_exit = IupItem("Exit", NULL);
  IupSetCallback(item_exit, "ACTION", (Icallback)ext_clb);

  // organizing menu items
  file_menu = IupMenu(item_open, item_save_as, IupSeparator(), item_exit, NULL);
  sub1_menu = IupSubmenu("File", file_menu);
  menu = IupMenu(sub1_menu, NULL);

  vbox = IupVbox(hbox, hboxBrightnessAdjustment, hboxCrop, label, state.imageWidget, NULL);
  IupSetAttribute(vbox, "ALIGNMENT", "ACENTER");
  IupSetAttribute(vbox, "GAP", "10");

  // window initialization code
  window = IupDialog(vbox);

  // setting the menu to window
  IupSetAttributeHandle(window, "MENU", menu);
  IupSetAttribute(window, "TITLE", "Image Manipulation Software");
  IupSetAttribute(window, "EXPAND", "YES");
  IupSetAttribute(window, "SIZE", "500x300");
  // I wanted to add these but it is blocked to the os level on my debian gtk environment
  // I don't want to waste my time with this garbage.
  // IupSetAttribute(window, "RESIZE", "YES");
  // IupSetAttribute(window, "MAXBOX", "YES");
  // IupSetAttribute(window, "MINBOX", "YES");

  IupShowXY(window, IUP_CENTER, IUP_CENTER);

  IupMainLoop();
}