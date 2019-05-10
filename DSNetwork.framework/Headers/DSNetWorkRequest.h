//
//  DSNetWorkRequest.h
//  DSNetWork
//
//  Created by color on 16/6/12.
//  Copyright © 2016年 zjw7sky. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>

@class DSNetWorkRequest;

NS_ASSUME_NONNULL_BEGIN

/// Request way
typedef NS_ENUM(NSInteger , DSRequestWay) {
    DSRequestWayGet             = 0,
    DSRequestWayPost,
    DSRequestWayHead,
    DSRequestWayPut,
    DSRequestWayDelete,
    DSRequestWayPatch,
};

/// Serializer type
typedef NS_ENUM(NSInteger , DSSerializerType) {
    DSSerializerTypeHTTP        = 0,
    DSSerializerTypeJSON,
};

// Network error code
typedef NS_ENUM(NSInteger , DSNetworkErrorCode) {
    DSNetworkErrorCodeNoError   = 0,
    DSNetworkErrorCodeNoNetwork = 1,
    DSNetworkErrorCodeTimeout   = 2,
    DSNetworkErrorCodeInValid   = 3,
    DSNetworkErrorCodeUndefined = 99,
};


/**
 *  DSNetworkDelegate
 */
@protocol DSNetworkDelegate <NSObject>

@optional

/**
 *  The callback when the request is completed
 *
 *  @param request The request
 */
- (void)ds_requestCompletion:(DSNetWorkRequest *)request;

@end

/**
 *  The block of the upload data
 *
 *  @param formData The upload data
 */
typedef void (^DSConstructingBlock)(id<AFMultipartFormData> formData);

/**
 *  The block of the progress
 *
 *  @param progress The progress
 */
typedef void (^DSProgressBlock)(NSProgress * progress);

/**
 *  The callback when the request is completed
 *
 *  @param request The request
 */
typedef void (^DSRequestCompletion)(DSNetWorkRequest *request);


/**
 *  The adapter
 */
@protocol DSNetworkAdapter <NSObject>

@optional

/**
 *  When you need some operating parameters (such as encryption, encoding), can realize the agent
 *
 *  @param request   The request
 *  @param reqParams The original parameters
 *
 *  @return already adapted parameters
 */
- (id)ds_request:(DSNetWorkRequest *)request adaptRequestParams:(id)reqParams;

/**
 *  When you need the response data for some operation (such as the decryption and decompression) you can achieve this agent
 *
 *  @param request The request
 *  @param resData The original response data
 *
 *  @return already adapted response data
 */
- (id)ds_request:(DSNetWorkRequest *)request adaptResponseData:(id)resData;

@end


/**
 *  The interceptor
 *  When you are on a request, or need to do some operation when the response is received (such as load HUD), can realize the agent
 */
@protocol DSNetworkInterceptor <NSObject>

@optional

- (void)ds_requestWillStart:(DSNetWorkRequest *)request;
- (void)ds_requestWillStop:(DSNetWorkRequest *)request;
- (void)ds_requestDidStop:(DSNetWorkRequest *)request;

@end

#pragma mark - Base

/**
 *  DSNetWorkRequest
 */
@interface DSNetWorkRequest : NSObject

/**
 *  The current request session task,readonly
 */
@property (readonly,nullable) NSURLSessionTask *ds_task;

/**
 *  The response data,readonly
 */
@property (readonly,nullable) id ds_responseObject;

/**
 *  Response error,readonly
 */
@property (readonly,nullable) NSError *ds_error;

/**
 *  Response error code,readonly
 */
@property (readonly) DSNetworkErrorCode ds_errorCode;

/**
 *  Whether the data is from the cache,readonly
 */
@property (readonly) BOOL ds_dataFromCache;

/**
 *  The upload data block
 */
@property (nullable, copy) DSConstructingBlock ds_constructingBlock;

/**
 *  The progress block
 */
@property (nullable, copy) DSProgressBlock ds_progressBlock;//progressblock

/**
 *  The completion block
 */
@property (nullable, copy) DSRequestCompletion ds_completion;//block

/**
 *  The delegate
 */
@property (nullable, weak) id<DSNetworkDelegate> ds_delegate;

/**
 *  The interceptors
 */
@property (nullable) NSArray *ds_interceptors;

/**
 *  The adapter
 */
@property (weak) id<DSNetworkAdapter> ds_adapter;

/**
 *  Request resume
 */
- (void)ds_resume;

/**
 *  Request suspend
 */
- (void)ds_suspend;

/**
 *  Request cancel
 */
- (void)ds_cancel;

@end


#pragma mark - Inheritance

/**
 *  DSNetWorkRequest
 *  A subclass can inherit these methods to update the content
 */
@interface DSNetWorkRequest (Inheritance)

/**
 *  The user name server authentication
 *
 *  @return user name
 */
- (NSString *)ds_username;

/**
 *  The password server authentication
 *
 *  @return password
 */
- (NSString *)ds_password;

/**
 *  Whether to use the CDN
 *
 *  @return Whether to use the CDN. Default: NO
 */
- (BOOL)ds_useCDN;

/**
 *  The CDN url
 *
 *  @return The CDN url. Returns not nil will ignore CDNUrl by default
 */
- (NSString *)ds_CDNUrl;

/**
 *  The base url
 *
 *  @return The base url. Returns not nil will ignore baseUrl by default
 */
- (NSString *)ds_baseUrl;//返回不为空会忽略  config的baseUrl

/**
 *  The additional address
 *
 *  @return The additional address. eg: /userinfoDatas/info
 */
- (NSString *)ds_address;

/**
 *  The parameters
 *
 *  @return The parameters. eg: NSDictionary,NSArray
 */
- (id)ds_params;

/**
 *  The all parameters
 *
 *  @return The all parameters. Returns not nil will ignore baseParams by default
 */
- (id)ds_allParams;

/**
 *  The request timeout
 *
 *  @return The request timeout. Default: 30 seconds
 */
- (NSTimeInterval)ds_timeout;

/**
 *  The request way
 *
 *  @return The request way. Default: Get
 */
- (DSRequestWay)ds_requestWay;

/**
 *  The request serializer type
 *
 *  @return The request serializer type. Default: HTTP
 */
- (DSSerializerType)ds_requestSerializerType;

/**
 *  The response serializer type
 *
 *  @return The response serializer type. Default: HTTP
 */
- (DSSerializerType)ds_responseSerializerType;

/**
 *  The HTTP header fields
 *
 *  @return The HTTP header fields
 */
- (NSDictionary<NSString *, NSString *> *)ds_HTTPHeaderFields;

/**
 *  The cache survival time
 *
 *  @return The cache survival time. Default: -1
 */
- (NSTimeInterval)ds_cacheSurviveTime;//缓存存活时间

/**
 *  The file breakpoint continuingly path
 *
 *  @return The file breakpoint continuingly path
 */
- (NSString *)ds_resumableDownloadPath;

/**
 *  The custom request
 *
 *  @return The custom request. Returns not nil will ignore url,params,way,serializerType,
 */
- (NSURLRequest *)ds_customUrlRequest;

/**
 *  The response data validation json format
 *
 *  @return The response data validation json format
 */
- (id)ds_responseDataValidator;

@end


NS_ASSUME_NONNULL_END
