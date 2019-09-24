#ifndef _MSG_Q_
#define _MSG_Q_


typedef enum
{
	MSG_QUEUE_BAD_ALLOC,
	MSG_QUEUE_NOT_INIT,
	MSG_QUEUE_OVERFLOW,
	MSG_QUEUE_UNDERFLOW,
	MSG_QUEUE_BUFFER_TOO_SMALL,
	MSG_QUEUE_SUCCESS
	
}SharedMessageQueueResult;


typedef struct SharedMessageQueue SharedMessageQueue;

/**
 * 
 * @breif: This method creates a message queue
 * 
 * @parms:
 * 			_name: Message queue name <file path>
 * 			_ memSize: memory size
 * 
 * @return: pointer to shared message queue when success else NULL
 * */
SharedMessageQueue* SharedMessageQueue_Create(const char *_name, size_t _memSize);

/**
 * 
 * @brief: This method connects to a message queue
 * 
 * @params:
 * 			_name: Message queue name <file path>
 * 			
 * @return: pointer to shared message queue when success else NULL
 * */

SharedMessageQueue* SharedMessageQueue_Connect(const char *_name);

/**
 * @brief: This method destroy a message queue
 * 
 * @params:
 * 			_q: pointer to message queue created by SharedMessageQueue_Create
 * */

void SharedMessageQueue_Destroy(SharedMessageQueue *_q);

/**
 * @brief: This method put a message in the queue
 * 
 * @params:
 * 			_q: pointer to message queue
 * 			_buffer: message content
 * 			_bufSize: message size in bytes
 * 
 * @return: MSG_QUEUE_SUCCESS when success else MSG_QUEUE_NOT_INIT or MSG_QUEUE_FULL
 * */

SharedMessageQueueResult SharedMessageQueue_Send (SharedMessageQueue *_q, void* _buffer, size_t _bufSize);

/**
 * @brief: This method receives a message from the queue
 * 
 * @params:
 * 			_q: pointer to message queue
 * 			_buffer: place to get the message
 * 			_bufSize: size of the buffer
 * 			_bytesRead: a place to return how many bytes received
 * 
 * @return: MSG_QUEUE_SUCCESS when success else MSG_QUEUE_NOT_INIT or MSG_QUEUE_EMPTY
 * */

SharedMessageQueueResult SharedMessageQueue_Recv (SharedMessageQueue *_q, void* _buffer, size_t _bufSize, size_t* _bytesRead);

/**
 * @brief: This method check if the queue is empty
 * 
 * @params:
 * 			_q: pointer to message queue
 * 
 * @return: 1 if empty else 0
 * 
 * */
int SharedMessageQueue_IsEmpty (SharedMessageQueue* _q);

#endif
