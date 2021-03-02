#ifndef __CHANNEL_H_
#define __CHANNEL_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stddef.h>  /* size_t */

/** 
 *  @file channel.h
 *  @brief Channel based on serial Comm datat structure module.
 *	
 *  @details  Implements a Channel DS based on msgq structure.
 *  user can send any cind of data/structure or msg he wants.
 *
 * @warning: all Channel functions are unsafe functions! user is responsible for
 * providing valid data! if the caller passes invalid data, behavior is undefined!
 *
 *  @author adham
 * 
 *  @bug send func -fails on test.
 */



typedef struct Channel Channel;

typedef enum ChannelStatus{
	CHANNEL_SUCCESS =0,
	CHANNEL_INVALID_FUNCTION_PARAMETER,
	CHANNEL_UN_INITIALIZED,
	CHANNEL_TRANSMITTING_ERROR,
	CHANNEL_RECEIVING_ERROR
	
}ChannelStatus;

typedef enum CHANNEL_FLAGS
{
	CHANNEL_CREATE = 1,
	CHANNEL_OPEN = 2,
	CHANNEL_EXCL = 4
}CHANNEL_FLAGS;


/** 
 * @brief Create a Channel DS 
 * 
 * @param _bufferSize: Channe Max buufer size in Bytes units
 * @param _path: path or any other string wich will provide achannel unique id. 
 * @param _flags: same flags as msg q flags. flags will be added with bitwise or with permissions.
 * @return a pointer to channel on success or null in failure.
 * @warning: if _buuferSize passed with zero size, Channel size will be created with
 * default size.  
 */
Channel* ChannelCreate(const char* _channelName, size_t _bufferSize,CHANNEL_FLAGS _flags);

/** 
 * @brief Send user msg over channel resource. 
 * 
 * @param _channel: Channe pointer wich was created in function above.
 * @param _pMsg: pointer to user msg. 
 * @param _msgSize: sizeof the msg above (not including long mtype struct member).
 * 
 * @return a channel status error enum.
 * @retval CHANNEL_SUCCESS: on success case.
 * @retval CHANNEL_UN_INITIALIZED: in null channel pointer receiving.
 * @retval CHANNEL_INVALID_FUNCTION_PARAMETER: _msgSize=0 or _pMsg=NULL 
 * @retval CHANNEL_TRANSMITTING_ERROR, on any other error while Tx  
 * @warning: if _buuferSize passed with zero size, Channel size will be created with
 * default size.  
 */
ChannelStatus ChannelTransmit(Channel* _channel, const void* _pMsg, size_t _msgSize);

/** 
 * @brief Receive user msg over channel resource. 
 * 
 * @param _channel: Channe pointer wich was created in function above.
 * @param _pMsg: pointer to user msg. 
 * @param _msgSize: sizeof the msg above (not including long mtype struct member).
 * 
 * @return a channel status error enum.
 * @retval CHANNEL_SUCCESS: on success case.
 * @retval CHANNEL_UN_INITIALIZED: in null channel pointer receiving.
 * @retval CHANNEL_INVALID_FUNCTION_PARAMETER: _msgSize=0 or _pMsg=NULL 
 * @retval CHANNEL_RECEIVING_ERROR, on any other error while Rx  
 * @warning: if _buuferSize passed with zero size, Channel size will be created with
 * default size.  
 */
ChannelStatus ChannelReceive(Channel* _channel, void* _pMsg, size_t _msgSize);

/** 
 * @brief Destroy Channel DS and setting its pointer to NULL. 
 * 
 * @param _channel: Channe pointer Address wich was created in function above.
 * 
 *
 * @return void
 * @warning: if channel is not empty and caller call Destroying function, data will
 * lost.  
 */
void ChannelDestroy(Channel** _channel);




#endif /*__CHANNEL_H_*/
