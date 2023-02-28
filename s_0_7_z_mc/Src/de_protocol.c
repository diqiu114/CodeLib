#include <string.h>
#include <stdbool.h>
#include "de_protocol.h"
#include "de_protocol_frame.h"
#include "debug.h"
#include "mem_malloc.h"
#include "cmsis_os.h"
#include "iap.h"

static uint8_t protocol_ser = 0;
static uint8_t query_more = 0;
//logger
static uint8_t query_type = 0xff;
static uint8_t query_lvl = 0xff;
static uint32_t query_start_ts = 0;
static uint32_t query_end_ts = 0;

static uint8_t crc8( uint8_t * pdata, uint16_t length ){
	uint8_t crc = 0;

	if ( length <= 0 ) {
		return crc;
	}
	while( length-- != 0 ) {
		for ( uint16_t i = 0x80; i != 0; i /= 2 ) {
			if ( (crc & 0x80) != 0) {
				crc *= 2;
				crc ^= 0x07; //
			} else {
				crc *= 2;
			}
			if ( (*pdata & i) != 0 ) {
				crc ^= 0x07;
			}
		}
		pdata++;
	}
	
	return crc;
}


errStatus_t de_protocol_check(uint8_t *pdata,uint16_t length) {
	
	if(pdata == NULL) return errErr;

	de_protocol_t *protocol = (de_protocol_t *)pdata;

	if(protocol->sof != 0x68) return errErr;

	if(length < 9) return errErr;

	uint16_t data_area_length = (uint16_t)protocol->data_length_h << 8 | protocol->data_length_l;

	uint16_t frame_length = data_area_length + 9;
	
	if(frame_length > length) return errErr;

	if(pdata[frame_length-1] != 0x16) return errErr;
	
	uint8_t checksum = crc8(pdata,frame_length - 2);

	return (checksum == pdata[frame_length-2]) ? errOK : errErr;
}


uint16_t fill_query_logger(uint8_t which,
                           uint8_t type,
                           uint8_t lvl,
                           uint32_t start_time,
                           uint32_t end_time,
                           uint8_t *p);

uint16_t de_protocol_slave_package_fill(uint8_t  *p,
							  uint8_t        ctrl,
		                      uint8_t        src,
					          uint8_t        dest,
					          uint8_t        ser,
					          uint16_t       tag_mask,
                              uint8_t        *pdata,
                              uint16_t       length)
{
    uint16_t index = 0;
	uint16_t index_tlv_length;
	uint16_t index_v_length;
	uint16_t temp_length;
	p[index++] = 0x68;

	p[index++] = dest;
	p[index++] = src;
	p[index++] = ctrl;
	p[index++] = ser;

	index_tlv_length = index;
	p[index++] = 0;
	p[index++] = 0;


    if(tag_mask & TAG_MASK_Logger) {
        p[index++] = TAG_Logger;

		index_v_length = index;
	    p[index++] = 0;
		p[index++] = 0;

        memcpy(p + index,pdata,length);
        index += length;
        
		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;

	}

	temp_length = (index - index_tlv_length - 2);
	p[index_tlv_length] = temp_length >> 8;
	p[index_tlv_length + 1] = temp_length;

	p[index] = crc8(p,index);
	index++;
	p[index++] = 0x16;

	return index;
}
void LoggerRequest(Logger_Msg_t logger);
uint16_t de_protocol_slave_package(uint8_t  *p,
							  uint8_t        ctrl,
		                      uint8_t        src,
					          uint8_t        dest,
					          uint8_t        ser,
					          uint16_t       tag_mask,
						      HandleResult  *result,
						      uint8_t        resultcnt)
{
	uint16_t index = 0;
	uint16_t index_tlv_length;
	uint16_t index_v_length;
	uint16_t temp_length;
	p[index++] = 0x68;

	p[index++] = dest;
	p[index++] = src;
	p[index++] = ctrl;
	p[index++] = ser;

	index_tlv_length = index;
	p[index++] = 0;
	p[index++] = 0;

	if(tag_mask & TAG_MASK_Status) {
		p[index++] = TAG_Status;

		index_v_length = index;
	    p[index++] = 0;
		p[index++] = 0;

		//add device information here.
		//...
 
        index += fill_query_status(query_more,p+index);

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;

	}

	if(tag_mask & TAG_MASK_Control) {


	}
    
    if(tag_mask & TAG_MASK_Logger) {
        p[index++] = TAG_Logger;

		index_v_length = index;
	    p[index++] = 0;
		p[index++] = 0;

        uint16_t  temp = fill_query_logger(query_more,query_type,query_lvl,query_start_ts,query_end_ts,p+index);
        if(temp == 0) {
            return 0;
        }
        
        index += temp;

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;

	}

	if(tag_mask & TAG_MASK_Config) {
		p[index++] = TAG_Config;
		index_v_length = index;
		p[index++] = 0;
		p[index++] = 0;

		if(ctrl & CTRL_WriteAck) {
			for(uint8_t i=0;i<resultcnt;i++) {
				p[index++] = result[i].DataId;
				p[index++] = result[i].result;
			}
		} else {

			index += fill_query_config(p+index);
		}

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;
	}
    
    if(tag_mask & TAG_MASK_Upgrade) {
		p[index++] = TAG_Upgrade;
		index_v_length = index;
		p[index++] = 0;
		p[index++] = 0;

		
        for(uint8_t i=0;i<resultcnt;i++) {
            p[index++] = result[i].DataId;
            p[index++] = result[i].result;
        }

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;
	}
    
    if(tag_mask & TAG_MASK_Transfer) {
        p[index++] = TAG_TransferData;
		index_v_length = index;
		p[index++] = 0;
		p[index++] = 0;

        for(uint8_t i=0;i<resultcnt;i++) {
            p[index++] = result[i].DataId;
            p[index++] = result[i].result;
        }

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;
    }
    
	temp_length = (index - index_tlv_length - 2);
	p[index_tlv_length] = temp_length >> 8;
	p[index_tlv_length + 1] = temp_length;

	p[index] = crc8(p,index);
	index++;
	p[index++] = 0x16;

	return index;


}


uint16_t de_protocol_master_package(uint8_t       *p,
							         uint8_t        ctrl,
		                             uint8_t        src,
					                 uint8_t        dest,
					                 uint8_t        ser,
					                 uint32_t       tag_mask,
									 uint8_t        query_detail,
									 uint8_t       *p_content,
									 uint16_t       p_length,
						             HandleResult  *result,
						             uint8_t        resultcnt)
{
	uint16_t index = 0;
	uint16_t index_tlv_length;
	uint16_t index_v_length;
	uint16_t temp_length;
	p[index++] = 0x68;

	p[index++] = dest;
	p[index++] = src;
	p[index++] = ctrl;
	p[index++] = ser;

	index_tlv_length = index;
	p[index++] = 0;
	p[index++] = 0;

	if(tag_mask & TAG_MASK_Query) {
		p[index++] = TAG_Query;

		index_v_length = index;
		p[index++] = 0;
		p[index++] = 0;

		p[index++] = query_detail;
		p[index++] = 1;

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;
	}


	if(tag_mask & TAG_MASK_Control) {
		p[index++] = TAG_Control;

		index_v_length = index;
		p[index++] = 0;
		p[index++] = 0;

		if(p_length > 0) {
			memcpy(p+index,p_content,p_length);
			index += p_length;
		}

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;

	}

	if(tag_mask & TAG_MASK_Config) {
		p[index++] = TAG_Config;

		index_v_length = index;
		p[index++] = 0;
		p[index++] = 0;

		if(p_length > 0) {
			memcpy(p+index,p_content,p_length);
			index += p_length;
		}

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;
	}

	if(tag_mask & TAG_MASK_Upgrade) {
		p[index++] = TAG_Upgrade;

		index_v_length = index;
		p[index++] = 0;
		p[index++] = 0;

		if(p_length > 0) {
			memcpy(p+index,p_content,p_length);
			index += p_length;
		}

		temp_length = index - index_v_length - 2;
		p[index_v_length] = temp_length >> 8;
		p[index_v_length + 1] = temp_length;

	}

	temp_length = (index - index_tlv_length - 2);
	p[index_tlv_length] = temp_length >> 8;
	p[index_tlv_length + 1] = temp_length;

	p[index] = crc8(p,index);
	index++;
	p[index++] = 0x16;

	return index;

}
void cell_module_query_status_response_handle(uint8_t id,uint8_t *pdata,uint16_t length,uint8_t ser);

void de_protocol_master_process(COMM_TYPE_t type,uint8_t *pdate,uint16_t length) {
	de_protocol_t *pMsg;
	uint8_t *p = NULL;

	uint16_t tlvs_length;
	uint16_t index;
	uint8_t   T;
	uint16_t  L;
	uint8_t  *V;
	uint8_t  control;
	uint16_t  tagmask = 0;

	HandleResult result = {0};
	uint8_t      result_cnt = 0;

	if(de_protocol_check(pdate, length) != errOK) {
        pMsg = NULL;
        return;
    }
		

	pMsg = (de_protocol_t *)pdate;

	tlvs_length = (uint16_t)pMsg->data_length_h << 8 | pMsg->data_length_l;
	control = pMsg->ctrl;
	index = 0;

	while(index + 4 < tlvs_length) {
		T = pMsg->tlvs[index++];
		L = pMsg->tlvs[index] << 8 | pMsg->tlvs[index+1];
		index += 2;
		V = pMsg->tlvs + index;
		switch(T) {
			case TAG_Status:
				cell_module_query_status_response_handle(pMsg->source,V,L,pMsg->ser);
				break;

			case TAG_Control:
				break;

			case TAG_Config:
				if(control & CTRL_WriteAck) {
					//power_module_config_response_handle(V,L,pMsg->ser);
				} else {
					//power_module_query_config_response_handle(V,L,pMsg->ser);
				}

				break;

			case TAG_Upgrade:
				//power_module_upgrade_response_handle(V,L,pMsg->ser);
				break;
			default:
				break;
		}
		index += L;
	}
}

void protocol_send_bytes(COMM_TYPE_t type,uint8_t *pdata,uint16_t length) {
    switch(type) {
        case COMM_TYPE_ETH:
            eth_sendbytes(pdata,length);
            break;
        case COMM_TYPE_USB:
            break;
        default:
        case COMM_TYPE_COM:
        case COMM_TYPE_485:
            Bsp_Rs485SendBytes(pdata,length);
            break;
    }
}
void logger_set_ack(uint8_t,uint8_t);
void CellTranferRequest(uint8_t *pMsg,uint16_t length);
void protocol_handle_config(uint8_t *pdata,uint16_t length,HandleResult *result,int *resultcnt);
bool de_protocol_process(COMM_TYPE_t type,uint8_t *pdate,uint16_t length) {
    
	de_protocol_t *pMsg;
	uint8_t *p = NULL;
	uint8_t break_flag = 0;
	uint8_t ctrl_code = CTRL_Response;
	
	uint16_t  tlvs_length;
	uint16_t  index;
	uint8_t   T;
	uint16_t  L;
	uint8_t  *pV;
	uint32_t  tagmask = 0;
    
	
	HandleResult *result = NULL;
	int           result_cnt = 0;

	if(de_protocol_check(pdate, length) != errOK)
		return false;

	pMsg = (de_protocol_t *)pdate;
	
	tlvs_length = (uint16_t)pMsg->data_length_h << 8 | pMsg->data_length_l;
	
	index = 0;
    
    uint8_t ser_ = SER_EOF | SER_SOF;
	
	while(index + 4 < tlvs_length && !break_flag ) {
		T = pMsg->tlvs[index++];
		L = pMsg->tlvs[index] << 8 | pMsg->tlvs[index+1];
		index += 2;

		switch(T) {
			case TAG_Query:
				{
					uint8_t query_what = pMsg->tlvs[index++];
					switch(query_what) {
					case TAG_Status:
						tagmask |= TAG_MASK_Status;
                        query_more = pMsg->tlvs[index++];
						break_flag = 1;
						break;
					case TAG_Config:
						tagmask |= TAG_MASK_Config;
						break_flag = 1;
						break;
					case TAG_Control:
						tagmask |= TAG_MASK_Control;
						break_flag = 1;
						break;
                    case TAG_Logger:
                        tagmask |= TAG_MASK_Logger;
                        ser_ = SER_SOF;
                        query_more = pMsg->tlvs[index++];//dataid
                        query_type = pMsg->tlvs[index++];
                        query_lvl = pMsg->tlvs[index++];
                        query_start_ts = pMsg->tlvs[index] << 24 \
                                       | pMsg->tlvs[index+1] << 16 \
                                       | pMsg->tlvs[index+2] << 8\
                                       | pMsg->tlvs[index+3];
                        index += 4;
                        query_end_ts = pMsg->tlvs[index] << 24 \
                                       | pMsg->tlvs[index+1] << 16 \
                                       | pMsg->tlvs[index+2] << 8\
                                       | pMsg->tlvs[index+3];
                        index += 4;
						break_flag = 1;
                        break;
					default:
						break_flag = 1;
						break;
					}
				}
				break;

			case TAG_Control:
				break;

			case TAG_Config:
				ctrl_code |= CTRL_WriteAck;
				tagmask |= TAG_MASK_Config;
				result = (HandleResult *)sys_malloc(200 * sizeof(HandleResult));
				if(result == NULL) {
					return true;
				}
				protocol_handle_config(pMsg->tlvs + index,L,result,&result_cnt);
				break_flag = 1;
				index += L;
				break;
            case TAG_Logger:
                logger_set_ack(pMsg->ser,TAG_Logger);
                break;
				
			case TAG_Upgrade:
				ctrl_code |= CTRL_WriteAck;
				tagmask |= TAG_MASK_Upgrade;
				result = (HandleResult *)sys_malloc(6 * sizeof(HandleResult));
				if(result == NULL) {
					return true;
				}
                IAP_SetStatus();
				protocol_handle_upgrade(pMsg->tlvs + index,L,result,&result_cnt);
				index += L;
				break;

			case TAG_TransferData:{
                uint8_t transfer_type = pMsg->tlvs[index++];
                tagmask |= TAG_MASK_Transfer;
                CodeResult_t err = Result_MsgErr;
                switch(transfer_type) {
                    case 0x00:
                        if(L < 9) {
                            break;
                        }

                        if(de_protocol_check(pMsg->tlvs+index, L-1) != errOK) {
                            break;
                        }
                             
                        err = Result_OK;
                        CellTranferRequest(pMsg->tlvs+index,L-1);
                        break;
                    default:
                        break;
                }
                result = (HandleResult *)sys_malloc(sizeof(HandleResult));
                result[0].DataId = transfer_type;
                result[0].result = err;
                result[0].extLength = 0;
                result_cnt = 1;
                index += L;
                }
                
				break;
			default:
				break;
		}
	}
	
    if(!(pMsg->ctrl & CTRL_Response)) {
        p = (uint8_t *)sys_malloc(PROTOCOL_RX_MAX_SIZE);
        if(p == NULL) {
            goto Exit;
        }
        uint16_t send_length = de_protocol_slave_package(p,
                                                    ctrl_code,
                                                    0,
                                                    pMsg->source,
                                                    ser_ | (pMsg->ser & 0x3F),
                                                    tagmask,
                                                    result,
                                                    result_cnt);

        if(send_length > 0) {
            protocol_send_bytes(type,p,send_length);
        }
        sys_free(p);
        p = NULL;
    }

Exit:
	if(result != NULL) {
		sys_free(result);
	}
    
    return true;


}

//------------------------------------------------------
#if 1
#define PROTOCOL_TRY_TIMES  3
osMessageQId  mid_CellComm = NULL;                                 // message queue id
osMessageQDef(msgCellComm, 6, ModuleRxMsg_t);            // message queue object

void cell_init(void) {
    mid_CellComm = osMessageCreate(osMessageQ(msgCellComm), NULL); 
}

errStatus_t cell_data_update(uint8_t id,uint8_t *pdata,uint16_t length);
void cell_module_query_status_response_handle(uint8_t id,uint8_t *pdata,uint16_t length,uint8_t ser) {
	uint16_t index = 0;
    errStatus_t err = errOK;

    err = cell_data_update(id,pdata,length);

	ModuleRxMsg_t *p = sys_malloc(sizeof(ModuleRxMsg_t));
    p->err = err;
	p->tag = TAG_Status;
	p->ser = ser & 0x3F;
	osMessagePut(mid_CellComm, (uint32_t)p, 300);
}

errStatus_t cell_module_send_and_response(uint8_t *sendbytes,uint16_t length,uint8_t exp_ser,uint8_t exp_tag,uint32_t timeout) {
	errStatus_t err = errErr;
	uint32_t msg;

	uint8_t trytimes = PROTOCOL_TRY_TIMES;
    
    if(mid_CellComm == NULL) {
        cell_init();
    }


	while(trytimes--) {
		protocol_send_bytes(COMM_TYPE_485,sendbytes,length);
		while(1) {
            
            osEvent evt = osMessageGet(mid_CellComm,timeout);
            if(evt.status == osEventMessage) { 
                
                ModuleRxMsg_t *p = (ModuleRxMsg_t *)evt.value.p;
				if((p->ser & 0x3F) == (exp_ser & 0x3F) && \
					p->tag == exp_tag) {
					err = p->err;
				}

				sys_free(p);

				if(err == errOK) {
					break;
				}
            } else {
				err = errErr;
				break;
			}
		}

		if(err == errOK) {
			break;
		}
	}

	sys_free(sendbytes);

	return err;

}
#endif
errStatus_t cell_module_query_status(uint8_t id,uint8_t query_what) {

	uint8_t *p = (uint8_t *)sys_malloc(128);
	if(p == NULL) {
		return errErr;
	}

	uint8_t ser_no = protocol_ser++;

	uint16_t bytes = de_protocol_master_package(p, \
			0, \
			0x00, \
			id, \
			SER_SINGLE | (ser_no & 0x3F), \
			TAG_MASK_Query, \
			query_what, \
			NULL,\
			0,\
			NULL, \
			0);

	return cell_module_send_and_response(p,bytes,ser_no,query_what,PROTOCOL_COMMU_RESP_TIME_OUT);

}


