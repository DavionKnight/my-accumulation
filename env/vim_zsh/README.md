## Shortcuts

1. tab标签功能

   &lt;leader&gt; num #切换到第num个标签
 
2. Mark高亮功能

   &lt;leader&gt; m #高亮当前代码

3. Markdown高亮功能

   F8 #在浏览器打开Markdown预览

## Release

### 2021.07.16

1.support tab and tab operations

2.add Markdown and preview

3.add python-mode


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


