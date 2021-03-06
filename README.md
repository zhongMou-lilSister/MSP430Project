# MSP430Project
浙江大学暑期课程《电子综合设计》课程设计

## 注意事项

现在只把*.c和*.h代码放上去，项目要用自己的。每次从github上面pull下来之后要自行进行复制粘贴（本地新建一个文件夹，专门负责本地的git，别和CCS里面的弄混了）。就是说，*.c和*.h代码更新的过程可以自动完成。但是手动复制粘贴还是不能少。（可以试试整体复制粘贴导入）下面是git的简易教程。

# Git使用方法-简版（转自daibi07）

## 命令行操作

### 1. 创建远程仓库（一组创一个即可）
   
   github上面create repository，注意不要用README.md初始化仓库，即创建时下图的这个别选。
   
   ![UM4yWV.jpg](https://s1.ax1x.com/2020/07/11/UM4yWV.jpg)

### 2. 使用git命令，在本地克隆远程仓库
   
   `git clone https://github.com/daibi07/Test1.git`

### 3. 设置签名

   `git config user.name "你的用户名"`
   
   `git config user.email "你的邮箱"`
   
   也可以进行全局设置，也就是clone到本机上的所有项目都用一个签名：
   
   `git config --global user.name "你的用户名"`

   用此命令查看设置：
   `git config -l`

### 4. 项目修改后提交到本地仓库

   添加文件修改：`git add .`

   提交文件修改到本地仓库：`git commit -m "XXXX"`（里面就是填个版本号吧）
   
### 5. 将本地仓库提交到远程仓库（push）   
   
   先通过命令git remote show [remote-name] 查看某个远程仓库的详细信息，比如要看所克隆的origin仓库，可以运行：
   
   `git remote show origin`
   
   如果这个远程仓库的地址与你所想提交的地址不符，可以进行修改：
   
   `git remote rm origin`
   
   `git remote add origin your_remote_url`（如：https://github.com/daibi07/Test1.git）
   
   提交到远程仓库：`git push -u origin master`
   
   push时可能会报错说“更新被拒绝，因为远程仓库包含您本地尚不存在的提交”，可参考此[解决方法](https://blog.csdn.net/XiangJiaoJun_/article/details/83721557?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase)
   
### 6. 将远程仓库同步到本地（pull）

   `git pull origin master`
   
## 参考资料

https://github.com/daibi07/Test/edit/master/README.md
