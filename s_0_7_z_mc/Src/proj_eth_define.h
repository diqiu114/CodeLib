/***********************************************************
* @copyright  (C) COPYRIGHT DANFINSWE
* @author      DFS Technology Department
*
* @brief      以太网模块用户定义

***********************************************************/
#ifndef _PROJ_ETH_DEFINE_H_
#define _PROJ_ETH_DEFINE_H_
//使用单网口模块
#define ETH_SINGLE_MODULE (1)
//使用通用的以太网模块
#define USE_ETH_GENERAL   (0)
//设置mac地址高字节
#define ETH_NEED_SET_MAC_HIG (0)
//设置mac地址中字节
#define ETH_NEED_SET_MAC_MID (0)
//设置mac地址低字节
#define ETH_NEED_SET_MAC_MIN (0)
//使用dns
#define ETH_NEED_SET_DNS (0)
//使用TTDB
#define ETH_NEED_SET_TTDB (0)
//启用组播地址接收
#define ETH_NEED_SET_RECV_GROUP (1)
//启用主连接
#define ETH_NEED_SET_MASTR_BROADCAST (1)
//主连接启用SDT功能
#define ETH_NEED_SET_MASTER_SDT (0)
//单播启用SDT功能
#define ETH_NEED_SET_UPGRADE_SDT (0)
//启用唯一标识符
#define ETH_NEED_SET_CONSISTID (0)
//需要设置commid
#define ETH_NEED_SET_COMMID (1)
//需要用户自定义协议
#define ETH_NEED_SET_USE_PROTO (1)
//使用tcp透传
#define ETH_TCP_PASSTHROUGH (0)
//使用udp透传
#define ETH_UDP_PASSTHROUGH (0)
//使用单播trdp格式
#define ETH_UDP_TRDP (0)
//使用发送数据过程帧
#define ETH_USE_PD (1)
//使用发送消息数据帧
#define ETH_USE_MD (0)
//组播个数
#define MASTER_BROADCAST_COUNT (1)
//接收commid个数
#define COMMID_COUNT (2)
//自由单播个数
#define UPGRADE_COUNT (1)
//接收SMI个数
#define RECV_SMI_COUNT (0)
//使用最新的以太网模块
#define USE_NEW_ETH_BOARD  (1)
#endif
