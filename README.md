# Qt-Image-Zoom-Example

This example imports a jpg image and converts it to a pixmap.  
A viewport is established above the  pixmap.  
The viewport image can be zoomed by using the mouse wheel.
The viewport can be dragged over the pixmap with the wheel button.
An accompanying frame displays a full image with the viewport 
displayed as an overlayed rectangle.  This rectangle can be 
translated with the WASD keys or the arrow keys.  The rectangle 
can be dragged with the mouse wheel button.

Actually, I used the the pixmap on the heap which is not the 
best thing to do.  Can use QPixmap pixmap rather than QPixmap* pixmap. 
This should give faster drawing.  Is much easier to just use QImage 
rather than QPixmap.

