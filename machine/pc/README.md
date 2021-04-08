## ID
PC

## 注意事项
1. Linux 系统的 VS Code 用 GitHub 账号同步，Windows 系统的 VS Code 用微软账户同步，避免出现系统之间的设置影响。  
2. VS Code 的同步设置不要勾选扩展。  

## 配置日志
1. 关闭 `sudo` 密码  
    1. 打开 `visudo`
        ```bash
        sudo visudo
        ```
    2. 找到 `%sudo ALL=(ALL:ALL) ALL` 这一行修改为 `%sudo ALL=(ALL:ALL) NOPASSWD:ALL`
2. 配置 `zsh`  
    详见[写给工程师的 Ubuntu 20.04 最佳配置指南 ](https://juejin.cn/post/6844904149822210056#heading-1)
3. 配置 `ssh`  
    1. 安装 `oepnssh-server`：
        ```bash
        sudo apt update
        sudo apt install openssh-server -y
        ```
    2. 查看运行状态：
        ```bash
        systemctl status ssh
        ```
    3. 允许 `ssh` 通过防火墙：
        ```bash
        sudo ufw allow ssh
        ```
    4. 通过 `ssh` 连接服务器：
        ```bash
        ssh username@ipaddr
        ```
    5. 禁用或启用 `ssh`：
        ```bash
        sudo systemctl disable --now ssh
        sudo systemctl enable --now ssh
        ```
    6. 复制本地公钥到服务器上：
        ```bash
        ssh-copy-id username@ipaddr
        ```
    7. 关闭密码登录：
        ```bash
        # 打开配置文件
        sudo vi /etc/ssh/sshd_config
        ```
        ```bash
        # 找到以下三项修改
        PasswordAuthentication no
        ChallengeResponseAuthentication no
        UsePAM no
        ```
        ```bash
        # 重启 ssh 服务
        sudo systemctl restart ssh
        ```