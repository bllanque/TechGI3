#ifndef _MANDELBROT_H
#define _MANDELBROT_H

#include "color.h"

/** Maximale Anzahl der Iterationen zur Bestimmung der Konvergenz der Folge.
 *  Kann reduziert werden, falls die Berechnung zu lange dauert.
 */
#define MAX_ITERATIONS 100

/** Gibt die X-Komponente (Realteil) des Bildmittelpunktes an */
#define CENTER_X -1.1728    /* Standard: -0.4 */

/** Gibt die Y-Komponente (Imaginärteil) des Bildmittelpunktes an */
#define CENTER_Y 0.29575    /* Standard: 0 */

/** Gibt die Breite des Bildes an */
#define DOMAIN_WIDTH 0.002  /* Standard: 2.5 */


/**
  * Berechnet eine grafische Darstellung der Mandelbrotmenge, die als Bitmap
  * im übergebenen Puffer gespeichert wird. Dazu wird jeder Pixel durch ein Element
  * des Typs pixel_data_t repräsentiert, welches jeweils 8-Bit-Werte für den Rot-
  * Grün- und Blauanteil des Pixels enthält. Die Parameter clip_x, clip_y, clip_width
  * und clip_height erlauben die Beschränkung der Berechnung auf einen kleineren
  * Ausschnitt der gesamten Grafik.
  *
  * data: Zeiger auf einen clip_width*clip_height großen Speicherbereich, in den die
  *       RGB-Daten des generierten Bildausschnittes geschrieben werden. Die Daten werden
  *       zeilenweise in den Puffer gespeichert: Nach data[0] werden die Daten des 1. Pixels
  *       der 1. Zeile des Ausschnittes geschrieben, nach data[clip_width-1] die Pixeldaten
  *       für letzten Pixel der 1. Zeile, an data[(clip_width * clip_height) - 1] die
  *       Daten für den letzten Pixel der letzten Zeile des Ausschnittes.
  *
  * full_width / full_height: Breite/Höhe des Gesamtbildes in Pixeln
  *
  * clip_x     : X-Koordinate des Ausschnittes innerhalb des Gesamtbildes
  * clip_y     : Y-Koordinate des Ausschnittes innerhalb des Gesamtbildes
  * clip_width : Breite des zu berechnenden Bildausschnittes
  * clip_height: Höhe des zu berechnenden Bildausschnittes
  */
void calc_mandelbrot(pixel_data_t *data, int full_width, int full_height,
                     int clip_x, int clip_y, int clip_width, int clip_height);

#endif // _MANDELBROT_H
