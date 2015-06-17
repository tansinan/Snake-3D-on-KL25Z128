/*
 * OLEDFONT.c
 *
 *  Created on: Jun 3, 2015
 *      Author: millin
 */

#include "OLEDFONT.h"
//ASCII Table from 0x20 to 7F
const uchar OLEDFONT[]={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //' '
0x00, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00, //'!'
0x00, 0x00, 0x0F, 0x03, 0x00, 0x0F, 0x03, 0x00, //'"'
0x0c, 0x1e, 0x3f, 0x7e, 0x7e, 0x3f, 0x1e ,0x0c, //'#'//已改成心形
0x00, 0x00, 0x66, 0x49, 0xC9, 0x33, 0x00, 0x00, //'$'
0x00, 0x12, 0x15, 0x52, 0xA8, 0x48, 0x00, 0x00, //'%'
0x00, 0x00, 0x60, 0x9C, 0xB2, 0xC2, 0xA2, 0x00, //'&'
0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, //'''
0x00, 0x00, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, //'('
0x00, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x00, 0x00, //')'
0x00, 0x00, 0x02, 0x1A, 0x07, 0x1A, 0x02, 0x00, //'*'
0x00, 0x10, 0x10, 0x10, 0xFE, 0x10, 0x10, 0x10, //'+'
0x00, 0x00, 0x00, 0xC0, 0x40, 0x00, 0x00, 0x00, //','
0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, //'-'
0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, //'.'
0x00, 0x80, 0x60, 0x18, 0x06, 0x01, 0x00, 0x00, //'/'
0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x7E, 0x00, //'0'
0x00, 0x00, 0x82, 0x82, 0xFF, 0x80, 0x80, 0x00, //'1'
0x00, 0xC2, 0xA1, 0x91, 0x89, 0xC6, 0x00, 0x00, //'2'
0x00, 0x42, 0x81, 0x89, 0x89, 0x76, 0x00, 0x00, //'3'
0x00, 0x10, 0x1C, 0x12, 0x91, 0xFF, 0x90, 0x00, //'4'
0x00, 0x40, 0x8F, 0x89, 0x89, 0x89, 0x71, 0x00, //'5'
0x00, 0x00, 0x7C, 0x8A, 0x89, 0x89, 0x71, 0x00, //'6'
0x00, 0x03, 0x01, 0x01, 0xE1, 0x19, 0x07, 0x00, //'7'
0x00, 0x76, 0x89, 0x89, 0x89, 0x89, 0x76, 0x00, //'8'
0x00, 0x8E, 0x91, 0x91, 0x91, 0x51, 0x3E, 0x00, //'9'
0x00, 0x00, 0x00, 0xCC, 0xCC, 0x00, 0x00, 0x00, //':'
0x00, 0x00, 0x80, 0xCC, 0x4C, 0x00, 0x00, 0x00, //';'
0x00, 0x10, 0x10, 0x28, 0x44, 0x44, 0x82, 0x00, //'<'
0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, //'='
0x00, 0x82, 0x44, 0x44, 0x28, 0x10, 0x10, 0x00, //'>'
0x00, 0x00, 0x02, 0x81, 0xA1, 0x11, 0x0E, 0x00, //'?'
0x00, 0x7e, 0x81, 0x99, 0xa5, 0xbd, 0xa1, 0x7e,	//'@'
0x00, 0x80, 0xC0, 0xBD, 0x23, 0xBC, 0xC0, 0x80, //'A'
0x00, 0x81, 0xFF, 0x89, 0x89, 0x89, 0x76, 0x00, //'B'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x81, 0x43, 0x00, //'C'
0x00, 0x81, 0xFF, 0x81, 0x81, 0x42, 0x3C, 0x00, //'D'
0x00, 0x81, 0xFF, 0x89, 0x9D, 0x81, 0xC3, 0x00, //'E'
0x00, 0x81, 0xFF, 0x89, 0x1D, 0x01, 0x03, 0x00, //'F'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x91, 0x73, 0x10, //'G'
0x00, 0x81, 0xFF, 0x89, 0x08, 0x89, 0xFF, 0x81, //'H'
0x00, 0x00, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x00, //'I'
0x00, 0x70, 0x80, 0x81, 0x81, 0x7F, 0x01, 0x00, //'J'
0x00, 0x81, 0xFF, 0x91, 0x18, 0x25, 0xC3, 0x81, //'K'
0x00, 0x81, 0xFF, 0x81, 0x80, 0x80, 0xE0, 0x00, //'L'
0x00, 0x81, 0xFF, 0x87, 0x18, 0x87, 0xFF, 0x81, //'M'
0x81, 0xFF, 0x83, 0x0C, 0x30, 0xC1, 0xFF, 0x01, //'N'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, //'O'
0x00, 0x81, 0xFF, 0x91, 0x11, 0x11, 0x0E, 0x00, //'P'
0x00, 0x3C, 0x42, 0x81, 0x81, 0x81, 0x42, 0x3C, //'Q'
0x00, 0x81, 0xFF, 0x91, 0x11, 0x31, 0x4E, 0x80, //'R'
0x00, 0xC6, 0x49, 0x89, 0x89, 0x8A, 0x73, 0x00, //'S'
0x00, 0x03, 0x01, 0x81, 0xFF, 0x81, 0x01, 0x03, //'T'
0x00, 0x01, 0x7F, 0x81, 0x80, 0x81, 0x7F, 0x01, //'U'
0x01, 0x07, 0x39, 0xC0, 0xC0, 0x39, 0x07, 0x01, //'V'
0x00, 0x01, 0x7F, 0x81, 0x78, 0x81, 0x7F, 0x01, //'W'
0x00, 0x81, 0xC3, 0xA5, 0x18, 0xA5, 0xC3, 0x81, //'X'
0x00, 0x01, 0x03, 0x8D, 0xF0, 0x8D, 0x03, 0x01, //'Y'
0x00, 0x00, 0xC3, 0xA1, 0x99, 0x85, 0xC3, 0x00, //'Z'
0x00, 0x00, 0x00, 0xFF, 0x01, 0x01, 0x00, 0x00, //'['
0x00, 0x01, 0x06, 0x38, 0xC0, 0x00, 0x00, 0x00, //'\'
0x00, 0x01, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, //']'
0x00, 0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00, //'^'
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //'_'
0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, //'`'
0x00, 0x68, 0x94, 0x94, 0x94, 0x54, 0xF8, 0x80, //'a'
0x81, 0xFF, 0x48, 0x84, 0x84, 0x84, 0x78, 0x00, //'b'
0x00, 0x78, 0x84, 0x84, 0x84, 0x88, 0x4C, 0x00, //'c'
0x00, 0x78, 0x84, 0x84, 0x84, 0x49, 0xFF, 0x80, //'d'
0x00, 0x78, 0x94, 0x94, 0x94, 0x94, 0x98, 0x00, //'e'
0x00, 0x84, 0x84, 0xFE, 0x85, 0x85, 0x85, 0x00, //'f'
0x00, 0x1e, 0xa1, 0xa1, 0xa1, 0x92, 0x7f, 0x01, //'g'
0x00, 0x81, 0xFF, 0x88, 0x04, 0x84, 0xF8, 0x80, //'h'
0x00, 0x00, 0x84, 0x84, 0xFD, 0x80, 0x80, 0x00, //'i'
0x00, 0x80, 0x84, 0x84, 0x85, 0x7C, 0x00, 0x00, //'j'
0x00, 0x81, 0xFF, 0x10, 0x34, 0xCC, 0x84, 0x84, //'k'
0x00, 0x00, 0x80, 0x81, 0xFF, 0x80, 0x80, 0x00, //'l'
0x84, 0xFC, 0x88, 0x04, 0xF8, 0x88, 0x04, 0xF8, //'m'
0x00, 0x84, 0xFC, 0x88, 0x04, 0x84, 0xF8, 0x80, //'n'
0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x78, 0x00, //'o'
0x00, 0x04, 0xFC, 0x88, 0x84, 0x84, 0x78, 0x00, //'p'
0x00, 0x78, 0x84, 0x84, 0x84, 0x48, 0xFC, 0x04, //'q'
0x00, 0x84, 0xFC, 0x88, 0x84, 0x84, 0x04, 0x00, //'r'
0x00, 0xC8, 0x94, 0x94, 0x94, 0x94, 0x6C, 0x00, //'s'
0x00, 0x04, 0x7E, 0x84, 0x84, 0x84, 0x40, 0x00, //'t'
0x00, 0x04, 0x7C, 0x80, 0x80, 0x44, 0xFC, 0x80, //'u'
0x04, 0x0C, 0x34, 0xC0, 0xC0, 0x34, 0x0C, 0x04, //'v'
0x00, 0x04, 0x7C, 0x84, 0x70, 0x84, 0x7C, 0x04, //'w'
0x00, 0x84, 0xCC, 0x30, 0x30, 0xCC, 0x84, 0x00, //'x'
0x00, 0x01, 0x87, 0x99, 0xe0, 0x19, 0x07, 0x01, //'y'
0x00, 0x00, 0xCC, 0xA4, 0x94, 0x8C, 0xC4, 0x00, //'z'
0x00, 0x00, 0x10, 0xEE, 0x01, 0x00, 0x00, 0x00, //'{'
0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, //'|'
0x00, 0x00, 0x01, 0xEE, 0x10, 0x00, 0x00, 0x00, //'}'
0x00, 0x10, 0x08, 0x08, 0x10, 0x10, 0x08, 0x00, //'~'
0x01, 0x3D, 0x42, 0x81, 0x81, 0x81, 0x43, 0x00, //'DEL'
};
