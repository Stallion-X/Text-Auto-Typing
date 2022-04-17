# Text_Auto_Typing
一款针对学校作业系统代码输入体验太烂而推出的，使用Qt开发的，具备图形界面的自动输入软件。

An automatic typing program developed by Qt due to the poor experience of homework system.
更新日志
texttokeyV1.5_fixed
修复死循环bug
为应对作业系统修改刷新速度导致难以保存文件 增加了新的应对措施
修改为默认不使用全自动调整
校验文本增加弹窗提示

texttokeyV1.5（重大更新）
加入自动校验文本与自动调速功能 检测到输入文本被作业系统刷新时会自动清空放慢速度重新输
加入首次使用时的用户协议
增加配置文件

texttokeyV1.4（重大更新）
采用多线程 输入时主界面不会停止响应
增加调速功能

texttokeyV1.3
为应对作业系统增加屏蔽各大自动输入工具功能的紧急状况 特紧急修改程序推出此版本
降低两个模式输入速度 防止刚输入的文本被刷新干掉
从该版本起 采用加壳加密源代码 防止该工具被反编译针对

texttokeyV1.2（重大更新）
加入新模式2（极速模式） 一秒输完 极大加速自动输入体验 但兼容性较差 仅支持win32api控件

texttokeyV1.1
加入调整设置功能
加入淦爆作业系统排版功能
