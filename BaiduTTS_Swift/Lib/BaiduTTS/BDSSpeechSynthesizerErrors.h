#ifndef BDSSpeechSynthesizer_BDSSpeechSynthesizerErrors_h
#define BDSSpeechSynthesizer_BDSSpeechSynthesizerErrors_h

FOUNDATION_EXPORT NSString * const BDTTS_BDS_SYNTHESIZER_ERROR_DOMAIN;
FOUNDATION_EXPORT NSString * const BDTTS_BDS_PLAYER_ERROR_DOMAIN;
FOUNDATION_EXPORT NSString * const BDTTS_BDS_NETWORK_ERROR_DOMAIN;
FOUNDATION_EXPORT NSString * const BDTTS_BDS_SERVER_RETURN_ERROR_DOMAIN;
FOUNDATION_EXPORT NSString * const BDTTS_BDS_EMBEDDED_ENGINE_ERROR_DOMAIN;

typedef enum BDSStartSynthesisError
{
    // Shared errors
    BDS_START_SYNTHESIS_OK = 0,                     /* No errors */
    BDS_START_SYNTHESIS_SYNTHESIZER_UNINITIALIZED,  /* Engine is not initialized */
    BDS_START_SYNTHESIS_TEXT_EMPTY,                 /* Synthesis text is empty */
    BDS_START_SYNTHESIS_TEXT_TOO_LONG,              /* Synthesis text is too long */
    BDS_START_SYNTHESIS_ENGINE_BUSY,               /* Already synthesising, cancel first or wait */
    BDS_START_SYNTHESIS_MALLOC_ERROR,                /* failed to allocate resources */
    BDS_START_SYNTHESIS_NO_NETWORK,                 /* No internet connectivity */
    BDS_START_SYNTHESIS_NO_VERIFY_INFO,             /* No product id or api keys set */
    /* Offline TTS engine wasn't loaded */
    BDS_START_SYNTHESIS_OFFLINE_ENGINE_NOT_LOADED
}BDSStartSynthesisError;

/*
 * Error codes for errors received through BDSSpeechSynthesizerDelegate's
 * synthesizerErrorOccurred -interface
 */
typedef enum BDSSynthesisError
{
    /* General usage */
    BDS_UNKNOWN_ERROR = 30001,  /* Unhandled error, see error description for details */
    /* Playback errors */
    BDS_PLAYER_FAILED_GET_STREAM_PROPERTIES = 25001,
    BDS_PLAYER_FAILED_OPEN_DEVICE,
    BDS_PLAYER_FAILED_OPEN_STREAM,
    BDS_PLAYER_ALLOC_FAIL,
    BDS_PLAYER_BAD_STREAM,
    BDS_PLAYER_START_PLAYBACK_FAILED,
    // Online TTS Errors
    /* Online TTS errors */
    BDS_ONLINE_TTS_CONNECT_ERROR = 2001,
    BDS_ONLINE_TTS_RESPONSE_PARSE_ERROR = 2002,
    BDS_ONLINE_TTS_PARAM_ERROR = 4501,
    /** 文本编码不支持 */
    BDS_ONLINE_TTS_TEXT_ENCODE_NOT_SUPPORTED = 4502,
    /** 认证错误 */
    BDS_ONLINE_TTS_VERIFY_ERROR = 4503,
    /** 获取access token失败 */
    BDS_ONLINE_TTS_GET_ACCESS_TOKEN_FAILED = 4001,
    
    // Oflfine TTS errors
    BDS_ETTS_ERR_PARTIAL_SYNTH = 10001,
    BDS_ETTS_ERR_CONFIG,
    BDS_ETTS_ERR_RESOURCE,
    BDS_ETTS_ERR_HANDLE,
    BDS_ETTS_ERR_PARMAM,
    BDS_ETTS_ERR_MEMORY,
    BDS_ETTS_ERR_TOO_MANY_TEXT,
    BDS_ETTS_ERR_RUN_TIME,
    BDS_ETTS_ERR_NO_TEXT,
    BDS_ETTS_ERR_LICENSE,
    
}BDSSynthesisError;

typedef enum BDSErrEngine{
    BDS_ERR_ENGINE_OK = 0,
    BDS_ERR_ENGINE_PARTIAL_SYNTH = 10001,
    BDS_ERR_ENGINE_CONFIG,
    BDS_ERR_ENGINE_RESOURCE,
    BDS_ERR_ENGINE_HANDLE,
    BDS_ERR_ENGINE_PARMAM,
    BDS_ERR_ENGINE_MEMORY,
    BDS_ERR_ENGINE_MANY_TEXT,
    BDS_ERR_ENGINE_RUN_TIME,
    BDS_ERR_ENGINE_NO_TEXT,
    BDS_ERR_ENGINE_LICENSE,
    BDS_ERR_ENGINE_MALLOC,
    BDS_ERR_ENGINE_ENGINE_NOT_INIT,
    BDS_ERR_ENGINE_SESSION_NOT_INIT,
    BDS_ERR_ENGINE_GET_LICENSE,
    BDS_ERR_ENGINE_LICENSE_EXPIRED,
    BDS_ERR_ENGINE_VERIFY_LICENSE,
    BDS_ERR_ENGINE_INVALID_PARAM,
    BDS_ERR_ENGINE_DATA_FILE_NOT_EXIST,
    BDS_ERR_ENGINE_VERIFY_DATA_FILE,
    BDS_ERR_ENGINE_GET_DATA_FILE_PARAM,
    BDS_ERR_ENGINE_ENCODE_TEXT,
    BDS_ERR_ENGINE_INIT_FAIL,
    BDS_ERR_ENGINE_IN_USE,
    BDS_ERR_ENGINE_BAD_INIT_STATE,
    BDS_ERR_ENGINE_UNKNOWN_ERROR
}BDSErrEngine;

// 播放器状态
typedef enum BDSSynthesizerStatus {
    /*
     * Failed to initialize SDK
     */
    BDS_SYNTHESIZER_STATUS_NONE = 0,
    
    /*
     * SDK ready for use
     */
    BDS_SYNTHESIZER_STATUS_IDLE,
    
    /*
     * SDK is synthesizing/speaking
     */
    BDS_SYNTHESIZER_STATUS_WORKING,
    
    /*
     * Synthesis (and speech) is paused
     */
    BDS_SYNTHESIZER_STATUS_PAUSED,
    
    /*
     * SDK has encountered error during previous synthesis.
     * SDK is ready for start new synthesis
     */
    BDS_SYNTHESIZER_STATUS_ERROR,
    
    /*
     * SDK was cancelled by user during previous synthesis.
     * SDK is ready for start new synthesis
     */
    BDS_SYNTHESIZER_STATUS_CANCELLED
}BDSSynthesizerStatus;

#endif
