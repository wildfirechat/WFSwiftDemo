//
//  MainTabViewController.swift
//  WFSwiftDemo
//
//  Created by dali on 2019/9/21.
//  Copyright © 2019 WF Chat. All rights reserved.
//

import UIKit

class MainTabViewController: UITabBarController {

    override func viewDidLoad() {
        super.viewDidLoad()

        let conversationVC = WFCUConversationTableViewController();
        let contactVC = WFCUContactListViewController();
        
        let navConv = UINavigationController.init(rootViewController: conversationVC);
        navConv.tabBarItem.title = "Message";
        navConv.tabBarItem.image = UIImage.init(named: "Image-1");
        navConv.tabBarItem.selectedImage = UIImage.init(named: "Image");
        
        let navCont = UINavigationController.init(rootViewController: contactVC);
        navCont.tabBarItem.title = "Contact";
        navCont.tabBarItem.image = UIImage.init(named: "Image-3");
        navCont.tabBarItem.selectedImage = UIImage.init(named: "Image-2");
        
        self.addChild(navConv);
        self.addChild(navCont);
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
