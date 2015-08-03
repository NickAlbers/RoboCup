#ifndef CIRCBUF_H_
#define CIRCBUF_H_

//*****************************************************************************
// circBuf.h
//
// Created on: May 7, 2015
// Author: Nick Albers and Mike Arnigo
//*****************************************************************************


//*****************************************************************************
// Buffer structure
//*****************************************************************************

typedef struct {
	unsigned int size;	// Number of entries in buffer
	unsigned int windex;	// index for writing, mod(size)
	unsigned int rindex;	// index for reading, mod(size)
	unsigned long *data;	// pointer to the data
} circBuf_t;


// *******************************************************
// Init_Circ_Buff: Initialise the circBuf instance. Reset both indices to
// the start of the buffer.  Dynamically allocate and clear the the 
// memory and return a pointer for the data.  Return NULL if 
// allocation fails.
//*****************************************************************************

unsigned long *
Init_Circ_Buff (circBuf_t *buffer, unsigned int size);


// *******************************************************
// Write_Circ_Buff: insert entry at the current windex location,
// advance windex.
//*****************************************************************************

void
Write_Circ_Buff (circBuf_t *buffer, unsigned long entry);


// *******************************************************
// Read_Circ_Buff: return entry at the current rindex location,
// advance rindex. No checking for overrun.
//*****************************************************************************

unsigned long
Read_Circ_Buff (circBuf_t *buffer);


// *******************************************************
// Free_Circ_Buff: Releases the memory allocated to the buffer data,
// sets pointer to NULL and ohter fields to 0. The buffer can
// re initialised by another call to Init_Circ_Buff().
//*****************************************************************************

void
Free_Circ_Buff (circBuf_t *buffer);

#endif /*CIRCBUF_H_*/

