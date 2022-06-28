# dijikstra-hamiltonCycle-viewer
# 迪杰斯特拉(Dijikstra)可视化与哈密顿(Hamilton)回路判断可视化工具



**前言：本例程序开发环境为：Qt5.15.2，使用的是MSVC 2019 64bit编译器**。



**整篇概述：**

&nbsp;      本项目由两个部分组成，一个是迪杰斯特拉(Dijikstra)可视化的程序，另一个是哈密顿(Hamilton)回路判断可视化的程序。

1. 迪杰斯特拉(Dijikstra)：源代码，演示图片
2. 哈密顿(Hamilton)回路：源代码，演示图片，安装包

---



#### 一、迪杰斯特拉(Dijikstra)

直接下载源码编译运行即可

##### 1. 第一个版本，界面截图如下

![p1](https://user-images.githubusercontent.com/89370087/176125227-83c4dce5-2679-44fa-b6c9-21034a672fe4.png)
![p2](https://user-images.githubusercontent.com/89370087/176125244-ce133b2f-1e80-408b-bfb5-9ab10b8c6694.png)
![p3](https://user-images.githubusercontent.com/89370087/176125256-b4e266bc-2536-41d3-aa4a-56dbea43b350.png)
![p4](https://user-images.githubusercontent.com/89370087/176125268-30b08d3e-e8c9-4b07-a38b-9aa487e13126.png)
![p5](https://user-images.githubusercontent.com/89370087/176125290-58c21981-2d75-46fb-a06d-4fce253190a3.png)
![p6](https://user-images.githubusercontent.com/89370087/176125323-758f5e18-de9d-432e-8a65-8ede1078f80f.png)


##### 2. 第二个版本，界面截图如下：

![p55](https://user-images.githubusercontent.com/89370087/176125676-397ef17a-015d-4ae2-b4b5-3d9587308b60.png)


##### 3. 不足之处

1. 程序界面主题色彩比较单一，二次开发者应该再琢磨琢磨QSS样式对控件美化。
2. 程序的健壮性不强，当存在非法输入时不能完全检测出，程序接收非法数据时易崩溃。
3. 程序界面的QGraphicsView中所画的点与线可以再做优化，特别是在颜色和形状方面，对于本程序所画的点，为一个圆形，填充的颜色为黄色，点与点所连线段为黑色。当给出起点和终点时，如果存在一条最短路径，那么，这条路径上的边会变成红色。

&nbsp;

##### 4. 最后说明

&nbsp;      因为这个程序属于半成品，所以该程序的安装包不对外发布，但是会给出源代码，感兴趣的朋友可以自行编译，关于界面美化部分建议可以直接参考第二个程序哈密顿回路判断(Hamilton)。



#### 二、哈密顿回路判断(Hamilton)

直接下载源码编译运行即可。



##### 1. 界面截图
![p1](https://user-images.githubusercontent.com/89370087/176125809-724e6c7a-ba88-4f53-9b5f-030346ec13bf.png)
![p2](https://user-images.githubusercontent.com/89370087/176125820-362ced3d-a2b0-40ed-9b27-d47589ec8d51.png)
![p3](https://user-images.githubusercontent.com/89370087/176125842-c277a531-3fcb-4e26-9cff-fcd1ecb9fe3b.png)
![p4](https://user-images.githubusercontent.com/89370087/176125860-61dbbdea-0751-4fb5-b0ff-56db7c7660f0.png)
![p5](https://user-images.githubusercontent.com/89370087/176125878-8945876d-5eda-46a2-bb84-5e95d9d598da.png)
![p6](https://user-images.githubusercontent.com/89370087/176125891-3942922a-aea3-4b7b-a3c9-14142a1d4975.png)
![p7](https://user-images.githubusercontent.com/89370087/176125901-db31559c-d6e8-4d5d-9929-5a59416a2c63.png)

##### 2. 最后说明
&nbsp;      该程序的安装包对外发布，并给出源代码。




