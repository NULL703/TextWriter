# 项目简介
TextWriter是一个命令行环境下的文本编辑器，功能简单，目前可以实现的功能有：
- 以纯文本文档的形式保存编辑的内容
- 以数字序列形式保存编辑的内容
- 查看数字序列文件或文本文件的内容
- 将文件进行纯文本或数字序列的转换

**以下是在未来的版本中添加的功能：**
- 将纯文本文件或数字序列文件进行低强度的加密 **（私密文件请谨慎使用）**
- 将任何文件转换为C语言数组形式的数字序列以嵌入其应用程序
- 文本编辑脚本化，提高文本编辑效率  
TextWriter的当前版本为**1.0.1**。

# 注意事项
- 在编辑文件时，你只能对当前编辑的这一行文本进行修改，一旦按下回车键，上一行的文本内容将**不可修改**！
- 转义序列以 `^#` 开头，且转义头与下一个换行符间的所有字符都将被忽略。**（转义序列只能放在行末或单独成行，否则转义序列将不可用）**
- 数字序列文件请勿随意修改！（尤其是文件开头的两项值），文件开头的数字序列 `07, 03` 是TextWriter后续版本识别数字序列文件的依据。
- 写入到文件的中文文本及全角字符**在Windows平台下只能用gb2312编码格式，Linux平台一般要用UTF-8编码格式才能打开**。
- 此程序依赖libformula，如果你直接克隆本项目的源代码，你还需要单独准备libformula的源代码，并将其放置到项目中（依赖库在项目中的路径是 `lib/[library_name]` ），然后你可能还需要手动配置Makefile。不过你可以在tag中找到完整的源码包，里面包含有程序所需要的依赖库源代码，直接使用make命令就可以完成编译。  
    libformula的最低版本要求：`V1.1.2`（此版本的正式版本尚未发布，所以本程序的完整源码包中所包含的libformula是预览版）
- 自 `V1.0.1` 版以后，编译生成的程序默认文本语言为中文，如果要使用英文版，请在 `texts.h` 的第10行添加 `#undef ZH_CN`
- 在Linux环境下使用本程序时需要将可执行文件 `cmdtr` 和动态链接库 `libformula.so` 分别放置于 `/usr/bin` 和`/usr/lib` 下才能正常使用。  

# 许可证
本项目使用MIT许可证。[单击查看](./LICENSE)