#include "Arduino.h"
#include "CircularBuffer.h"
circularBuffer::circularBuffer( int size )
{
	m_size = size ;
	m_buffer = ( unsigned long *) calloc( m_size , sizeof( int )   ) ;
	m_read = 0 ;
	m_write = 1 ;
   m_failed_writes = 0 ;
   m_failed_read = 0 ;
}

unsigned long* circularBuffer::read()
{
	if( ( m_read + 1 ) < m_write )
	{
		++m_read ;
		return (unsigned long*) &m_buffer[ m_read ] ;
	}

   if( m_read > m_write )
   {
      if( ( m_read + 1 ) < m_size )
      {
         ++m_read ;
   		return (unsigned long*) &m_buffer[ m_read ] ;
   	}
   	else
   	{
   	   if( m_write > 0 )
   		{
   		   m_read = 0 ;
   		   return (unsigned long*) &m_buffer[ m_read ] ;
   		 }
   	}
   }
  
	++m_failed_read ;
	return NULL ;
}

int circularBuffer::write( unsigned long value )
{
	if( m_write > m_read )
	{
		if( m_write < m_size )
		{
			m_buffer[ m_write ] = value ;
			++m_write ;
			return 1 ;
		}
		else
		{
			if( m_read > 0 )
			{
				m_write = 0 ;
				m_buffer[ m_write ] = value ;
				++m_write ;
				return 1 ;
			}
		}
	}
	else
	{
		m_buffer[ m_write ] = value ;
		++m_write ;
		return 1 ;
	}

	++m_failed_writes ;
	return 0 ;
}
