//
//  ViewController.swift
//  WFSwiftDemo
//
//  Created by dali on 2019/9/20.
//  Copyright © 2019 WF Chat. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var phoneNumberField: UITextField!
    
    @IBOutlet weak var superCodeField: UITextField!
    //    @IBAction func onConnect(_ sender: Any) {
//        WFCCNetworkService.sharedInstance()?.connect("1p3010LL", token: tokenLabel.text);
////
////        let sb = UIStoryboard(name:"Main",bundle: Bundle.main);
////        let mainvc = sb.instantiateViewController(withIdentifier: "main_table_id");
////        UIApplication.shared.delegate?.window?!.rootViewController = mainvc;
//    }
    
    @IBAction func onLoginBtn(_ sender: Any) {
        if self.phoneNumberField.text == nil || self.superCodeField == nil {
            print("invalid phone number or super code");
            return;
        }
        
        let manager = AFHTTPSessionManager();
        manager.requestSerializer = AFJSONRequestSerializer();
        let paramDict: Dictionary<String, String> = ["mobile" : self.phoneNumberField.text!, "code":self.superCodeField.text!, "clientId":WFCCNetworkService.sharedInstance()?.getClientId() ?? ""];
        
        manager.post(DEMO_APP_URL + "/login", parameters: paramDict, progress: nil, success: { (operation: URLSessionDataTask!, responseObject: Any!) -> Void in
            let dict: NSDictionary = responseObject as! NSDictionary;
            if dict["code"] as! Int64 == 0 {
                print("hello");
                let result = dict["result"] as! NSDictionary;
                let userId = result["userId"] as! NSString;
                let token = result["token"] as! NSString;
                
                DispatchQueue.main.async(execute: {
                    WFCCNetworkService.sharedInstance()?.connect(userId as String, token: token as String);
                    
                    let sb = UIStoryboard(name:"Main",bundle: Bundle.main);
                    let mainvc = sb.instantiateViewController(withIdentifier: "main_table_id");
                    UIApplication.shared.delegate?.window?!.rootViewController = mainvc;
                })
            }
        }) { (operation: URLSessionDataTask!, error: Error!) -> Void in
            print(error ?? "")
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
    }


}

