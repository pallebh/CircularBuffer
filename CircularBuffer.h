#ifndef circularBuffer_H
#define circularBuffer_H

class circularBuffer
{
	public :
		//constructor
		circularBuffer( int size ) ;
      
      // interface
		unsigned long* read() ; // NULL means notthing to read
		int write( unsigned long value ) ; // NULL means value was not saved in the buffer
		
	private :
		// variables
		int m_size ;
		volatile unsigned long* m_buffer ;
		volatile int m_read ;
		volatile int m_write ;

		volatile int m_failed_writes ;
		volatile int m_failed_read ;
} ;

#endif 