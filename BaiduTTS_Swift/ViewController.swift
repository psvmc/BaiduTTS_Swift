//
//  ViewController.swift
//  BaiduTTS_Swift
//
//  Created by 张剑 on 16/3/18.
//  Copyright © 2016年 张剑. All rights reserved.
//

import UIKit
import AVFoundation
class ViewController: UIViewController,BDSSpeechSynthesizerDelegate,AVSpeechSynthesizerDelegate {
    
    @IBOutlet weak var inputTextView: UITextView!
    
    var bdSSpeechSynthesizer:BDSSpeechSynthesizer!;
    override func viewDidLoad() {
        super.viewDidLoad()
        bdSSpeechSynthesizer = BDSSpeechSynthesizer.sharedInstance();
        bdSSpeechSynthesizer.setSynthesizerDelegate(self);
        bdSSpeechSynthesizer.setApiKey("VEeUVLxBmgdyxYZO2cvBXZck", withSecretKey: "9c7ea41c61b175d114187c3b12340d88");
        
        bdSSpeechSynthesizer.setSynthesizerParam(NSNumber(unsignedInt: BDS_SYNTHESIZER_TEXT_ENCODE_UTF8.rawValue), forKey: BDS_SYNTHESIZER_PARAM_TEXT_ENCODE);
        bdSSpeechSynthesizer.setSynthesizerParam(NSNumber(unsignedInt: BDS_SYNTHESIZER_SPEAKER_FEMALE.rawValue), forKey: BDS_SYNTHESIZER_PARAM_SPEAKER);
        bdSSpeechSynthesizer.setSynthesizerParam(NSNumber(unsignedInt: BDS_SYNTHESIZER_AUDIO_ENCODE_AMR_15K85.rawValue), forKey: BDS_SYNTHESIZER_PARAM_AUDIO_ENCODING);
        
        bdSSpeechSynthesizer.setSynthesizerParam(NSNumber(integer: 10), forKey: BDS_SYNTHESIZER_PARAM_VOLUME);
        bdSSpeechSynthesizer.setSynthesizerParam(NSNumber(integer: 5), forKey: BDS_SYNTHESIZER_PARAM_SPEED);
        bdSSpeechSynthesizer.setSynthesizerParam(NSNumber(integer: 5), forKey: BDS_SYNTHESIZER_PARAM_PITCH);
        bdSSpeechSynthesizer.setThreadPriority(1.0);
        let textDatfile = NSBundle.mainBundle().pathForResource("Chinese_Text", ofType: "dat");
        let speechDatfile = NSBundle.mainBundle().pathForResource("Chinese_Speech_Female", ofType: "dat");
        let tempLicenseFilePath = NSBundle.mainBundle().pathForResource("bdtts_license", ofType: "dat");
        do{
            try bdSSpeechSynthesizer.verifyDataFile(textDatfile)
        }catch{
            print("资源文件验证失败");
        }
        
        
        let ret = bdSSpeechSynthesizer.startTTSEngine(textDatfile, speechDataPath: speechDatfile, licenseFilePath: tempLicenseFilePath, withAppCode: "")
        if (ret != BDS_ERR_ENGINE_OK) {
            print("TTS启动失败")
        }
        
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
        self.view.endEditing(true);
    }
    
    @IBAction func playMsgClick(sender: AnyObject) {
        bdSSpeechSynthesizer.speak(inputTextView.text)
    }
    
    //-------------------------------------------------------------------------
    //-----------------------------百度语音TTS的代理方法--------------------------
    //-------------------------------------------------------------------------
    func synthesizerStartWorkingSentence(SynthesizeSentence: Int) {
        print("百度语音--开始合成 (sentence: \(SynthesizeSentence))")
    }
    
    func synthesizerFinishWorkingSentence(SynthesizeSentence: Int) {
        print("百度语音--结束合成 (sentence: \(SynthesizeSentence))")
    }
    
    func synthesizerErrorOccurred(error: NSError!, speaking SpeakSentence: Int, synthesizing SynthesizeSentence: Int) {
        print("百度语音--合成错误 (sentence: \(SynthesizeSentence))")
    }
    
    func synthesizerSpeechStartSentence(SpeakSentence: Int) {
        print("百度语音--开始播放 (sentence: \(SpeakSentence))")
    }
    
    func synthesizerSpeechEndSentence(SpeakSentence: Int) {
        print("百度语音--结束播放 (sentence: \(SpeakSentence))")
    }
    
    func synthesizerPaused(src: BDSAudioPlayerPauseSources) {
        print("百度语音--暂停")
    }
    
    func synthesizerResumed() {
        print("百度语音--恢复")
    }
    
    func synthesizerNewDataArrived(newData: NSData!, dataFormat fmt: BDSAudioFormat, characterCount newLength: Int32, sentenceNumber SynthesizeSentence: Int) {
        print("百度语音--接受新数据");
    }
    
    func synthesizerTextSpeakLengthChanged(newLength: Int32, sentenceNumber SpeakSentence: Int) {
        let all = inputTextView.text.characters.count;
        print("百度语音--播放进度:\(newLength)/\(all)");
        
    }
    
    
    //------------------------------华丽的分割线---------------------------------
    
    @IBAction func playMsgSysClick(sender: AnyObject) {
        let player = AVSpeechSynthesizer();
        player.delegate = self;
        let u = AVSpeechUtterance(string: inputTextView.text);
        u.voice = AVSpeechSynthesisVoice(language: "zh-TW");
        u.volume = 1.0;//音量 [0-1] Default = 1
        u.rate = 0.48;//播放速度
        
        u.pitchMultiplier = 1.0;//播放基准音调 [0.5 - 2] Default = 1
        player.speakUtterance(u);
    }
    
    //-------------------------------------------------------------------------
    //-----------------------------系统默认TTS的代理方法--------------------------
    //-------------------------------------------------------------------------
    //播放完毕
    func speechSynthesizer(synthesizer: AVSpeechSynthesizer, didFinishSpeechUtterance utterance: AVSpeechUtterance) {
        print("苹果语音--播放完毕")
    }
    
    //播放中
    func speechSynthesizer(synthesizer: AVSpeechSynthesizer, willSpeakRangeOfSpeechString characterRange: NSRange, utterance: AVSpeechUtterance) {
        let process = Double(characterRange.location) / Double(utterance.speechString.characters.count);
        print("苹果语音--播放进度\(process)")
    }
    
    //开始播放
    func speechSynthesizer(synthesizer: AVSpeechSynthesizer, didStartSpeechUtterance utterance: AVSpeechUtterance) {
        print("苹果语音--开始播放")
        
    }
    
    func speechSynthesizer(synthesizer: AVSpeechSynthesizer, didCancelSpeechUtterance utterance: AVSpeechUtterance) {
        print("苹果语音--取消播放")
        
    }
    
    
}

