//
//  BDSMixedModeSynthesizer.h
//  BDSSpeechSynthesizer
//
//  Created by lappi on 4/14/15.
//  Copyright (c) 2015 百度. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BDSSpeechSynthesizerDelegate.h"
#import "BDSSynthesizerLogLevel.h"
#import "BDSSpeechSynthesizerParams.h"
#import "BDSSpeechSynthesizerErrors.h"

@interface BDSSpeechSynthesizer : NSObject

/** TTS播报的category */
@property (nonatomic, copy) NSString *audioSessionCategory;

#pragma mark - Init/Uninit
/**
 * @brief 获取合成器唯一实例
 *
 * @return 返回合成器唯一实例
 */
+ (BDSSpeechSynthesizer*)sharedInstance;

/**
 * @brief 释放合成器唯一实例
 *
 *
 */
+ (void)releaseInstance;

#pragma mark - Configurations

/**
 * @brief 设置合成器代理
 *
 * @param delegate 代理对象，负责处理合成器各类事件
 *
 * @return 识别器对象
 */
- (void)setSynthesizerDelegate: (id<BDSSpeechSynthesizerDelegate>)delegate;

/*
 * @brief set synthesizer param
 * @param param Parameter object. Refer to enum BDSSynthesizerParamKey for object types and valid values for different keys.
 * @param key Key for parameter.
 *
 */
-(BDSSynthesizerParamError)setSynthesizerParam:(id)param forKey:(BDSSynthesizerParamKey)key;

/*
 * @brief get current value of parameter
 * @param key Key for parameter.
 * @param err If not nil, is set to BDS_SYNTHESIZER_PARAM_ERR_OK on success or error code on failure.
 * @return parameter object or nil. Refer to enum BDSSynthesizerParamKey for object types for different keys.
 */
-(id)getSynthesizerParamforKey:(BDSSynthesizerParamKey)key error:(BDSSynthesizerParamError*)err;

/**
 * @brief 设置认证信息
 *
 * @param apiKey 在百度开发者中心注册应用获得
 * @param secretKey 在百度开发者中心注册应用获得
 */
- (void)setApiKey:(NSString *)apiKey withSecretKey:(NSString *)secretKey;

/**
 * -(BDSSynthesizerParamError)setCallbackQueue:(dispatch_queue_t)callbackQueue;
 * @brief YOU CAN IGNORE THIS IF YOU ARE GOING TO USE THIS SDK DIRECTLY FROM UI THREAD.
 *        Sets the queue that should be used for making callbacks to BDSSpeechSynthesizerDelegate.
 *        By default UI queue is used.
 *
 * @param callbackQueue A serial queue for making callbacks. (Using concurrent queue may result in
 *                      unexpected behaviour in some cases)
 *
 * @sample [[BDSSpeechSynthesizer sharedInstance] setCallbackQueue:dispatch_queue_create("MY_CALLBACK", DISPATCH_QUEUE_SERIAL)];
 *
 * @return BDS_SYNTHESIZER_PARAM_ERR_OK On success.
 *         BDS_SYNTHESIZER_PARAM_ERR_SDK_BUSY If synthesis is running.
 *         BDS_SYNTHESIZER_PARAM_ERR_SDK_UNINIT If SDK is not properly initialized.
 *
 */
-(BDSSynthesizerParamError)setCallbackQueue:(dispatch_queue_t)callbackQueue;

/**
 * -(dispatch_queue_t)getCurrentCallbackQueue
 * @brief YOU CAN IGNORE THIS IF YOU ARE GOING TO USE THIS SDK DIRECTLY FROM UI THREAD.
 *        Gets current dispatch queue used for callbacks.
 *        It is recommended to use returned queue to call other interface methods of this SDK.
 *        Calling from other queues/thread may result in unexpected behaviour in some cases.
 *        By default this is UI queue.
 */
-(dispatch_queue_t)getCurrentCallbackQueue;
#pragma mark - Load Embedded TTS engine

/**
 * @brief 设置合成线程优先级，请在startTTSEngine:licenseFilePath:withAppCode:前调用
 *
 * @param priority
 *            线程优先级，取值范围[0.0, 1.0]，默认0.5
 */
- (void)setThreadPriority:(double)priority;

/**
 * @brief 启动合成引擎
 *
 * @param textDatFilePath 文本分析数据文件路径
 * @param speechDataPath 声学模型数据文件路径
 * @param licenseFilePath 授权文件路径，如果没有本地授权可传入nil
 * @param appCode 用户持有的授权app code
 *
 * @return 错误码
 */
- (BDSErrEngine)startTTSEngine: (NSString*)textDatFilePath
                speechDataPath: (NSString*)speechDatFilePath
               licenseFilePath: (NSString*)licenseFilePath
                   withAppCode: (NSString*)appCode;

-(BDSErrEngine)loadEnglishData: (NSString*)textDataPath
                    speechData: (NSString*)speechDataPath;

/**
 * @brief 重新加载文本分析数据文件或者声学模型数据文件
 *
 * @param datFilePath: 数据文件路径
 *
 * @return 错误码
 */
- (BDSErrEngine)reinitTTSData: (NSString*)datFilePath;

/**
 * @brief 加载定制库，在startTTSEngine:licenseFilePath:withAppCode:消息被调用后，调用此函数
 *
 * @param datFilePath 定制库路径
 *
 * @return 错误码
 */
- (BDSErrEngine)loadDomainData:(NSString*)datFilePath;

/**
 * @brief 卸载定制库
 *
 * @return 错误码
 */
- (BDSErrEngine)unloadDomainData;

/**
 * @brief 验证音库文件的有效性
 * @param datFilePath data文件路径
 * @param err 如果验证失败, 返回错误信息
 *
 * @return 验证成功YES，失败NO
 */
- (BOOL)verifyDataFile: (NSString*) datFilePath error:(NSError**)err;

/**
 * @brief 获取音库文件相关参数
 * @param datFilePath data文件路径
 * @param paramType 参数类型
 * @param paramValue 传出对应参数的值
 * @param err 如果失败, 返回错误信息
 *
 * @return 成功YES，失败NO
 */
- (BOOL)getDataFileParam: (NSString*)datFilePath
                    type: (TTSDataParam)paramType
                   value: (NSString**)paramValue
                   error: (NSError**)err;

#pragma mark - Synthesis interfaces
/**
 * @brief 开始文本合成但不朗读，开发者需要通过BDSSpeechSynthesizerDelegate的
 *        synthesizerNewDataArrived:data:isLastData:sentenceNumber:方法传回的数据自行播放
 *        The sentence number passed to callbacks will be 0
 *
 * @param text 需要语音合成的文本
 */
- (BDSStartSynthesisError)synthesize:(NSString *)text;

/**
 * @brief 开始文本合成但不朗读，开发者需要通过BDSSpeechSynthesizerDelegate的
 *        synthesizerNewDataArrived:data:isLastData:sentenceNumber:方法传回的数据自行播放
 *
 * @param strings 需要语音合成的文本
 *        The sentence number passed to callbacks indicates the index of string in this array.
 */
-(BDSStartSynthesisError)batchSynthesize:(NSArray *)strings;

/**
 * @brief 开始文本合成并朗读
 *        The sentence number passed to callbacks will be 0
 *
 * @param text 需要朗读的文本
 */
- (BDSStartSynthesisError)speak:(NSString *)text;

/**
 * @brief 开始文本合成并朗读
 *
 * @param strings 需要朗读的文本
 *        The sentence number passed to callbacks indicates the index of string in this array.
 */
- (BDSStartSynthesisError)batchSpeak:(NSArray*)strings;

/**
 * @brief Start new speak task with sentences or add more sentences to current playback
 *
 * @param sentences Array of sentences to be added.
 * @param generatedIDs Empty mutable array, on return contains array of NSNumber objects indicating
 *                     IDs for passed sentences. If passed array is not empty, generated IDs will be
 *                     added to the end of the array.
 *                     The returned IDs corresbond to the SynthesizeSentence- and SpeakSentence-
 *                     parameters passed to BDSSpeechSynthesizerDelegate's callback methods.
 *
 * @note               The ID is a running number which is initially 0 and increases by one for each sentence
 *                     passed here. The number gets reset to 0 when old synthesize-, batchSynthesize-, speak-
 *                     and batchSpeak-interfaces are used. This is to maintain backward compatibility of the SDK.
 *
 * @return Error code. If != BDS_START_SYNTHESIS_OK, no sentences have been added and generatedIDs is unchanged.
 */
- (BDSStartSynthesisError)queueSpeakSentences:(NSArray*)sentences sentenceIDs:(NSMutableArray*)generatedIDs;

/**
 * @brief Start new synthesis task with sentences or add more sentences to current synthesis
 *
 * @param sentences Array of sentences to be added.
 * @param generatedIDs Empty mutable array, on return contains array of NSNumber objects indicating
 *                     IDs for passed sentences. If passed array is not empty, generated IDs will be
 *                     added to the end of the array.
 *                     The returned IDs corresbond to the SynthesizeSentence- and SpeakSentence-
 *                     parameters passed to BDSSpeechSynthesizerDelegate's callback methods.
 *
 * @note               The ID is a running number which is initially 0 and increases by one for each sentence
 *                     passed here. The number gets reset to 0 when old synthesize-, batchSynthesize-, speak-
 *                     and batchSpeak-interfaces are used. This is to maintain backward compatibility of the SDK.
 *
 * @return Error code. If != BDS_START_SYNTHESIS_OK, no sentences have been added and generatedIDs is unchanged.
 */
- (BDSStartSynthesisError)queueSynthesizeSentences:(NSArray*)sentences sentenceIDs:(NSMutableArray*)generatedIDs;

/**
 * @brief 取消本次合成并停止朗读
 */
- (void)cancel;

/**
 * @brief 暂停文本合成并朗读
 */
- (BDSSynthesizerStatus)pause;

/**
 * @brief 继续文本合成并朗读
 */
- (BDSSynthesizerStatus)resume;

/**
 * @brief 获取合成器状态
 *
 */
- (BDSSynthesizerStatus)synthesizerStatus;

/**
 * @brief return total count of sentences queued for playback
 * the count also includes sentences that haven't been synthesized yet.
 */
-(NSInteger)RemainingPlaybackSentenceCount;

/**
 * @brief return total count of sentences that are still to be synthesized.
 */
-(NSInteger)RemainingSynthesizeSentenceCount;

#pragma mark - Playback control

/**
 * @brief 设置播放器音量
 *
 * @param volume 音量值
 *
 */
- (void)setPlayerVolume:(float)volume;

/**
 * @brief 设置AudioSessionCategory类型
 *
 * @param category AudioSessionCategory类型，取值参见AVAudioSession Class Reference
 * Note: BDS_SYNTHESIZER_PARAM_ENABLE_AVSESSION_MGMT must be set to YES for this to have effect.
 *
 * Default: AVAudioSessionCategoryPlayback
 */
- (void)setAudioSessionCategory:(NSString *)category;

#pragma mark - Debugging
/**
 * @brief 获取错误码对应的描述
 *
 * @param errorCode 错误码
 *
 * @return 错误描述信息
 */
- (NSString *)errorDescriptionForCode:(NSInteger)errorCode;

/**
 * @brief 设置日志级别
 *
 * @param logLevel 日志级别
 */
+ (void)setLogLevel:(BDSLogLevel)logLevel;

/**
 * @brief 获取当前日志级别
 *
 * @return 日志级别
 */
+ (BDSLogLevel)logLevel;

/**
 * @brief 获取库版本号
 *
 * @return 版本号
 */
+ (NSString *)version;

/**
 * @brief 获取引擎版本信息
 *
 */
+ (NSInteger)engineVersion;

@end