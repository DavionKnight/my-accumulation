## Shortcuts
### 常用操作
* [leader] + num    #切换到第num个标签
* [leader] + m      #高亮当前代码
* [leader] + n      #取消当前高亮
* [leader] + mc     #取消所有高亮
* [leader] + *      #跳转到当前高亮的下一个单词
* [leader] + #      #跳转到当前高亮的上一个单词
\# 跳转到当前高亮的上一个单词
* F8            #在浏览器打开Markdown预览
---
### Nerdtree常用操作
* o: 打开一个目录或者打开文件，非常重要，避免nerdtree引入的多标签问题
* C: 将根路径设置为光标所在的目录
* u: 设置上级目录为根路径
* U: 设置上级目录为根路径，但是维持原来目录打开的状态
* m: 显示文件系统菜单(可以以UI方式打开文件夹,复制路径等)
---

## Release

### 2021.07.19
1. 修复nerdtree打开目录时多开一个tab的问题
* 通过o打开目录可解决
2. 添加常用快捷键表

### 2021.07.16
1. support tab and tab operations
2. add Markdown and preview
3. add python-mode


## Depends

### vim configurations

1. install vundle  
```bash
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
```
2. support clipboard
```bash
sudo apt-get install vim-gtk
```

### zsh configurations

```bash
# 重新定义expect（解决 rz/sz 工具异常的问题）
alias expect='export LC_CTYPE=en_US && expect'
# 登录到自己的relay，需设置relay用户名 + 邮箱密码（注意每次修改邮箱密码，就需要更新一次！！！）
alias relay='expect ~/.relay.expect namexxxx passwdxxxx'
# 如：配置自动登录自己开发机
alias mydev='relay namexxx@machine_address'
# 关闭history共享
unsetopt share_history
unsetopt inc_append_history
```


