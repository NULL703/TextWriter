# 项目简介
TextWriter是一个命令行环境下的文本编辑器，功能简单，目前可以实现的功能有：
- 以纯文本文档的形式保存编辑的内容
- 以数字序列形式保存编辑的内容
- 查看数字序列文件或文本文件的内容
- 将文件进行纯文本或数字序列的转换
- 将任何文件转换为C语言数组形式的数字序列以嵌入其应用程序
- 批量转换文件  
- 同时查看多个文件，类似于 `cat` 命令  

**以下是在未来的版本中添加的功能：**
- 将纯文本文件或数字序列文件进行低强度的加密 **（私密文件请谨慎使用）**
- 文本编辑脚本化，提高文本编辑效率  
- 在批处理模式中排除要转换的文件  
- 主选项支持多文件处理（不包括批处理模式）  
- 指定偏移量或行数查看文件中的内容  
TextWriter的当前版本为**1.1.3**。

# 注意事项
- 在编辑文件时，你只能对当前编辑的这一行文本进行修改，一旦按下回车键，上一行的文本内容将**不可修改**！
- 转义序列以 `^#` 开头，且转义头与下一个换行符间的所有字符都将被忽略。**（转义序列只能放在行末或单独成行，否则转义序列将不可用）**
- 数字序列文件请勿随意修改！（尤其是文件开头的两项值），文件开头的数字序列 `07, 03` 是TextWriter后续版本识别数字序列文件的依据。
- 写入到文件的中文文本及全角字符**在Windows平台下只能用gb2312编码格式，Linux平台一般要用UTF-8编码格式才能打开**。
- 自 `V1.0.1` 版以后，编译生成的程序默认文本语言为中文，如果要使用英文版，请在 `texts.h` 的第10行添加 `#undef ZH_CN`
- 在Linux环境下使用本程序时需要将可执行文件 `cmdtr` 和动态链接库 `libformula.so` 分别放置于 `/usr/bin` 和`/usr/lib` 下才能正常使用（libformula.so的存放位置因发行版而异）。  
- 如果使用源代码编译，并且目标平台为Windows，请尽量使用gcc编译器进行编译，若使用MSVC环境进行编译可能会使程序出现诸多的兼容性问题，对于这些问题，本人暂时不会更改。

# 许可证
本项目使用MIT许可证。[单击查看](./LICENSE)
