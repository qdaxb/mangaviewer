# 介绍

axb的漫画阅读工具，使用滚动的方式浏览漫画，支持jpg/png/bmp等常用图像格式，同时也支持zip/rar/7z压缩格式的直接读取。

为了能在上班时更隐蔽的看漫画，我省略了程序的菜单、工具栏和边框等等，只保留了图片显示区域和进度条：  

<img alt="" src="http://blog.2baxb.me/wp-content/uploads/ckfinder/images/20130717_232817.png" style="width: 840px; height: 356px;" />

扔到工作环境大概是这样： <img src="http://blog.2baxb.me/wp-content/uploads/2013/05/447601_51bdca2f05a6a.png" alt="-447601_51bdca2f05a6a" width="600" height="480" />

# 下载

V0.1.0

[百度网盘][1]

# 使用说明

**<span style="color: #ff0000;">按H显示帮助</span>**

<table width="100%">

``` 
<tr>
	<td width="50%">**常规**</td>
	<td></td>
</tr>
<tr>
	<td>O/双击：打开文件</td>
	<td>左键/右键：拖动窗口</td>
</tr>
<tr>
	<td>Alt+`：窗口隐藏</td>
	<td>Q/Esc：退出</td>
</tr>
<tr>
	<td>**阅读**</td>
	<td></td>
</tr>
<tr>
	<td>右键+左键：进入滚动模式</td>
	<td>左键：退出滚动模式</td>
</tr>
<tr>
	<td>滚动模式下移动鼠标：滚动图片</td>
	<td>滚动模式下Ctrl+移动鼠标：反向滚动图片</td>
</tr>
<tr>
	<td>滚轮：滚动图片</td>
	<td>Ctrl+滚轮：翻页</td>
</tr>
	<tr>
	<td>空格/Down： 向下移动</td>
	<td>Backspace/Up: 向上移动</td>
</tr>
<tr>
	<td>左键点击进度条：按进度跳转</td>
	<td>G/右键点击进度条：按页数跳转</td>
</tr>
<tr>
	<td>0-9: 修改移动步长(1/10-1/1)</td>
	<td></td>
</tr>

<tr>
	<td>**显示**</td>
	<td></td>
</tr>
<tr>
	<td>P：切换进度条完整显示模式</td>
	<td>Tab：切换分页模式</td>
</tr>
<tr>
	<td>Ctrl+T：切换图像缩放算法（更快/更好）</td>
	<td>H：切换帮助显示</td>
</tr>
<tr>
	<td>Alt+滚轮：调整宽度</td>
	<td>Shift+滚轮：调整高度</td>
</tr>
<tr>
	<td>F：适应图像大小</td>
	<td>Shift+F：全屏幕</td>
</tr>
```

</table>



# 许可

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.  

You can visit http://www.gnu.org/licenses/gpl.html to get a copy of the GNU General Public License.

程序开发时引用了Qt、File Extractor、zlib、unrar项目，感谢众多项目作者的付出。

# 源代码

<https://github.com/qdaxb/mangaviewer>

# 更新日志

<pre>

V0.1.0 2015/07/29

 -增加全屏功能
 
 -增加左键拖拽功能

V0.0.9 2014/01/28

 -修正图像原始大小不可用bug

 -增加移动步长参数

 -增加部分快捷键

V0.0.8 2013/08/15  

 -修改文件排序算法

V0.0.7 2013/07/20

 -增加适应图像原始大小功能

V0.0.6  2013/06/18

 -修改默认缩放算法

 -修改帮助排版

V0.0.5  2013/06/18

 -增加转到指定页功能

V0.0.4  2013/06/17

 -增加Tab键切换切图模式功能

V0.0.3  2013/06/15

 -增加压缩文件读取功能

2013/05/20

 -重写缩放算法

2013/05/07

 -重构主要模块

2012/08/27

 -重写文件读取类

2012/08/14

 -正序倒序浏览、缩放功能完成

2012/08/08

 -建立

</pre>

 

# 反馈

如果有使用上的问题或者其它想法请联系我  

1、新浪微博[@蛋疼的axb][2]  

2、提交issue

[1]: http://pan.baidu.com/s/1i9C9S
[2]: http://weibo.com/2baxb
