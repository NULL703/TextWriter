#!bin/sh
# 用于编译、安装与卸载目标程序的shell脚本 (V1.1)
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

function displayHelp()
{
    echo "Usage: sh install.sh
    sh install.sh [uninstall | clean | compile-only]
    [help]: 显示帮助信息。
    [uninstall]: 卸载cmdtr及其组件。
    [clean]: 清除编译产生的二进制文件。
    [compile-only]: 只编译不安装。"
    echo "默认情况下（即不添加任何参数）将编译并安装cmdtr。"
    exit 0
}

function clean()
{
    make "clean"
    if [ "$?" != 0 ]; then
        echo "Clean failed!"
        exit 1
    fi
    exit 0
}

function compile()
{
    # 编译程序，在程序编译完成后才能进行下面的操作
    if [ "./bin" == "" -o ! -d "./bin" ]; then
        make
    fi
    # 编译失败必定不会产生可执行文件cmdtr，因此此处以可执行文件cmdtr是否存在作为编译成功的依据
    test -e "./bin/cmdtr" || compileFailed
}

case "$1" in
    "help")
        displayHelp
    ;;
    "uninstall")
        uninstall
    ;;
    "clean")
        clean
    ;;
    "compile-only")
        compile; exit 0
    ;;
esac

compile
# 安装cmdtr及其组件
cp -u "./bin/cmdtr" "/bin"
# 如果两个存放库文件的目录都没有libformula则执行安装函数
if [ ! -f "/lib/libformula.so" -a ! -f "/lib64/libformula.so" ]; then
    installLibformula
fi