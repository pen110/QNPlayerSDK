//
//  QNPlayerSDkManager.h
//  QNPlayerSDK
//
//  Created by 潘欣 on 2022/9/26.
//

#import <Foundation/Foundation.h>
//PLPlayerKit 播放器核心类
#import <AVFoundation/AVFoundation.h>
#import <qplayer2_core/QPlayerContext.h>
#import <qplayer2_core/RenderView.h>
#import <qplayer2_core/QIOSCommon.h>
//请求成功
typedef void ( ^successBlock) (id _Nullable json);
// 请求失败
typedef void (^failure)(id _Nullable error);
NS_ASSUME_NONNULL_BEGIN

@protocol qnplayerSdkDelegate <NSObject>
@optional
/**
 首帧耗时回调
 @param context 当前的播放器
 @param elapsedTime 从play 开始到首帧渲染出来的总耗时 单位毫秒
*/
- (void)manager:(QPlayerContext *)context elapsedTime:(NSInteger)elapsedTime;

/**
 SEI 数据回调，且回调时机为SEI数据所在帧的时间
 @param onSEIData 当前的播放器
 @param data SEI 数据
*/
-(void)manager:(QPlayerContext *)onSEIData data:(NSData *)data;
/**
 @brief 鉴权失败回调
 @param context 当前播放器
 */
-(void)managerFailed:(QPlayerContext *)context error:(QPlayerAuthenticationErrorType)error;

/**
 @brief 鉴权成功回调
 @param context 当前播放器
 */
-(void)managerOnAuthenticationSuccess:(QPlayerContext *)context;
/**
 倍速改变回调
 @param context 当前的播放器
 @param speed 改变后的倍速
*/
-(void)managerOnSpeedChanged:(QPlayerContext *)context speed:(float)speed;

/**
 清晰度切换失败
 @param context 当前的播放器
 @param usertype 开始切换清晰度的url流的userType
 @param urlType 开始切换清晰度的url流的
 @param oldQuality 切换前的清晰度
 @param newQuality 要切到哪路清晰度
*/
-(void)managerOnQualitySwitchFailed:(QPlayerContext *)context usertype:(NSString *)usertype urlType:(QPlayerURLType)urlType oldQuality:(NSInteger)oldQuality newQuality:(NSInteger)newQuality;

/**
 状态变更回调
 @param context 当前的播放器
 @param state 播放器状态
 */
-(void)managerOnStateChange:(QPlayerContext *)context state:(QPlayerState)state;


/**
 @brief 开始buffering
 @param context 当前播放器
 */
-(void)managerOnBufferingStart:(QPlayerContext *)context;

/**
 @brief 结束buffering
 @param context 当前播放器
 */
-(void)managerOnBufferingEnd:(QPlayerContext *)context;


/**
 清晰度切换完成
 @param context 当前的播放器
 @param usertype 开始切换清晰度的url流的userType
 @param urlType 开始切换清晰度的url流的
 @param oldQuality 切换前的清晰度
 @param newQuality 要切到哪路清晰度
*/
-(void)managerOnQualitySwitchComplete:(QPlayerContext *)context usertype:(NSString *)usertype urlType:(QPlayerURLType)urlType oldQuality:(NSInteger)oldQuality newQuality:(NSInteger)newQuality;

@end



@interface QNPlayerSDkManager : NSObject

@property (nonatomic, strong) QPlayerContext *_Nullable playerContext;
@property (nonatomic, strong) RenderView *_Nullable myRenderView;

@property (nonatomic, weak)id<qnplayerSdkDelegate>delegate;
/// 管理SDK单例
+ (instancetype)shardManager;

/// 设置播放音视频的model
/// @param model 音视频的model  QStreamElement 播放地址信息
/// @param startPos 起播时间戳 毫秒
- (void)playerManagerWithMediaModel:(QMediaModel *)model startPos:(int64_t)startPos;


- (void)close;
@end

NS_ASSUME_NONNULL_END
