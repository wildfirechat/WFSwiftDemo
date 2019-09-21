# WFSwiftDemo
本工程为Swift集成野火IM示例工程。如果您在使用swift语言集成野火IM的过程中遇到问题，可以对比本工程。

## 更新库文件
本工程的```Frameworkd```目录下放置有所有野火IM的依赖库和资源，您可以更新这些依赖库，使用您编译的版本。注意如果有新添加的动态库依赖，需要在```Embedded Binaries```加上动态库。

## 修改配置
找到```Config.swift```文件，修改其中的```Demo_APP_URL```和```IM_HOST```。如果您使用了非推荐的80端口或者更新ICE配置，请在代码中自行更换。

## 运行
点击XCode执行按钮，启动应用，在第一个界面上输入电话号码和```SuperCode```，点连接。启动之后界面如下：

1. 会话界面
![会话界面](ScreenShot/conversation.png)

2. 联系人界面
![联系人界面](ScreenShot/contact.png)
