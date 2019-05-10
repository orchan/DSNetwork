//
//  DSNetWorkConfig.h
//  DSNetWork
//
//  Created by color on 16/6/13.
//  Copyright © 2016年 zjw7sky. All rights reserved.
//

#import <Foundation/Foundation.h>
@class DSNetWorkConfig;

NS_ASSUME_NONNULL_BEGIN
/**
 *  DSNetWorkConfig
 *  Responsible for adding the default configuration
 */
@interface DSNetWorkConfig : NSObject

+ (DSNetWorkConfig *)sharedInstance;

/**
 *  Whether it is released
 */
@property BOOL              isRelease;

/**
 *  The release url
 */
@property (copy) NSString   *releaseBaseUrl;

/**
 *  The debug url
 */
@property (copy) NSString   *debugBaseUrl;

/**
 *  The base Params
 */
@property NSDictionary      *baseParams;

/**
 *  The CDN url
 */
@property (copy)NSString    *CDNUrl;

/**
 *  network reachable
 */
@property (readonly)BOOL    isReachable;

/**
 *  The security policy
 *
 */
@property (copy)NSData    *securityPolicy;

@end

NS_ASSUME_NONNULL_END
