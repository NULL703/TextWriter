#!bin/sh
# 用于编译、安装与卸载目标程序的shell (V1.0)
# Created on 2023.2.18
# Created by NULL_703
# NOTE: 需要配合sudo命令或者以root身份执行此脚本才能完成编译安装操作

function uninstall()
{
    rm -f "/bin/cmdtr"
    rm -f "/lib/libformula.so"
    exit 0
}

function compileFailed()
{
    echo "Compile failed!"
    exit 1
}

function installLibformula()
{
    read -p "你要将libformula.so安装到何处？(lib/lib64)" libDIR
    [ "$libDIR" == "lib" ] && cp -u "./bin/libformula.so" "/lib"
    [ "$libDIR" == "lib64" ] && cp -u "./bin/libformula.so" "/lib64"
}

if [ "$1" == "uninstall" ]; then
    uninstall
fi

# 编译程序，在程序编译完成后才能进行下面的操作
if [ "./bin" == "" -o ! -d "./bin" ]; then
    make
fi

# 编译失败必定不会参数可执行文件cmdtr，因此此处以可执行文件cmdtr是否存在作为编译成功的依据
test -e "./bin/cmdtr" || compileFailed
cp -u "./bin/cmdtr" "/bin"
# 如果两个存放库文件的目录都没有libformula则执行安装函数
if [ ! -f "/lib/libformula.so" -a ! -f "/lib64/libformula.so" ]; then
    installLibformula
fi