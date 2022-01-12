## Shortcuts
### 常用操作
* [leader] + num   &emsp;&emsp;&emsp;切换到第num个标签
* [leader] + m     &emsp;&emsp;&emsp;高亮当前代码
* [leader] + n     &emsp;&emsp;&emsp;取消当前高亮
* [leader] + mc    &emsp;&emsp;&emsp;取消所有高亮
* [leader] + *     &emsp;&emsp;&emsp;跳转到当前高亮的下一个单词
* [leader] + #     &emsp;&emsp;&emsp;跳转到当前高亮的上一个单词
* [leader] + gb    &emsp;&emsp;&emsp;git blame
* [leader] + gd    &emsp;&emsp;&emsp;git diff
* [leader] + gs    &emsp;&emsp;&emsp;git status
* [leader] + vv    &emsp;&emsp;&emsp;grep -rn
* [Ctrl+L]         &emsp;&emsp;&emsp;&emsp;next tab
* [Ctrl+H]         &emsp;&emsp;&emsp;&emsp;privous tab
* F8                &emsp;&emsp;&emsp;在浏览器打开Markdown预览
### Nerdtree常用操作
* o: 打开一个目录或者打开文件，非常重要，避免nerdtree引入的多标签问题
* C: 将根路径设置为光标所在的目录
* u: 设置上级目录为根路径
* U: 设置上级目录为根路径，但是维持原来目录打开的状态
* m: 显示文件系统菜单(可以以UI方式打开文件夹,复制路径等)
---


## Depends

### vim configurations

#### 1. install vundle  
```bash
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
```

#### 2. support clipboard
```bash
sudo apt-get install vim-gtk vim-gnome -y
vim --version | grep "clipboard"
```

#### 3. make nerdtree beauty
 * 1) download otf
```bash
mkdir -p ~/.local/share/fonts
cd ~/.local/share/fonts && curl -fLo "Droid Sans Mono for Powerline Nerd Font Complete.otf" https://github.com/ryanoasis/nerd-fonts/raw/master/patched-fonts/DroidSansMono/complete/Droid%20Sans%20Mono%20Nerd%20Font%20Complete.otf
```
 * 2) get otf and install
 * 3) set terminal font choice ‘Droid Sans Mono Nerd'

#### 4. Use sshkey to access github without username and passwd
 * 1) gen ssh key
```bash
    ssh-keygen -t rsa -b 4096 -C "你的邮箱"
```
   do not overwrite system default rsakey ~/.ssh/id_rsa, just save in current path
 * 2) copy public key to github
 * 3) set local github default private key in ~/.ssh/config
```bash
Host github.com
    HostName github.com
    User git
    IdentityFile /home/meteor/.ssh/id_rsa.github
    IdentitiesOnly yes
```
#### 5. install ag searcher
```bash
    apt-get install silversearcher-ag
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

### cscope support python
```bash
find ./ -name '*.py' > ./cscope.files
cscope -Rbqk
```
---

## ReleaseNote

### 2021.07.28
1. 因为ctrl+]与函数跳转冲突，找到一个更好替代快捷键
 * ctrl+L tab next
 * ctrl+H tab privous
2. 关闭切换窗口快捷键

### 2021.07.28
1. vim有些键是绑死的，映射一个另一个会跟着变，如
 * tab与ctrl+i是绑死的,因此下一个tab修改为ctrl+](尽量用ctrl，因为ctrl一直按着也生效)
 * ctrl+[与esc是绑死的,取消tab privous,尽量习惯用leader+数字切换标签
2. 取消tab close，:q可以替代

### 2021.07.27
1. 切换窗口修改为ctrl+h/j/k/l
2. cscope支持python

### 2021.07.21
1. 修复nerdtree打开新文件时，原tab名字变为’NERD_tree'问题
 * 新增vim-nerdtree-tabs
 * let g:nerdtree_tabs_meaningful_tab_names = 1
2. 美化nerdtree字体

### 2021.07.19
1. 修复nerdtree打开目录时多开一个tab的问题
 * 通过o打开目录可解决
2. 添加常用快捷键表

### 2021.07.16
1. support tab and tab operations
2. add Markdown and preview
3. add python-mode

