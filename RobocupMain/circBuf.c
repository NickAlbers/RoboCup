//*****************************************************************************
// circBuf.c
//
// Created on: May 7, 2015
// Author: Nick Albers and Mike Arnigo
//*****************************************************************************

#include "stdlib.h"
#include "circBuf.h"

// ****************************************************************************
// Init_Circ_Buff: Initialise the circBuf instance. Reset both indices to
// the start of the buffer.  Dynamically allocate and clear the the 
// memory and return a pointer for the data.  Return NULL if 
// allocation fails.
//*****************************************************************************

unsigned long *
Init_Circ_Buff (circBuf_t *buffer, unsigned int size)
{
	buffer->windex = 0;
	buffer->rindex = 0;
	buffer->size = size;
	buffer->data = 
        (unsigned long *) calloc (size, sizeof(unsigned long));
	return buffer->data;
}
   // Note use of calloc() to clear contents.

// ****************************************************************************
// Write_Circ_Buff: insert entry at the current windex location,
// advance windex.
//*****************************************************************************

void
Write_Circ_Buff (circBuf_t *buffer, unsigned long entry)
{
	buffer->data[buffer->windex] = entry;
	buffer->windex++;
	if (buffer->windex >= buffer->size)
	   buffer->windex = 0;
}

// ****************************************************************************
// Read_Circ_Buff: return entry at the current rindex location,
// advance rindex. No checking for overrun.
//*****************************************************************************

unsigned long
Read_Circ_Buff (circBuf_t *buffer)
{
	unsigned long entry;
	
	entry = buffer->data[buffer->rindex];
	buffer->rindex++;
	if (buffer->rindex >= buffer->size)
	   buffer->rindex = 0;
    return entry;
}

// ****************************************************************************
// Free_Circ_Buff: Releases the memory allocated to the buffer data,
// sets pointer to NULL and ohter fields to 0. The buffer can
// re initialised by another call to Init_Circ_Buff().
//*****************************************************************************

void
Free_Circ_Buff (circBuf_t * buffer)
{
	buffer->windex = 0;
	buffer->rindex = 0;
	buffer->size = 0;
	free (buffer->data);
	buffer->data = NULL;
}

