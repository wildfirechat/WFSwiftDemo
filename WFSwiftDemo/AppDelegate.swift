//
//  AppDelegate.swift
//  WFSwiftDemo
//
//  Created by dali on 2019/9/20.
//  Copyright © 2019 WF Chat. All rights reserved.
//

import UIKit


@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, ConnectionStatusDelegate, WFAVEngineDelegate {
    func didReceiveCall(_ session: WFAVCallSession!) {
//        WFCUVideoViewController *videoVC = [[WFCUVideoViewController alloc] initWithSession:session];
//        [[WFAVEngineKit sharedEngineKit] presentViewController:videoVC];
        DispatchQueue.main.async(execute: {
            let videoVC = WFCUVideoViewController();
            WFAVEngineKit.shared()?.present(videoVC);
        })
    }
    
    func shouldStartRing(_ isIncoming: Bool) {
        //start call ring.
    }
    
    func shouldStopRing() {
        //stop call ring.
    }
    
    func onConnectionStatusChanged(_ status: ConnectionStatus) {
//        dispatch_async(dispatch_get_main_queue(), ^{
//            if (status == kConnectionStatusRejected || status == kConnectionStatusTokenIncorrect || status == kConnectionStatusSecretKeyMismatch) {
//                [[WFCCNetworkService sharedInstance] disconnect:YES];
//            } else if (status == kConnectionStatusLogout) {
//                UIViewController *loginVC = [[WFCLoginViewController alloc] init];
//                self.window.rootViewController = loginVC;
//            }
//            });
        //if connect status is reject / token incorrect / key mismatch. should logout.
    }
    

    var window: UIWindow?


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        WFCCNetworkService.sharedInstance()?.connectionStatusDelegate = self as ConnectionStatusDelegate;
        WFCCNetworkService.sharedInstance()?.setServerAddress(IM_HOST);
        
        WFAVEngineKit.shared()?.addIceServer("turn:turn.liyufan.win:3478", userName: "wfchat", password: "wfchat");
        WFAVEngineKit.shared()?.setVideoProfile(WFAVVideoProfile.profile480P, swapWidthHeight: true);
        WFAVEngineKit.shared()?.delegate = self;
        
        let bar = UINavigationBar.appearance();
        bar.barTintColor = UIColor.init(displayP3Red: 0.1, green: 0.27, blue: 0.9, alpha: 0.9);
        
        bar.tintColor = UIColor.white;
        
        
        return true
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}

