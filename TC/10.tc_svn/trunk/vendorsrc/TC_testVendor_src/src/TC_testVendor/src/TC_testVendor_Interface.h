/////////////////////////////////////////////////////////////////////////////////////////////////
/// 	COPYRIGHT NOTICE
/// 	Copyright (c) 2017, 北京天创征腾信息科技有限公司（版权声明）
/// 	All rights reserved.
///
/// @file		TC_testVendor_Interface.h
/// @brief		testVendor工程入口/接口文件。
///
/// @author	
/// @date		2019年7月
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TC_TESTVENDOR_INTERFACE_H__
#define __TC_TESTVENDOR_INTERFACE_H__


#ifdef __cplusplus
extern "C"
{
#endif

/**
* @brief 从主要供测试使用
* @param inInfo	[in]输入参数.
* @param outInfo	[out]输出参数.
* @return
*	0	成功
*	其他	失败
*/
void TC_testVendor_Interface(char *inInfo, char *outInfo);

#ifdef __cplusplus
}
#endif

#endif

