//
//  ViewController.swift
//  BaiduTTS_Swift
//
//  Created by 张剑 on 16/3/18.
//  Copyright © 2016年 张剑. All rights reserved.
//

import UIKit

class ViewController: UIViewController,BDSSpeechSynthesizerDelegate {

    override func viewDidLoad() {
        super.viewDidLoad()
        let bdSSpeechSynthesizer = BDSSpeechSynthesizer.sharedInstance();
        bdSSpeechSynthesizer.setSynthesizerDelegate(self);
        bdSSpeechSynthesizer.setApiKey("VEeUVLxBmgdyxYZO2cvBXZck", withSecretKey: "9c7ea41c61b175d114187c3b12340d88");
        bdSSpeechSynthesizer.setSynthesizerParam(BDS_SYNTHESIZER_TEXT_ENCODE_UTF8 as! AnyObject, forKey: BDS_SYNTHESIZER_PARAM_TEXT_ENCODE);
        bdSSpeechSynthesizer.setSynthesizerParam(BDS_SYNTHESIZER_SPEAKER_FEMALE as! AnyObject, forKey: BDS_SYNTHESIZER_PARAM_SPEAKER);
        bdSSpeechSynthesizer.setSynthesizerParam(BDS_SYNTHESIZER_AUDIO_ENCODE_AMR_15K85 as! AnyObject, forKey: BDS_SYNTHESIZER_PARAM_AUDIO_ENCODING);
        bdSSpeechSynthesizer.setSynthesizerParam(5 as AnyObject, forKey: BDS_SYNTHESIZER_PARAM_VOLUME);
        bdSSpeechSynthesizer.setSynthesizerParam(5 as AnyObject, forKey: BDS_SYNTHESIZER_PARAM_SPEED);
        bdSSpeechSynthesizer.setSynthesizerParam(5 as AnyObject, forKey: BDS_SYNTHESIZER_PARAM_PITCH);
        bdSSpeechSynthesizer.setThreadPriority(1.0);
        let textDatfile = NSBundle.mainBundle().pathForResource("Chinese_Text", ofType: "dat");
        let speechDatfile = NSBundle.mainBundle().pathForResource("Chinese_Speech_Female", ofType: "dat");
        let tempLicenseFilePath = NSBundle.mainBundle().pathForResource("bdtts_license", ofType: "dat");
        do{
            try bdSSpeechSynthesizer.verifyDataFile(textDatfile);
            print("百度TTS  数据文件验证成功")
        }catch{
            print(error);
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


}

