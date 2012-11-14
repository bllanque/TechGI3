#ifndef _BITMAP_H
#define _BITMAP_H

#include <stdio.h>

/** Größe des Bitmap-Headers in Bytes */
#define BITMAP_HEADER_SIZE 26

/**
 * Schreibt einen Header für das Windows Bitmap-Format (BMP) in den angegebenen
 * Datenstrom. Als Typ für die Bilddaten wird das 24-Bit-RGB-Format definiert,
 * bei dem jeder Pixel durch einen 8-Bit-Wert für die Grundfarben Blau, Grün und
 * Rot beschrieben wird. Die dem Header folgenden Bilddaten werden zeilenweise,
 * beginnend mit der letzten Zeile geschrieben. 
 * Die Parameter width und height müssen ganzzahlig durch 4 teilbar sein.
 * 
 * width:  Breite der Bitmap-Grafik in Pixeln
 * height: Höhe der Bitmap-Grafik in Pixeln
 */ 
void write_bitmap_header(FILE *stream, int width, int height);

#endif // _BITMAP_H
