//
//  PttClient.h
//  PttClient
//
//  Created by Heavyrain Lee on 2021/10/12.
//

#import <Foundation/Foundation.h>

//! Project version number for PttClient.
FOUNDATION_EXPORT double PttClientVersionNumber;

//! Project version string for PttClient.
FOUNDATION_EXPORT const unsigned char PttClientVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <WFPttClient/PublicHeader.h>

@class WFCCConversation;
@protocol WFPttDelegate <NSObject>
@optional
//某人开始在对讲会话中讲话
- (void)didConversation:(WFCCConversation *)conversation startTalkingUser:(NSString *)userId;

//某人结束在对讲会话中讲话
- (void)didConversation:(WFCCConversation *)conversation endTalkingUser:(NSString *)userId;
@end

/**
 开始讲话的通知。跟WFPttDelegate代理的didConversation:startTalkingUser:功能相同
 */
__attribute__((visibility("default"))) extern NSString *kWFPttTalkingBeginNotification;

/**
 讲话结束通知。跟WFPttDelegate代理的didConversation:endTalkingUser:功能相同
 */
__attribute__((visibility("default"))) extern NSString *kWFPttTalkingEndNotification;


/**
 对讲结束原因。
 */
typedef NS_ENUM(NSInteger, PttEndReason) {
    //用户主动释放
    EndReason_User_Release = 0,
    //讲话超时
    EndReason_Tiemout = 1,
    //被抢占
    EndReason_Take_Over = 2,
    //网络错误
    EndReason_Network_Error = 3,
    //群禁言，只有群主能讲话
    EndReason_Group_Muted = 4,
    //成员被禁言
    EndReason_Member_Muted = 5,
    //音频服务错误
    EndReason_Media_Error = 6,
    //不在会话内
    EndReason_Not_InGroup = 7,
    //用户被封禁
    EndReason_User_Disabled = 8
};

/**
 请求对讲错误码
 
 @discuss 请求对讲错误码是在请求时，达不到满足条件时返回的错误码。对讲结束原因时对讲开始后，有了某种变化，比如没有网络、被管理员禁言等导致对讲结束。
 */
#define PTT_ERROR_CODE_UNKNOWN_ERROR -1
#define PTT_ERROR_CODE_OCCUPIED -2
#define PTT_ERROR_CODE_MAX_SPEAKER -3
#define PTT_ERROR_CODE_GROUP_MUTED -4
#define PTT_ERROR_CODE_GROUP_MEMBER_MUTED -5
#define PTT_ERROR_CODE_ALREADY_INTALKING -6
#define PTT_ERROR_CODE_NOT_INGROUP -7
#define PTT_ERROR_CODE_PTT_DISABLED -8


@class WFCCMessage;
__attribute__((visibility("default"))) @interface WFPttClient : NSObject
+ (instancetype)sharedClient;

/**
 对讲代理
 */
@property(nonatomic, weak)id<WFPttDelegate> delegate;

/**
 是否开启对讲。
 */
@property(nonatomic, assign)BOOL enablePtt;


/**
 后台播放无声声音，用户避免在后台被冻结。YES/NO
 */
@property(nonatomic, strong)NSNumber *playSilent;

/**
 保存语音文件的临时目录
 */
@property(nonatomic, strong)NSString *cachePath;

/**
 开启Speaker。
 */
@property(nonatomic, assign)BOOL enableSpeaker;

/**
 单聊会话的最大讲话人数，只能是1或2。
 
 @discussion 单聊会话使用全局设置，群组会话可以单独设置最大讲话人数
 */
@property(nonatomic, assign)int singleChatMaxSpeakerNumber;
/**
 单聊会话是否保存对讲为语音消息。
 
 @discussion 单聊会话使用全局设置，群组会话可以单独设置是否保存为语音消息
 */
@property(nonatomic, assign)BOOL singleChatSaveVoiceMessage;
/**
 单聊会话的最长讲话时长，单位为秒，大于0小于等于120。
 
 @discussion 单聊会话使用全局设置，群组会话可以单独设置最长发言时长
 */
@property(nonatomic, assign)int singleChatMaxSpeakerTime;

/**
 获取对讲会话的最大发言人数。
 
 @param conversation  对讲会话
 @return 会话的最大发言人数
 @discussion 单聊会话使用全局设置，群组会话获取群组的最大发言人数。
 */
- (int)getMaxSpeakerNumber:(WFCCConversation *)conversation;

/**
 是否保存语音消息
 
 @param conversation  对讲会话
 @return 是否保存语音消息
 @discussion 单聊会话使用全局设置，群组会话获取群组是否保存语音消息。
 */
- (BOOL)isSaveVoiceMessage:(WFCCConversation *)conversation;

/**
 获取对讲会话的最大发言时长。
 
 @param conversation  对讲会话
 @return 会话的最大发言时长，单位为秒。
 @discussion 单聊会话使用全局设置，群组会话获取群组的最长发言时长。
 */
- (int)getMaxSpeakerTime:(WFCCConversation *)conversation;

/**
 设置对讲会话的最大发言人数。仅有群主能设置。仅群组会话可以设置。单聊会话使用全局设置singleChatMaxSpeakerNumber
 
 @param conversation  对讲会话
 @param number 最大发言人数
 @param successBlock 成功的回调
 @param errorBlock 失败的回调
 */
- (void)setConversation:(WFCCConversation *)conversation maxSpeakerNumber:(int)number success:(void(^)(void))successBlock error:(void(^)(int errorCode))errorBlock;

/**
 设置对讲会话的最大发言人数。仅有群主能设置。仅群组会话可以设置。单聊会话使用全局设置singleChatSaveVoiceMessage
 
 @param conversation  对讲会话
 @param save    是否设置保存语音消息
 @param successBlock 成功的回调
 @param errorBlock 失败的回调
 */
- (void)setConversation:(WFCCConversation *)conversation saveVoiceMessage:(BOOL)save success:(void(^)(void))successBlock error:(void(^)(int errorCode))errorBlock;

/**
 设置对讲会话的最大发言时长。仅有群主能设置。仅群组会话可以设置。单聊会话使用全局设置singleChatMaxSpeakerTime
 
 @param conversation  对讲会话
 @param duration 最大发言时长
 @param successBlock 成功的回调
 @param errorBlock 失败的回调
 */
- (void)setConversation:(WFCCConversation *)conversation maxSpeakerTime:(int)duration success:(void(^)(void))successBlock error:(void(^)(int errorCode))errorBlock;

/**
 请求对讲会话中发言
 
 @param conversation           对讲会话
 @param startBlock         请求成功的回调
 @param failureBlock    请求失败的回调
 @param endBlock              对讲结束的回调
 */
- (void)requestTalk:(WFCCConversation *)conversation startTalking:(void (^)(void))startBlock requestFailure:(void (^)(int errorCode))failureBlock talkingEnd:(void (^)(PttEndReason reason))endBlock;

/**
 结束发言
 
 @param conversation           对讲会话
 */
- (void)releaseTalking:(WFCCConversation *)conversation;

/**
 获取当前正在讲话会话
 
 @return 返回当前正在讲话会话。
 */
- (WFCCConversation *)getTalkingConversation;

/**
 获取当前讲话开始时间。
 
 @return 当前讲话开始时间，0为未讲话。
 */
- (int64_t)getTalkingStartTime;

/**
 获取会话内讲话者的Id
 
 @param conversation           对讲会话
 @return 会话内讲话者<用户ID，起始时间>字典
 */
- (NSDictionary<NSString *, NSNumber *> *)getTalkingMember:(WFCCConversation *)conversation;
@end
